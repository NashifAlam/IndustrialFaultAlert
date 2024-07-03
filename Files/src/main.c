#include "header.h"

main()
{
	int curTemp	= 0;					  //ADC
	int tempMax = readThresholdMax();	  //EEPROM
	int tempMin = readThresholdMin();  	  //EEPROM
	int smokeDetected = 0;				  //I/O Smoke sensor
	
	IODIR0 = GREENLED | REDLED; 
	
	//LCDStart();	 
	InitLCD();
	Enable_EINT0();
	
	while(1)
	{
		//curTemp = readTemp();			
		//smokeDetected = smokeSensorReading();
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD(" Sensor Reading");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD(" ACTIVE");

		if(smokeDetected || (curTemp < tempMin)||(curTemp > tempMax))
		{
			Alert();
		}
		delay_ms(500);
	}
}
