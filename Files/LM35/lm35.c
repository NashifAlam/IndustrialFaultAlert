//lm35.c
#include "adc.h"
#include "types.h"

u8 ReadTempLM35(u8 chNo)
{
	f32 eAR;
	eAR=Read_ADC(chNo) * 100;
	return eAR;
}
