#include "header.h"

int interruptFlag = 0; 

float curTemp	= 0;					  //ADC
int tempMax = 0, tempMin = 0; 


main()
{
					 
	InitLCD(); 
	Enable_EINT0();
	IODIR0 |= 1 << GREENLED;
	IODIR0 |= 1 << REDLED; 

	Init_UART0();
	Init_ADC();
	init_MQ2();
	init_i2c();
	tempMax = readThresholdMax();	  //EEPROM
	tempMin = readThresholdMin();  	  //EEPROM
					  //I/O Smoke sensor

	while(1)
	{
		curTemp = ReadTempLM35(0x01);			
		//smokeDetected = smokeSensorReading();
		
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Temp : ");
		CmdLCD(GOTO_LINE1_POS0+7);
		F32LCD(curTemp,2);
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("MIN:");
		CmdLCD(GOTO_LINE2_POS0 +4);
		U32LCD(tempMin);
		CmdLCD(GOTO_LINE2_POS0 +8);
		StrLCD("MAX:");
		CmdLCD(GOTO_LINE2_POS0+12);
		U32LCD(tempMax);
			//curTemp = ReadTempLM35(0x02);

		//CmdLCD(CLEAR_LCD);
		if(smokeSensorReading())
		{
			//Alert();
			RedLED(1);
			Alert(0);
			RedLED(0);
			delay_s(3);

		} 
		else if(curTemp < tempMin)
		{
		 	RedLED(1);
			Alert(1);
			RedLED(0);
			delay_s(3);
		}
		else if(curTemp > tempMax)
		{
			RedLED(1);
			Alert(2);
			RedLED(0);
			delay_s(3);
		}
		else
		{
			GreenLED(1);
			delay_ms(800);
			GreenLED(0);
		}
		
		delay_ms(1000);
	 
		
	}
}
