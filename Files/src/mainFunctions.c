#include "header.h"
#include "eeprom.h"

//s8 p[9] __attribute__((at(0x40000040)))="";
int ackSwitch()
{
	return (IOPIN0 >> (ACKSWITCH & 1)); 
}

int interSwitch()
{
	return 	(IOPIN0 >> (INTERSWITCH & 1));
}

void Alert(void)
{
	//Message to GSM;	 
	SendGSM_SMS("Alert You fucked up !!");

	while(!ackSwitch())//while turn off switch is not pressed
	{
		RedLED(1);
		delay_ms(300);
		RedLED(0);
		delay_ms(300);
	}
}


void LCDStart(void)
{	

	s8 Message[10];


	strcpy(Message, "Enter Password");
	
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD(Message);
	CmdLCD(GOTO_LINE2_POS0);
	//Password Display

	InitKPM();	
	checkPassword();
	return;
}


void checkPassword(void)
{
	s8 credentialBuff[20];
	s8 hashBuff[16];
	//s8 Message[16];
	s8 Min[4], Max[4];

	short int i;
	short int trial =0;
	
	//When read from I2C works 	 
	//i2c_eeprom_seqread(I2C_EEPROM_SA,0x00,hashBuff,10);
	//strcpy(hashBuff, p);
		
	strcpy(hashBuff, "1234567");


TRIAL: 
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Password");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<=10;i++)

	{	
		credentialBuff[i] = KeyScan();
		//CmdLCD(GOTO_LINE2_POS0 + i);
		CharLCD(credentialBuff[i]);
		
		if(credentialBuff[i]=='A')
		{
			credentialBuff[i]='\0';
			break;
		}
		if(i == 10)
		{
			credentialBuff[i] = '\0';
		}
		delay_ms(300);
	 }

	if(!strcmp(credentialBuff, hashBuff))
	{
		GreenLED(1);
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
	
		StrLCD("Min temp : ");
		//CmdLCD(GOTO_LINE2_POS0);
		CmdLCD(GOTO_LINE1_POS0 + 12);
		
		for(i=0;i <=3;i++)
		{
			Max[i]= KeyScan();
			
			CharLCD(Max[i]);

			if(Max[i]=='A')
			{
				Max[i]='\0';
				break;
			}
			if(i == 3)
			{
				Max[i] = '\0';
				break;
			}
			delay_ms(300);
		 }		

		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("Max temp : ");
		CmdLCD(GOTO_LINE2_POS0 + 12);		
		
		for(i=0;i <=3;i++)
		{
			Min[i]= KeyScan();
			//
			CharLCD(Min[i]);
			if(Min[i]=='A')
			{
				Min[i]='\0';
				break;
			}
			if(i == 3)
			{
				Min[i] = '\0';
				break;
			}
			delay_ms(300);
		 }	

		setThreshold(Min,Max);
		GreenLED(0); // Turn off LED when interrupt over 
		delay_s(3);
		CmdLCD(CLEAR_LCD);
		RedLED(0);
		return;
	}
	else
	{
		RedLED(1);
		if(trial < 3)
		{
			++trial;
			//strcpy(Message, "Wrong Password !!");
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0); 
			StrLCD("Wrong Password !!");
			delay_s(1);
			goto TRIAL;
		}
		else
		{
			//strcpy(Message, "User Locked");
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("User Locked");
			delay_s(3);
			RedLED(0);
			CmdLCD(CLEAR_LCD);
			return;
		}
	}
}


