#include "dac.h"

void DACInit(void)
{
   
  DAC1->MCR |= (2U << DAC_MCR_MODE1_Pos);
	
	DAC1->CR |= DAC_CR_EN1;
	
	DAC1->DHR12R1 |= (DAC1_DEFAULT_OUTPUT << DAC_DHR12R1_DACC1DHR_Pos);
	DAC1->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
	
}
