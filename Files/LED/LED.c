#include <LPC21xx.h>
#include "pin.h"

void RedLED(short int status)
{

	if(status) IOSET0 |= 1 << REDLED;
	else IOCLR0 |= 1 <<REDLED;
	 
	return;
}
void GreenLED(short int status)
{
	
	if(status) IOSET0 |= 1 << GREENLED;
	else IOCLR0 |= 1 << GREENLED;
	 
	return;
}
