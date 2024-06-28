#include <LPC21xx.h>
#include "functions.h"

main()
{
	int curTemp	= 0;
	int tempMax = readThresholdMax();
	int tempMin = readThresholdMin();  
	int smokeDetected = 0;
	
	while(1)
	{
		//curTemp = readTemp();
			
		//smokeDetected = smokeSensorReading();
		if(smokeDetected || (curTemp < tempMin)||(curTemp > tempMax))
		{
			Alert();
		}
	}
}
