#include "types.h"

void delay_us(u32 dlyUS)
{
	dlyUS*=12;
	while(dlyUS--);
}

void delay_ms(unsigned int dlyMS)
{
  int i;
  for(;dlyMS>0;dlyMS--)
  {
		for(i=12000;i>0;i--);
  }		
}
