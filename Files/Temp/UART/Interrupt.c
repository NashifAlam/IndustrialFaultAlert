#include "pin.h"
#include "defines.h"
#include "functions.h"
	 	
#define CFGPIN(WORD,PIN,FUNC) \
        WORD=((PIN<16) ? \
             ((WORD&~(3<<(PIN*2)))|(FUNC<<(PIN*2))): \
             ((WORD&~(3<<((PIN-16)*2)))|(FUNC<<((PIN-16)*2))));
				

unsigned int count;

//#define EINT0_LED 1

void eint0_isr(void) __irq
{
//	CPLBIT(IOPIN1,EINT0_LED);//isr activity
	LCDStart();
	SCLRBIT(EXTINT,0);//clear flag
	VICVectAddr=0;//dummy write;
}	

void Enable_EINT0(void)
{
	//CFGPIN(PINSEL0,1,FUNC4);
	CFGPIN(PINSEL1,0,INTERSWITCH);
//	SETBIT(IODIR1,EINT0_LED);
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
