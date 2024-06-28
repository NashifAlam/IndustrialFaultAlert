//seg.c
#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "seg_defines.h"

cu8 segLUT[10]=
{
	0xc0,0xF9,0xa4,0xb0,0x99,
	0x92,0x82,0xf8,0x80,0x90
};


void Init_7segs()
{
  //cfg p0.8 to p0.15 as gpio out for
	//cfg comm's for ca7seg_2_mux as gpio out
	IODIR0|=0xFF<<SEG|1<<CA1|1<<CA2;
}

void disp_2_mux_segs(u8 t)
{
		
			IOPIN0=(segLUT[t/10])<<SEG;
			IOSET0=1<<CA1;
			delay_ms(1);
			IOCLR0=1<<CA1;

			//write to data pins
			IOPIN0=segLUT[t%10]<<SEG;
			//turn on seg2
			IOSET0=1<<CA2;
			//on time
			delay_ms(1);
			//turn of seg2
			IOCLR0=1<<CA2;		
}


