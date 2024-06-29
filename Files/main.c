#include "header.h"



main()
{
	int curTemp	= 0;					  //LM35.c
	int tempMax = readThresholdMax();	  //eeprom.c
	int tempMin = readThresholdMin();  	  //eeprom.c
	int smokeDetected = 0;				  //MQ2.c  I/O Smoke sensor 
 	
	while(1)
	{
		//curTemp = readTemp();
		//smokeDetected = smokeSensorReading();
		if(smokeDetected || (curTemp < tempMin) || (curTemp > tempMax))
		{
			Alert();				//function.c RED ON, Broadcast, Send SMS
		}
	}

	if(OnUARTInterrput())
	{
		readMessage();					//GSM.c 	Read from GSM using uart
		verifyMessage();				//GSM.c 	Check the message
		WriteThreholdEEPROM(); 			//eeprom.c 	I2C write to eeprom 
		tempMax = readThresholdMax(); 	//eeprom.c
		tempMin = readThresholdMin();	//eeprom.c
	}


	if(switchPressInterrupt())  		//switch.c
	{
		LCDStart();						//functions.c -> LCD.c
		
		if(CheckPassword())				//fucntions.c -> keypad.c
		{
			SetThreshold();				//fucntions.c -> keypad.c
			WriteThreholdEEPROM();		// I2C -> eeprom.c
			tempMax = readThresholdMax();	//eeprom.c
			tempMin = readThresholdMin();	//eeprom.c
			OnGreenLED();				//LED.c
		}
		else
		{
			sendAlertSms();				//GSM.c
			BlinkRedLED();				//LED.c
		}
	}
	
}
