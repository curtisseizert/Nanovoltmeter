
#include "acq_private.h"

#include "nvmb.h"
#include "gpio.h"
#include "tim.h"
#include "uart.h"
#include "spi.h"


/// @brief Performs the timer and AD403X setup steps to prepare for acquisition
/// @param acq AcqParam_t container for the acquisition parameters and data
void setup_acquisition(AcqParam_t * acq)
{
	init_mod_timers(acq);
	timer_config(acq);
	ad403x_reset(acq->adc);
	ad403x_set_acquisition_param(acq);
	acq->adc_data->bufsize = acq->blocks_per_cycle;
	sinc_set_order(acq->sinc, acq->sinc_order);
}

/// @brief Checks if the CDS controller (GPIO/TIMER) state matches the setting
/// @param acq AcqParam_t container for the acquisition parameters and data
/// @return 1 if the states do not match
/// @return 0 if the states match
static int16_t cds_state_setting_mismatch(AcqParam_t * acq)
{
	return !(acq->flags & ACQ_FLAG_GPIO_CDS) != !(acq->flags & ACQ_FLAG_GPIOCDS_SET) ? 0 : 1;
}

/// @brief Checks if the MOD/DEMOD controller (GPIO/TIMER) state matches the setting
/// @param acq AcqParam_t container for the acquisition parameters and data
/// @return 1 if the states do not match
/// @return 0 if the states match
static int16_t mod_state_setting_mismatch(AcqParam_t * acq)
{
	return !(acq->flags & ACQ_FLAG_GPIO_MOD) != !(acq->flags & ACQ_FLAG_GPIOMOD_SET) ? 0 : 1;
}

/// @brief Starts acquisition
/// @param acq AcqParam_t container for the acquisition parameters and data
void start_acquisition(AcqParam_t * acq)
{
	if(cds_state_setting_mismatch(acq)) tim_cds_clocks(acq);
	if(mod_state_setting_mismatch(acq)) tim_mod_clocks(acq);

	enable_timer(TIM2);
	enable_timer(TIM15);
	
	acq->flags |= ACQ_FLAG_MOD_ON;
}

/// @brief Pauses acquisition, stops mod/demod, resets and sets up ADC
/// @param acq AcqParam_t container for the acquisition parameters and data
void pause_acquisition(AcqParam_t * acq)
{
	/* Disable timers, 
	*	 enable gpio modulator and cds
	*	 reset AD403X,
	*  reconfigure AD403X with current parameters*/
	
	disable_mod_timers();
	TIM8->CCER &= ~TIM_CCER_CC1NE;	// Disable TIM8 output (it is enabled in TIM3IRQ_Handler)
	acq->index = 0;
	acq->offset_accum = 0;
	acq->offset_counter = 0;
	
	gpio_mod_clocks(acq);
	gpio_cds_clocks(acq);
	set_mod_phase(acq, MOD_PHASE_1);
	set_cds_phase(acq, SW1_CM_SW2_CM);
	
	ad403x_reset(acq->adc);
	ad403x_set_acquisition_param(acq);

	acq->flags &= ~(ACQ_FLAG_MOD_ON | ACQ_FLAG_MODTIMRDY);
}

/// @brief Pauses acquisition without resetting the AD403X to enable diagnostics
/// @param acq AcqParam_t container for the acquisition parameters and data
void pause_acquisition_diagnostic(AcqParam_t * acq)
{
	/* Disable timers, 
	*	 enable gpio modulator and cds
	*	 reset AD403X,
	*  reconfigure AD403X with current parameters*/
	
	disable_mod_timers();
	TIM8->CCER &= ~TIM_CCER_CC1NE;	// Disable TIM8 output (it is enabled in TIM3IRQ_Handler)
	
	gpio_mod_clocks(acq);
	gpio_cds_clocks(acq);
	set_mod_phase(acq, MOD_PHASE_0);
	set_cds_phase(acq, SW1_CM_SW2_CM);
}

/// @brief Disables the modulator/demodulator, CDS, and ADC timers
/// @param None
static void disable_mod_timers(void)
{
	TIM_TypeDef * timers[6] = {TIM2, TIM3, TIM4, TIM5, TIM8, TIM15};

	for(uint16_t i = 0; i < 6; i++)
	{
		disable_timer(timers[i]);
		reset_timer(timers[i]);
	}
}

/// @brief Configures the AD403X with the acquisition parameters
/// @param acq AcqParam_t container for the acquisition parameters and data
static void ad403x_set_acquisition_param(AcqParam_t * acq)
{
		// Wait for busy to go low indicating POR is complete
	while(gpio_get_state(BUSY_C_Pin) == GPIO_STATE_HI);
	ad403x_enter_reg_access(acq->adc);
	
	ad403x_write_register(acq->adc, AD403X_REG_AVG, acq->log2SampAvg);
	ad403x_write_register(acq->adc, AD403X_REG_MODES, AD403X_DEFAULT_MODE);
	
	ad403x_exit_reg_access(acq->adc);
}


/// @brief Initializes the modulator/demodulator, CDS, and ADC timers
/// @param acq AcqParam_t container for the acquisition parameters and data
static void init_mod_timers(AcqParam_t * acq)
{
	acq->flags &= ~(ACQ_FLAG_GPIO_CDS | ACQ_FLAG_GPIO_MOD);
	
	tim2_init();		// Initialize timers
	tim3_init();
	tim4_init();
	tim5_init();
	tim8_init();
	tim15_init();
	
	acq->flags |= ACQ_FLAG_MODTIMRDY;
}


/// @brief Uses acquisition parameters to calculate timer parameters and update registers
/// @param acq - AcqParam_t container of the acquisition parameters and data
static void timer_config(AcqParam_t * acq)
{
	/* NOTE: Assumes no prescaler for timers */
	
	uint16_t blocks_per_phase;
	uint32_t ticks_per_phase;
	uint32_t ticks_per_sample;
	uint32_t ticks_per_block;

		/* All timers use integer multiples of ticks_per_phase or ticks_per_sample */
	ticks_per_phase = (uint32_t) (get_sys_freq() / (acq->mod_freq * 2));
	ticks_per_sample = (uint32_t) (get_sys_freq() / acq->adc_samp_freq);
	ticks_per_block = ticks_per_sample << acq->log2SampAvg;
	
		/* Recalculate mod_frequency to account for finite resolution */
	acq->mod_freq = (float) get_sys_freq() / (float) (ticks_per_phase * 2);
	
		/* Calculate ARR values for mod, demod, and cds timers */
	TIM2->ARR = (2 * ticks_per_phase) - 1;
	TIM3->ARR = (2 * ticks_per_phase) - 1;
	TIM4->ARR = (2 * ticks_per_phase * acq->mod_cycles_per_cds) - 1;
	TIM5->ARR = ticks_per_phase - 1;
	
		/* Calculate deadtimes in cycles */
	float clkfreq_mhz = get_sys_freq()/1000000;
	acq->mod_deadtime_cyc = (uint32_t) (acq->mod_deadtime_us * clkfreq_mhz);
	acq->demod_deadtime_cyc = (uint32_t) (acq->demod_deadtime_us * clkfreq_mhz);
	
		/* Recalculate actual deadtimes */
	acq->mod_deadtime_us = (float) acq->mod_deadtime_cyc/ (float) clkfreq_mhz;
	acq->demod_deadtime_us = (float) acq->demod_deadtime_cyc/ (float) clkfreq_mhz;
	
		/* Calculate capture compare register values */
	TIM2->CCR1 = (uint32_t) (ticks_per_phase - acq->mod_deadtime_cyc - 1);
	TIM2->CCR3 = (uint32_t) (ticks_per_phase - 1);
	TIM2->CCR4 = (uint32_t) ((2 * ticks_per_phase) - acq->mod_deadtime_cyc - 1);
	
	TIM3->CCR1 = (uint32_t) (ticks_per_phase - acq->demod_deadtime_cyc - 1);
	TIM3->CCR3 = (uint32_t) (ticks_per_phase - 1);
	TIM3->CCR4 = (uint32_t) ((2 * ticks_per_phase) - acq->demod_deadtime_cyc - 1);
	
	TIM4->CCR3 = ticks_per_phase * acq->mod_cycles_per_cds;
	TIM4->CCR4 = ticks_per_phase * acq->mod_cycles_per_cds;
	
	TIM5->CCR1 = (uint32_t) (acq->settle_time_us * clkfreq_mhz); 
	
		/* Calculate number of CNV pulses per cycle */
	blocks_per_phase = (uint16_t) (ticks_per_phase/ticks_per_block); // Calculate number of blocks that will fit
	acq->cnv_cycles = blocks_per_phase << acq->log2SampAvg; // Multiply number of blocks by number of samples per block
	acq->blocks_per_cycle = 2 * blocks_per_phase; // Convert blocks per phase to blocks per cycle for external use
	
	TIM8->RCR = acq->cnv_cycles - 1; // Update TIM8->RCR
	TIM8->ARR = ticks_per_sample - 1;
	TIM8->CCR1 = ticks_per_sample - 12U; // 60 ns pulse (must be greater than 1/f_osc to 
										// ensure flip flop triggers).
	tim15_config(acq->mod_cycles_per_avg);
	
	acq->flags |= ACQ_FLAG_PARAM_SETUP;
}


		/************************************************
		 * 												*
		 * 		CDS/Mod Phase-Related Functions			*
		 * 												*
		 * **********************************************/

/// @brief Unlinks modulator/demodulator from timer to enable user-defined states
/// @param acq AcqParam_t container for the acquisition parameters and data
void gpio_mod_clocks(AcqParam_t * acq)
{
	acq->flags |= ACQ_FLAG_GPIO_MOD;
	
	GPIO_Init_TypeDef init = {
		.mode = GPIO_OUTPUT,
		.otype = GPIO_PUSH_PULL,
		.ospeed = GPIO_SPEED_MED,
		.pupd = GPIO_NO_PUPD
	};

	gpio_init_pin(TIM2_CH1, &init);
	gpio_init_pin(TIM2_CH3, &init);
	gpio_init_pin(TIM3_CH1, &init);
	gpio_init_pin(TIM3_CH3, &init);
}

/// @brief Links modulator/demodulator to timers for normal chopper behavior
/// @param acq AcqParam_t container for the acquisition parameters and data
void tim_mod_clocks(AcqParam_t * acq)
{
	acq->flags &= ~ACQ_FLAG_GPIO_MOD;
	
	GPIO_Init_TypeDef init = {
		.mode = GPIO_AF,
		.otype = GPIO_PUSH_PULL,
		.ospeed = GPIO_SPEED_MED,
		.pupd = GPIO_NO_PUPD
	};

	gpio_init_pin(TIM2_CH1, &init);
	gpio_init_pin(TIM2_CH3, &init);
	gpio_init_pin(TIM3_CH1, &init);
	gpio_init_pin(TIM3_CH3, &init);

	gpio_config_af(TIM2_CH1, TIM2_CH1_AF);
    gpio_config_af(TIM2_CH3, TIM2_CH3_AF);
    gpio_config_af(TIM3_CH1, TIM3_CH1_AF);
    gpio_config_af(TIM3_CH3, TIM3_CH3_AF);
}

/// @brief Unlinks CDS switches from timers to allow user-defined states
/// @param acq AcqParam_t container for the acquisition parameters and data
void gpio_cds_clocks(AcqParam_t * acq)
{
	acq->flags |= ACQ_FLAG_GPIO_CDS;

	GPIO_Init_TypeDef init = {
		.mode = GPIO_OUTPUT,
		.otype = GPIO_PUSH_PULL,
		.ospeed = GPIO_SPEED_MED,
		.pupd = GPIO_NO_PUPD
	};

	gpio_init_pin(TIM4_CH3, &init);
    gpio_init_pin(TIM4_CH4, &init);
}

/// @brief Links CDS switches to timers for normal reversal to null ADC offsets
/// @param acq AcqParam_t container for the acquisition parameters and data
void tim_cds_clocks(AcqParam_t * acq)
{
	acq->flags &= ~ACQ_FLAG_GPIO_CDS;

	GPIO_Init_TypeDef init = {
		.mode = GPIO_AF,
		.otype = GPIO_PUSH_PULL,
		.ospeed = GPIO_SPEED_MED,
		.pupd = GPIO_NO_PUPD
	};	

    gpio_init_pin(TIM4_CH3, &init);
    gpio_init_pin(TIM4_CH4, &init);
    gpio_config_af(TIM4_CH3, TIM4_CH3_AF);
    gpio_config_af(TIM4_CH4, TIM4_CH4_AF);
}

/// @brief Allows user to define modulator phase when in GPIO control
/// @param acq AcqParam_t container for the acquisition parameters and data
/// @param phase State to apply to the modulator
void set_mod_phase(AcqParam_t * acq, ModPhase_t phase)
{
	if(acq->flags & ACQ_FLAG_GPIO_MOD)
	{
		gpio_set_state(TIM2_CH1, (PinState_t) phase == MOD_PHASE_0);
		gpio_set_state(TIM2_CH3, (PinState_t) phase == MOD_PHASE_1);
		gpio_set_state(TIM3_CH1, (PinState_t) phase == MOD_PHASE_0);
		gpio_set_state(TIM3_CH3, (PinState_t) phase == MOD_PHASE_1);

		acq->flags &= ~ACQ_FLAG_GPIOMODPOL;
		acq->flags |= ACQ_FLAG_GPIOMODPOL * (uint16_t) phase;
		
	}
}

/// @brief Allows user to define CDS switch positions when in GPIO control
/// @param acq AcqParam_t container for the acquisition parameters and data
/// @param phase (CDSPhase_t) States of both swiches to apply
void set_cds_phase(AcqParam_t * acq, CDSPhase_t phase)
{
	if(acq->flags & ACQ_FLAG_GPIO_CDS)
	{
		uint8_t sw1_phase = (phase & (1U << SW1_Pos)) >> SW1_Pos;
		uint8_t sw2_phase = (phase & (1U << SW2_Pos)) >> SW2_Pos;

		gpio_set_state(TIM4_CH3, (PinState_t) sw1_phase);
		gpio_set_state(TIM4_CH4, (PinState_t) sw2_phase);

	}
}

ModPhase_t get_mod_phase(void)
{
	return gpio_get_state(TIM2_CH1) == GPIO_STATE_HI ? MOD_PHASE_0 : MOD_PHASE_1;
}

/// @brief Gets the current CDS phase by polling the GPIO states of the switches
/// @param none
/// @return CDSPhase_t with the state of both switches
CDSPhase_t get_cds_phase(void)
{
	uint8_t phase = 0;
	if(gpio_get_state(TIM4_CH3) == GPIO_STATE_HI) phase |= (1U << SW1_Pos);
	if(gpio_get_state(TIM4_CH4) == GPIO_STATE_HI) phase |= (1U << SW2_Pos);

	return (CDSPhase_t) phase;
}

/// @brief Converts a CDSPhase_t with switch states to a 
/// @param phase 
/// @return 
static int16_t convert_cds_phase_to_multiplier(CDSPhase_t phase)
{
	int16_t mult = 1;

	if(phase == SW1_IN_SW2_CM) mult = -1;

	return mult;
}

static int16_t get_cds_phase_multiplier(void)
{
	return convert_cds_phase_to_multiplier(get_cds_phase());
}


		/************************************************
		 * 												*
		 * 			Gain-Related Functions				*
		 * 												*
		 * **********************************************/

/// @brief Sets gain switches and updates gain settings
/// @param acq AcqParam_t container of acquisition parameters and intermediate values
/// @param gain (GainState_t) gain to be set
void set_gain(AcqParam_t * acq, GainState_t gain)
{
	// Set gain switches
	gpio_set_state(GAIN_40_DB_Pin, (PinState_t) (gain == GAIN_STATE_LO));
	gpio_set_state(GAIN_60_DB_Pin, (PinState_t) (gain == GAIN_STATE_HI));

	// Recalculate V_os DAC code deadband
	set_code_deadband(acq);
	acq->gain_state = gain;
}

/// @brief Updates the code deadband where no change to the Vos DAC code will be applied
/// @param acq AcqParam_t container of acquisition parameters and intermediate values
static void set_code_deadband(AcqParam_t * acq)
{
	float lsb_size_nV = (float) (2 * acq->acq_const->v_ref/AD403X_CODE_SPAN);
	lsb_size_nV *= 1E9/((float) get_analog_gain(acq));


	acq->code_deadband = (int16_t) (acq->Vos_dac_deadband_nV / lsb_size_nV);
}

double get_analog_gain(AcqParam_t * acq)
{
	return (acq->gain_state == GAIN_STATE_LO) ? acq->acq_const->gain_lo : acq->acq_const->gain_hi;
}

/// @brief Saves the current vavg as a null value to enable null compensation
/// @param acq - AcqParam_t container of acquisition parameters and data
void set_null(AcqParam_t * acq, double v_avg)
{
	if(acq->gain_state == GAIN_STATE_HI) acq->acq_const->v_null_hi = v_avg;
	else	acq->acq_const->v_null_lo = v_avg;
}

/// @brief Subtracts a user-saved null value from the reading
/// @param acq - AcqParam_t container of acquisition parameters and data
/// @return Null-compensated v_avg
double subtract_null(AcqParam_t * acq, double v_avg)
{
	double compVavg;
	if(acq->gain_state == GAIN_STATE_HI) compVavg = v_avg - acq->acq_const->v_null_hi; 
	else	compVavg = v_avg - acq->acq_const->v_null_lo; 
	
	return compVavg;
}

		/************************************************
		 * 												*
		 * 			 Data Processing Functions			*
		 * 												*
		 * **********************************************/

/// @brief Checks for ADC block sync errors at mod switch transitions
/// @param None 
/// @return BLOCK_NO_ERROR if no errors, BLOCK_SYNC_ERROR if a synchronizatino error was found
/// @note Checks if the ADC BUSY pin remains high over a modulator switch transition, which
/// @note would indicate the ADC is averaging values from both modulator switch states.
inline BlockErr_t check_block_sync(void)
{
	return (BlockErr_t) (GPIOA->IDR & GPIO_IDR_ID0);
}

/// @brief Checks overrange bit from raw ADC data
/// @param data - AD403XData_t of the ADC data 
/// @return BLOCK_NO_ERROR if no overranges, BLOCK_OVERRANGE_ERROR if overranges detected
BlockErr_t check_overrange(const AD403XData_t * data)
{
	BlockErr_t status = BLOCK_NO_ERROR;
	
	for(uint16_t i = 0; i < data->bufsize; i++){
		status |= (BlockErr_t) (data->buf[i] & (uint32_t) BLOCK_OVERRANGE_ERROR);
	}
	
	return status;
}

/// @brief Averages the elements in an array of data 
/// @param data - AD403XData_t of the ADC data 
/// @return int32_t of the average value of the elements of the array 
int32_t get_code_average(const AD403XData_t * data)
{
	int64_t avg = data->buf[0];
	for(uint32_t i = 1; i < data->bufsize; i++){
		avg += data->buf[i];
	}
	
	avg /= data->bufsize;
	avg *= (int64_t) data->phase[0];
	return (int32_t) avg;
}

/// @brief Calculates the offset in a modulator cycle
/// @param data AD403XData_t of the ADC data 
/// @return int32_t of the offset between phases in the modulator cycle (in codes)
int32_t get_code_offset(const AD403XData_t * data)
{
	int32_t offset = 0;
	
	for(uint32_t i = 0; i < data->bufsize/2; i++){
		offset += data->buf[i] - data->buf[i + data->bufsize/2];
	}
	
	offset /= data->bufsize;
	offset *= (int32_t) data->phase[0];
	return offset;
}

/// @brief Updates the phase information in the AD403XData_t type
/// @param data AD403XData_t container for ADC data
/// @note Because data may be processed after a switch transition, the phase data for 
/// @note the next block is taken from GPIO states, and the values are shifted over.
/// @note As such, for the phase data to be accurate, this function must be called
/// @note for each cycle or the phase data may become stale.
static void ad403x_data_update_phase(AD403XData_t * data)
{
	data->phase[0] = data->phase[1];
	data->phase[1] = (int8_t) get_cds_phase_multiplier();
}

/// @brief Converts ADC code to volts using code span and frontend gain
/// @param acq AcqParam_t container of acquisition parameters and data
/// @param code ADC code
/// @return Double precision floating point representation of input voltage 
double adc_code_to_volts(AcqParam_t * acq, int64_t code)
{
	return (double) code / (AD403X_CODE_SPAN * get_analog_gain(acq));
}

/// @brief Processes data from one full modulator cycle to extract average and offset information
/// @param acq AcqParam_t container of acquisition parameters and data
/// @note Calculated v_avg is stored in the AcqParam_t container through update of the 
/// @note SincFilter_t element. Offset information is stored in acq->offset_accum.
void process_data_cycle(AcqParam_t * acq)
{
	if(check_overrange(acq->adc_data)) acq->flags |= ADC_OVERRANGE_FLAG;
	
	int64_t avg_val = get_code_average(acq->adc_data)/4;
	sinc_update_integrators(acq->sinc, avg_val);

	acq->offset_accum += get_code_offset(acq->adc_data)/4;
	acq->offset_counter++;

	ad403x_data_update_phase(acq->adc_data);
}

/// @brief Calculates code increment to apply to the V_os DAC to null the input offset voltage
/// @param acq AcqParam_t container of acquisition parameters and data
/// @return vos_dac_increment (-1, 0, or 1) to add to the V_os DAC code
/// @note Intended usage: 		vos_dac_code += calculate_vos_dac_increment(&acq1);
/// @note DAC code Overflow/underflow checks must be performed outside this function 
int16_t calculate_vos_dac_increment(AcqParam_t * acq)
{
	int16_t vos_dac_increment = 0;

	if((acq->offset_counter >= acq->mod_cycles_per_update) && !(acq->flags & SKIP_VOS_DAC_UPDATE_FLAG))
	{
		acq->offset_accum /= acq->mod_cycles_per_update;
		if(acq->offset_accum > acq->code_deadband) vos_dac_increment++;
		if(acq->offset_accum < (-1 * acq->code_deadband)) vos_dac_increment--;
		
		acq->v_os = (float) adc_code_to_volts(acq, (int64_t) acq->offset_accum);
		acq->offset_accum = 0;
		acq->offset_counter = 0;
	}

	return vos_dac_increment;
}

/// @brief Convenience function that outputs scaled voltage averaged over an averaging cycle
/// @param acq AcqParam_t container of acquisition parameters and data
/// @return Scaled voltage
/// @note Must be invoked only once after getting data from an entire block because
/// @note the function modifies the state of the SincFilter_t * acq->sinc.
double get_block_v_avg(AcqParam_t * acq)
{
	int64_t code_filtered = sinc_update_combs(acq->sinc);
	sinc_reset_filter(acq->sinc);
	
	return adc_code_to_volts(acq, code_filtered);
}

		/************************************************
		 * 												*
		 * 			 Miscellaneous Functions			*
		 * 												*
		 * **********************************************/


/// @brief Queues a data write to the AD5686
/// @param code - data to write to the AD5686
void queue_dac_write(uint32_t * code)
{
	dma_ch1_lli[1].CSAR = (uint32_t *) code;
	dma_set_next_node(GPDMA1_Channel1, &dma_ch1_lli[1]);
}

/// @brief Sets relays to default states (K1R, K2S, K3S)
/// @param None
void set_relay_defaults(void)
{
	gpio_set_pin(K1_R);
	gpio_set_pin(K2_S);
	gpio_set_pin(K3_R);
	
	TIM7->CR1 |= TIM_CR1_CEN; // Enable TIM7 for 5 ms delay
}
