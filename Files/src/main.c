#include "header.h"

main()
{
	int curTemp	= 0;					  //ADC
	int tempMax = readThresholdMax();	  //EEPROM
	int tempMin = readThresholdMin();  	  //EEPROM
	int smokeDetected = 0;				  //I/O Smoke sensor
	
	IODIR0 = GREENLED | REDLED; 
	Enable_EINT0();
	//LCDStart();	 
	
	

	while(1)
	{
		//curTemp = readTemp();			
		//smokeDetected = smokeSensorReading();
		
		if(smokeDetected || (curTemp < tempMin)||(curTemp > tempMax))
		{
			Alert();
		}
		delay_ms(500);
	}
}
