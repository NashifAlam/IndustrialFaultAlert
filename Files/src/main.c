#include "header.h"

int interruptFlag = 0; 
  
//EEPROM
#define I2CPINS 0x00000050
//Interrupt
//0x15400001 
#define PININTERRUPT  0x15400001
main()
{
	int curTemp	= 0;					  //ADC
	int tempMax = readThresholdMax();	  //EEPROM
	int tempMin = readThresholdMin();  	  //EEPROM
	int smokeDetected = 0;				  //I/O Smoke sensor
	//s8 Min[4], Max[4];
	IODIR0 |= 1 << GREENLED; 
	IODIR0 |= 1 << REDLED; 
	
	//itoa(tempMax, Max, 10);
	//itoa(tempMin, Min, 10);
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
		 Alert();
		//CmdLCD(GOTO_LINE2_POS0+8);
		//StrLCD(Max);
		if(smokeDetected || (curTemp < tempMin)||(curTemp > tempMax))
		{
				//Alert();
				//delay_ms(100);
		}  
			
		delay_s(1);
	 /**/
		  
		/*
		if(interruptFlag == 1)
		{
			//LCDStart();
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Interrupt Hit !!");
			delay_s(3);
			CmdLCD(CLEAR_LCD);
			interruptFlag = 0; 

		}
		else
		{
			//curTemp = ReadTempLM35(0x02);
	
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Interrupt Not !!");
			delay_s(2);
			CmdLCD(CLEAR_LCD) */
			
	}
}
