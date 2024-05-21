


#ifndef SINC_H_
#define SINC_H_

#include <stdint.h>

#define MAX_SINC_ORDER					3

typedef struct{
	int64_t integrators[2 * MAX_SINC_ORDER];
	int64_t combs[2 * MAX_SINC_ORDER];
	uint32_t counter;
	uint16_t order;
} SincFilter_t;

void sinc_update_integrators(SincFilter_t * sinc, int64_t input);
int64_t sinc_update_combs(SincFilter_t * sinc);
void sinc_reset_filter(SincFilter_t * sinc);
void sinc_set_order(SincFilter_t * sinc, uint16_t order);

#endif // SINC_H_
