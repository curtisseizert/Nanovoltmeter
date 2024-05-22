

    /* acq_private.h */
    /* Header for static declarations defined in acq.c */

#ifndef ACQ_PRIVATE_H_
#define ACQ_PRIVATE_H_

#include "acq.h"

static int16_t cds_state_setting_mismatch(AcqParam_t * acq);
static int16_t mod_state_setting_mismatch(AcqParam_t * acq);

static void disable_mod_timers(void);
static void init_mod_timers(AcqParam_t * acq);

static void timer_config(AcqParam_t * acq);
static void ad403x_set_acquisition_param(AcqParam_t * acq);
static void set_code_deadband(AcqParam_t * acq);

static int16_t convert_cds_phase_to_multiplier(CDSPhase_t phase);
static int16_t get_cds_phase_multiplier(void);

#endif
