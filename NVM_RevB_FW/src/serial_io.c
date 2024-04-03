
#include "stdio.h"
#include "stdlib.h"

#include "serial_io.h"
#include "ad5686.h"
#include "ad403x.h"
#include "tim.h"

void parseInput(char * inputcmd)
{
	uint16_t cmdCode;
	uint8_t i = 0;
	
	while(!inputcmd[i] && i<UART_RX_CMD_SIZE) i++; // increment index until past blanks
	if(inputcmd[i] == 0x20) goto nextcmd;
	
	if((inputcmd[i + 1] == 0x20) || (inputcmd[i + 1] == 0x0A)) {
		cmdCode = inputcmd[i];
		i++;
	}
	else{
		if((inputcmd[i + 2] == 0x20) || (inputcmd[i + 2] == 0x0A)) {
			cmdCode = (inputcmd[i] << 8) | inputcmd[i + 1];
			i += 2;
		}
		else {
			cmdCode = inputcmd[i];
			i++;
		}
	}
	
	uint8_t reply_buffer[32];
	
	uint32_t param = strtoul(&inputcmd[i],&inputcmd[UART_RX_CMD_SIZE - i],10);
	double dparam = strtod(&inputcmd[i],&inputcmd[UART_RX_CMD_SIZE - i]);

		switch(cmdCode){
			
				/* Parameters are lowercase letters */
			case 0x67: // g (gain)
				setGain(&acq1, (uint16_t)param );
				setGain(&acq2, (uint16_t)param );
				break;
			case 0x6D66: // mf (modulator frequency)
				acq2.mod_freq = (float) dparam;
				break;
			case 0x6361: // ca (mod cycles per average)
				acq2.mod_cycles_per_avg = (uint16_t) param;
				break;
			case 0x6375: // cu (mod cycles per DAC update)
				acq2.mod_cycles_per_update = (uint16_t) param;
				break;
			case 0x6363: // cc (mod cycles per CDS cycle)
				acq2.mod_cycles_per_cds = (uint16_t) param;
				break;
			case 0x6673: // fs (ADC sampling frequency)
				acq2.adc_samp_freq = param;
				break;
			case 0x6C61: // la (log2 samples per ADC block)
				acq2.log2SampAvg = (uint16_t) param;
				break;
			case 0x7374: // st (settling time, microseconds)
				acq2.settle_time_us = (float) dparam;
				break;
			case 0x6462: // db (DAC update deadband, nanovolts)
				acq2.Vos_dac_deadband_nV = (float) dparam;
				break;
			case 0x646D: // dm (deadtime, modulator, microseconds)
				acq2.mod_deadtime_us = (float) dparam;
				break;
			case 0x6464: // dd (deadtime, demodulator, microseconds)
				acq2.demod_deadtime_us = (float) dparam;
				break;
			
			
				
				/* Commands are uppercase letters */
			case 0x54: // T (Test)
				sendData(reply_buffer, sprintf(reply_buffer, "Test request recieved\n\r"));
				break;
			case 0x53: // S (Start)
				startAcquisition(&acq1);
				break;
			case 0x50: // P (Pause)
				pauseAcquisition(&acq1);
				break;
			case 0x49: // I (Init)
				setupAcquisition(&acq1);
				break;
			case 0x55: // U (Update)
				pauseAcquisition(&acq1);
				acq1 = acq2;
				setupAcquisition(&acq1);
				break;
			case 0x4C43: // LC (List Current parameters)
				pauseAcquisition(&acq1);
				sendParameterString(&acq1);
				break;
			case 0x4C4E: // LN (List New parameters)
				pauseAcquisition(&acq1);
				sendParameterString(&acq2);
				break;
			case 0x4346: // CF (Clear Flags)
				flags = 0;
				break;
				/* Temperature commands */
			case 0x5354: // ST (Start Temperature)
				LPTIM1Start();
				break;
			case 0x5054: // PT (Pause Temperature)
				LPTIM1Stop();
				break;
			
			
				/* Relay commands */
			case 0x4B31: // K1 (Relay K1 state, S = 1)
				relaySetState(&acq1, 1, (uint8_t) param);
				break;
			case 0x4B32: // K2 (Relay K2 state, S = 1)
				relaySetState(&acq1, 2, (uint8_t) param);
				break;
			case 0x4B33: // K3 (Relay K3 state, S = 1)
				relaySetState(&acq1, 3, (uint8_t) param);
				break;
			
			
				/* DAC commands */
			case 0x4441: // DA (DAC output A code)
				AD5686_WriteDACDMA(AD5686_DAC_A, (uint16_t) param);
				break;
			case 0x4442: // DB (DAC output B code)
				AD5686_WriteDACDMA(AD5686_DAC_B, (uint16_t) param);
				break;			
			case 0x4443: // DC (DAC output C code)
				AD5686_WriteDACDMA(AD5686_DAC_C, (uint16_t) param);
				break;				
			case 0x4444: // DD (DAC output D code)
				AD5686_WriteDACDMA(AD5686_DAC_D, (uint16_t) param);
				break;			
			
			
				/* Diagnostic Commands */
			case 0x5044: // PD (Pause, Diagnostic)
				pauseAcquisitionDiagnostic(&acq1);
				break;
			case 0x5252: // RR (Read Register)
				sendRegValue((uint16_t) param, AD403X_ReadRegisterSingle((uint16_t) param));
				break;
			case 0x4743: // GC (Gpio Cds)
				flags |= SKIP_VOS_DAC_UPDATE_FLAG;
				gpioCDSCmd((uint8_t) param);
				break;
			case 0x474D: // GM (Gpio Mod)
				flags |= SKIP_VOS_DAC_UPDATE_FLAG;
				GPIOmodclocks(&acq1);
				setmodphase(&acq1, (uint16_t) param);
				break;
				
				
		}
		nextcmd:
	for(uint8_t i = 0; i < UART_RX_CMD_SIZE; i++) inputcmd[i]=0;
	cmdInd[0] = cmdInd[1];

}

void gpioCDSCmd(uint8_t phase)
{
	uint8_t phase1, phase2;
	
	phase1 = phase & 0x01;
	phase >>= 1;
	phase2 = phase & 0x01;
	
	GPIOcdsclocks(&acq1);
	setcdsphase(&acq1, phase1, phase2);
	
}

void sendParameterString(struct acq_param * acq)
{
	char TxBuffer[64];
	uint8_t len;
	UART4DisableDMATx();
	double gain;
	
	if(acq->gain_state) gain = gain60;
	else	gain = gain40;
	
	len = sprintf(TxBuffer, "Modulator Frequency: %.2f Hz\n\r", acq->mod_freq);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "Modulator Cycles Per Average: %d\n\r", acq->mod_cycles_per_avg);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "Modulator Cycles Per DAC Update: %d\n\r", acq->mod_cycles_per_update);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "Modulator Cycles Per CDS Cycle: %d\n\r", acq->mod_cycles_per_cds);
	sendDataBlocking(TxBuffer, len);

	len = sprintf(TxBuffer, "ADC Sampling Frequency: %.3f kSPS\n\r", (float) acq->adc_samp_freq/1000);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "ADC Block Size: %d\n\r", (uint32_t) (1U << acq->log2SampAvg));
	sendDataBlocking(TxBuffer, len);

	len = sprintf(TxBuffer, "Modulator Settling Time: %.2f us\n\r", acq->settle_time_us);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "DAC update deadband: %.1f nV\n\r", acq->Vos_dac_deadband_nV);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "Modulator Deadtime: %.2f us\n\r", acq->mod_deadtime_us);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "Demodulator Deadtime: %.2f us\n\r", acq->demod_deadtime_us);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "Frontend Gain: %.6f\n\r", gain);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "Reference Voltage: %.6f V\n\r", Vref);
	sendDataBlocking(TxBuffer, len);
	
	len = sprintf(TxBuffer, "Sample Rate: %.2f SPS\n\r", acq->mod_freq/acq->mod_cycles_per_avg);
	sendDataBlocking(TxBuffer, len);
	
	UART4EnableDMATx();
}

void sendRegValue(uint16_t reg, uint8_t val)
{
	char TxBuffer[64];
	uint8_t len;
	UART4DisableDMATx();
	
	len = sprintf(TxBuffer, "Addr: %x  Value: %x\n\r", reg, val);
	sendDataBlocking(TxBuffer, len);
	
	UART4EnableDMATx();
}