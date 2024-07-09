#include <LPC21xx.h>
#include "delay.h"
#include "types.h"
#include "adc_defines.h"
#include "defines.h"
#include "pin.h"

void Init_ADC(void)
{
	//cfg i/o pin p0.27 for analog input (AIN0)
	//default pin p0.27 is cfgd as AIN0 
	//cfg ADCR to make ADC operational with
	//required sampling rate
	//PINSEL1 |= (0x01 << ADCPIN); //Check out SDC func
	ADCR=((PDN_BIT)|(CLKDIV<<8));
}

f32  Read_ADC(u32 chNo)
{
	u32 adcV;	f32 eAR;
	//start adc with channel no
	ADCR&=0xFFFFFF00;
	ADCR|=(1<<ADC_START_BIT)|(1<<chNo);
	//wait for >= recommended time
	delay_us(3);
	//check until conversion completed 
	while(READBIT(ADDR,DONE_BIT)==0);
	CLRBIT(ADCR,ADC_START_BIT);
	//read converted digital 10-bit data;
    adcV=((ADDR>>RESULT_BITS)&0x3FF);
	//interpret using step size
	eAR=(adcV*(3.3/1023));
	return eAR;
}

