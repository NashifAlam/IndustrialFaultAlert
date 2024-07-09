#include "defines.h"
#include "pin.h"

void init_MQ2(void)
{
	IODIR0 |= 1 << MQ2PIN;
}
int smokeSensorReading(void)
{
	if(READBIT(IOSET0,MQ2PIN)== 1)
		return 1;
	 
	return 0;
}
