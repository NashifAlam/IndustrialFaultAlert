#include <lpc21xx.h>
#include "pin_function_defines.h"
#include "defines.h"

#define EINT0_LED 16

void eint0_isr(void) __irq;
void Enable_EINT0(void);

unsigned int count;

main()
{
	Enable_EINT0();
	while(1)
	{
		count++;
  }		
}

void eint0_isr(void) __irq
{
	CPLBIT(IOPIN1,EINT0_LED);//isr activity
	SCLRBIT(EXTINT,0);//clear flag
	VICVectAddr=0;//dummy write;
}	

void Enable_EINT0(void)
{
	//CFGPIN(PINSEL0,1,FUNC4);
	CFGPIN(PINSEL1,0,FUNC2);
	SETBIT(IODIR1,EINT0_LED);
	SSETBIT(VICIntEnable,14);
	VICVectCntl0=0x20|14;
	VICVectAddr0=(unsigned)eint0_isr;
	
	//Enable EINT0 
	//SSETBIT(EXTINT,0) //default
	
	//EINT0 as EDGE_TRIG
  SETBIT(EXTMODE,0);
	//EINT0 as REDGE
  SETBIT(EXTPOLAR,0);	
}	
