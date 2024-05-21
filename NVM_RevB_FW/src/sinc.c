

#include "sinc.h"


void sinc_set_order(SincFilter_t * sinc, uint16_t order)
{
	sinc->order = order;
}

/// @brief Updates integrators in a cascaded integrator-comb sinc filter, increments counter
/// @param sinc - SincFilter_t container for the filter data
/// @param input - value to input to the filter
void sinc_update_integrators(SincFilter_t * sinc, int64_t input)
{
	if((sinc->order < 1) || sinc->order > 3) sinc->order = 1;
	for(uint8_t i = 0; i < 2*sinc->order; i += 2)
	{
		sinc->integrators[i] = sinc->integrators[i + 1];
		sinc->integrators[i + 1] += input;
		input = sinc->integrators[i + 1];
	}
	sinc->counter++;
}

/// @brief Updates combs in a cascaded integrator-comb sinc filter, resets counter
/// @param sinc SincFilter_t container for the filter data
/// @return output of the filter
int64_t sinc_update_combs(SincFilter_t * sinc)
{
	int64_t carry = sinc->integrators[sinc->order * 2 - 1];
	int64_t divisor = 1;
	for(uint8_t i = 0; i < sinc->order*2; i+=2)
	{
		sinc->combs[i] = sinc->combs[i+1];
		sinc->combs[i+1] = carry;
		carry = sinc->combs[i+1] - sinc->combs[i];
		divisor *= sinc->counter;
	}
	sinc->counter = 0;
	return carry/divisor;
}

/// @brief Updates combs in a cascaded integrator-comb sinc filter, resets counter
/// @param sinc SincFilter_t container for the filter data
/// @return (double) output of the filter
double sinc_update_combs_ret_fp(SincFilter_t * sinc)
{
	int64_t carry = sinc->integrators[sinc->order * 2 - 1];
	int64_t divisor = 1;
	for(uint8_t i = 0; i < sinc->order*2; i+=2)
	{
		sinc->combs[i] = sinc->combs[i+1];
		sinc->combs[i+1] = carry;
		carry = sinc->combs[i+1] - sinc->combs[i];
		divisor *= sinc->counter;
	}
	sinc->counter = 0;
	double output = (double) carry;
	return output/divisor;
}

/// @brief Zeros the integrators, combs, and counter of a sinc filter
/// @param sinc - SincFilter_t container for the filter data
void sinc_reset_filter(SincFilter_t * sinc)
{
	sinc->counter = 0;
	for(uint8_t i = 0; i < 2 * MAX_SINC_ORDER; i++)
	{
		sinc->integrators[i] = 0;
		sinc->combs[i] = 0;
	}
}

void sinc_reset_counter(SincFilter_t * sinc)
{
	sinc->counter = 0;
}
