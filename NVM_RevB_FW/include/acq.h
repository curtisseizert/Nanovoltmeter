	/** acq.h
	 * 	Header file for high-level acquisition functions for NVM Rev B
	*/

#ifndef ACQ_H_
#define ACQ_H_

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "sys_cfg.h"
#include "stdint.h"
#include "ad403x.h"
#include "sinc.h"

#define ACQ_FLAG_GPIO_CDS				(1UL << 0)
#define ACQ_FLAG_GPIOCDS_SW1			(1UL << 1)
#define ACQ_FLAG_GPIOCDS_SW2			(1UL << 2)
#define ACQ_FLAG_GPIO_MOD				(1UL << 3)
#define ACQ_FLAG_GPIOMODPOL				(1UL << 4)
#define ACQ_FLAG_PARAM_SETUP			(1UL << 5)
#define ACQ_FLAG_MODTIMRDY				(1UL << 6)
#define ACQ_FLAG_MOD_ON					(1UL << 7)
#define ACQ_FLAG_GPIOMOD_SET			(1UL << 8)
#define ACQ_FLAG_GPIOCDS_SET			(1UL << 9)

#define RELAY_K1_SET					(1UL << 1)
#define RELAY_K2_SET					(1UL << 2)
#define RELAY_K3_SET					(1UL << 3)

#define OVERRANGE_FLAG					1UL << 10
#define ADC_OVERRANGE_FLAG				1UL << 11
#define HI_GAIN_FLAG					1UL << 12
#define SEND_UART_FLAG					1UL << 13
#define SKIP_VOS_DAC_UPDATE_FLAG		1UL << 14
#define BLOCK_SYNC_ERROR_FLAG			1UL << 15 // If ADC blocks are not aligned with mod cycles
#define NULL_ENABLE						1UL << 16
#define ACQ_FLAG_SET_NULL				1UL << 17

#define AD403X_MAX_ARRAY_LEN			512

#define DATA_FLAG_DATA_INVALID			(1U << 0)
#define DATA_FLAG_WAIT_FOR_CYCLE		(1U << 1)

#define AD403X_CODE_SPAN				(1UL << 30)

typedef struct{
	int32_t buf[AD403X_MAX_ARRAY_LEN];
	uint16_t index;
	uint16_t bufsize;
	int16_t phase[2];		// phase[1] gets copied to phase[0] when block
							// is processed
}AD403XData_t;

typedef struct{
	double v_null_lo;
	double v_null_hi;
	double v_ref;
	double gain_lo;
	double gain_hi;
}AcqConst_t;

typedef enum{
	GAIN_STATE_LO,
	GAIN_STATE_HI
}GainState_t;

/// @brief Struct containing the parameters for an acquisition
typedef struct{
	AcqConst_t * acq_const;
	SincFilter_t * sinc;
	AD403XData_t * adc_data;
	const AD403X_t * adc;

	int32_t mod_deadtime_cyc;
	int32_t demod_deadtime_cyc;
	uint32_t adc_samp_freq;
	int32_t offset_accum;
	uint32_t flags;
	
	float mod_freq; 
	float mod_deadtime_us;
	float demod_deadtime_us;
	float settle_time_us;
	float Vos_dac_deadband_nV;
	float v_os;

	uint16_t offset_counter;
	uint16_t index; 
	uint16_t code_deadband;			// 
	uint16_t mod_cycles_per_avg;	// number of modulator cycles per average value
	uint16_t mod_cycles_per_update; // number of modulator cycles per Vos DAC update
	uint16_t mod_cycles_per_cds;	// number of modulator cycles per ADC input reversal
	uint16_t log2SampAvg;
	uint16_t cnv_cycles;
	uint16_t blocks_per_cycle;
	
	uint16_t relay_states;
	uint16_t array_size;

	uint16_t sinc_order;

	GainState_t gain_state;
	
}AcqParam_t;

typedef enum{
	MOD_PHASE_0		= 0,
	MOD_PHASE_1		= 1
} ModPhase_t;

#define SW1_Pos 	0
#define SW2_Pos		1

typedef enum{
	SW1_CM_SW2_CM	= 0,
	SW1_IN_SW2_CM	= (1U << SW1_Pos),
	SW1_CM_SW2_IN	= (1U << SW2_Pos),
	SW1_IN_SW2_IN	= (1U << SW1_Pos) | (1U << SW2_Pos)
} CDSPhase_t;

typedef enum{
	BLOCK_NO_ERROR			= 0,
	BLOCK_SYNC_ERROR		= 1,
	BLOCK_OVERRANGE_ERROR	= 2,
	BLOCK_SYNC_OVR_ERROR	= 3
} BlockErr_t;

	// HIGH LEVEL FUNCTIONS
void setup_acquisition(AcqParam_t * acq);
void start_acquisition(AcqParam_t * acq);
void pause_acquisition(AcqParam_t * acq);
void pause_acquisition_diagnostic(AcqParam_t * acq);

	// SWITCH STATE-RELATED FUNCTIONS
void gpio_mod_clocks(AcqParam_t * acq);
void gpio_cds_clocks(AcqParam_t * acq);
void set_mod_phase(AcqParam_t * acq, ModPhase_t phase);
void set_cds_phase(AcqParam_t * acq, CDSPhase_t phase);
void tim_mod_clocks(AcqParam_t * acq);
void tim_cds_clocks(AcqParam_t * acq);
ModPhase_t get_mod_phase(void);
CDSPhase_t get_cds_phase(void);

	// GAIN-RELATED FUNCTIONS
void set_gain(AcqParam_t * acq, GainState_t gain);
double get_analog_gain(AcqParam_t * acq);
float getLSBSize_nV(double gain);

	// NULL COMPENSATION FUNCTIONS
void set_null(AcqParam_t * acq, double v_avg);
double subtract_null(AcqParam_t * acq, double v_avg);

	// DATA PROCESSING FUNCTIONS
double get_block_v_avg(AcqParam_t * acq);
double adc_code_to_volts(AcqParam_t * acq, int64_t code);
void process_data_cycle(AcqParam_t * acq);
int16_t calculate_vos_dac_increment(AcqParam_t * acq);
double get_block_v_avg(AcqParam_t * acq);
inline BlockErr_t check_block_sync(void);
int32_t get_code_average(const AD403XData_t * data);
int32_t get_code_offset(const AD403XData_t * data);

	// MISCELLANEOUS FUNCTIONS
void queue_dac_write(uint32_t * code);

#endif // ACQ_H_
