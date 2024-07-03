#include <LPC21xx.h>
#include "pin.h"

void RedLED(short int status)
{
	if(status) IOSET0 = REDLED;
	else IOCLR0 = REDLED;
	 
	return;
}
void GreenLED(short int status)
{
	if(status) IOSET0 = GREENLED;
	else IOCLR0 = GREENLED;
	 
	return;
}
