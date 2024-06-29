#include "header.h"

int readThresholdMin(void)
{
		int threshold;
	   //read threshold from eeprom 
	   return threshold;
}
int readThresholdMax(void)
{
		int threshold;
	   //read threshold from eeprom 
	   return threshold;
}
void Alert(void)
{
	//BlinkRedLED();
	//Message to GSM;
	int temp;
	temp++;
}

void LCDStart(void)
{	

	s8 Message[10];
	s8 KPMinput;
	InitLCD();

	
	strcpy(Message, "Enter Password");
	
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD(Message);
	CmdLCD(GOTO_LINE2_POS0);
	//Password Display

	InitKPM();
	while(1)
	{
	   	KPMinput = KeyScan();
		CmdLCD(GOTO_LINE2_POS0);
		CharLCD(KPMinput);
		delay_ms(100);
	}
	

	
}
