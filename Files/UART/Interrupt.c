#include "pin.h"
#include "defines.h"
#include "functions.h"
#include "LED.h"
#include "delay.h"
	 	
/*#define CFGPIN(WORD,PIN,FUNC) \
        WORD=((PIN<16) ? \
             ((WORD&~(3<<(PIN*2)))|(FUNC<<(PIN*2))): \
             ((WORD&~(3<<((PIN-16)*2)))|(FUNC<<((PIN-16)*2))));
*/				


extern int interruptFlag;
unsigned int count;

//#define EINT0_LED 1

void eint0_isr(void) __irq
{
	//CPLBIT(IOPIN0,EINT0_LED);//isr activity
	//LCDStart();
	interruptFlag = 1;
	irr();
	checkPassword();
	delay_ms(2);
	SCLRBIT(EXTINT,0);//clear flag
	VICVectAddr=0;//dummy write;	
	interruptFlag = 0;	   
}	

void Enable_EINT0(void)
{
	PINSEL1 |=  PININTERRUPT;
	//0x15400000;
	//CFGPIN(PINSEL0,1,FUNC4);
	//CFGPIN(PINSEL0,INTERSWITCH,2);
//	SETBIT(IODIR1,EINT0_LED);
	VICVectAddr0=(unsigned)eint0_isr;
	VICVectCntl1=0x20|14;
	SSETBIT(VICIntEnable,14);
	
	
	//Enable EINT0 
	//SSETBIT(EXTINT,0) //default
	   SCLRBIT(EXTINT,0);	

	//EINT0 as EDGE_TRIG
  SETBIT(EXTMODE,0);
	//EINT0 as REDGE
  //SETBIT(EXTPOLAR,0);	
}	
