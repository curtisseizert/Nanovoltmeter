#ifndef ACQ_H
#define ACQ_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "sys_cfg.h"
#include "stdint.h"

#define ACQ_FLAG_GPIO_CDS			(1U << 0)
#define ACQ_FLAG_GPIOCDS_SW1	(1U << 1)
#define ACQ_FLAG_GPIOCDS_SW2	(1U << 2)
#define ACQ_FLAG_GPIO_MOD			(1U << 3)
#define ACQ_FLAG_GPIOMODPOL		(1U << 4)
#define ACQ_FLAG_PARAM_SETUP	(1U << 5)
#define ACQ_FLAG_MODTIMRDY		(1U << 6)
#define ACQ_FLAG_MOD_ON				(1U << 7)
#define ACQ_FLAG_GPIOMOD_SET	(1U << 8)
#define ACQ_FLAG_GPIOCDS_SET	(1U << 9)

#define RELAY_K1_SET					(1U << 1)
#define RELAY_K2_SET					(1U << 2)
#define RELAY_K3_SET					(1U << 3)

#define OVERRANGE_FLAG						1U << 0
#define ADC_OVERRANGE_FLAG				1U << 1
#define HI_GAIN_FLAG							1U << 2
#define SEND_UART_FLAG						1U << 3
#define SKIP_VOS_DAC_UPDATE_FLAG	1U << 4
#define BLOCK_SYNC_ERROR_FLAG			1U << 5 // If ADC blocks are not aligned with mod cycles

struct acq_param{
	
	
	uint32_t mod_cnt, tim4_arr, tim5_arr;
	uint32_t mod_deadtime_cyc, demod_deadtime_cyc;
	uint32_t adc_samp_freq;
	
	float mod_freq, mod_deadtime_us, demod_deadtime_us, settle_time_us;
	float Vos_dac_deadband_nV, Vos_dac_deadband_V, lsb_size_nV;
	
	uint16_t codeDeadBand;
	uint16_t mod_cycles_per_avg;
	uint16_t mod_cycles_per_update; // number of modulator cycles per VOS DAC update
	uint16_t mod_cycles_per_cds;
	uint16_t log2SampAvg, cnv_cycles;
	uint16_t mod_psc, blocks_per_cycle;
	uint16_t gain_state, relay_states;
	uint16_t array_size;
	uint16_t flags;
	
};



void setupAcquisition(struct acq_param * acq);
void AD403X_SetAcquisitionParam(struct acq_param * acq);
void setAcquisitionDefaults(struct acq_param * acq);

extern double Vref, gain40, gain60;
extern volatile int32_t * AD4032_data;
extern volatile uint16_t ind;
extern volatile int32_t offset_accum;
extern volatile int16_t offset_counter;

void allocateArrayMemory(struct acq_param * acq);

void timerConfig(struct acq_param * acq);

void GPIOmodclocks(struct acq_param * acq);
void GPIOcdsclocks(struct acq_param * acq);
void setmodphase(struct acq_param * acq, uint16_t);
void setcdsphase(struct acq_param * acq, uint8_t, uint8_t);

void TIMmodclocks(struct acq_param * acq);
void TIMcdsclocks(struct acq_param * acq);

void startAcquisition(struct acq_param * acq);
void pauseAcquisition(struct acq_param * acq);
void pauseAcquisitionDiagnostic(struct acq_param * acq);

void disableModTimers(void);

void initModTimers(struct acq_param * acq);

int8_t getGpioPhase(struct acq_param * acq);

void setGain(struct acq_param * acq, uint16_t g);
double getGain(struct acq_param * acq);
float getLSBSize_nV(double gain);

void updateDeadBand(struct acq_param * acq);

void relaySetState(struct acq_param * acq, uint8_t relayNum, uint8_t state);

#endif