#include "header.h"
#include "eeprom.h"

extern int tempMax;
extern int tempMin;
char hashBuff[16];
char keyPress;
s8 credentialBuff[20];
	//char hashBuff[16];
	//s8 Message[16];
s8 Min[4], Max[4];
short int counter;
short int trial =0;
int Flag;

int ackSwitch()
{
	return (IOPIN0 >> (ACKSWITCH & 1)); 
}

void irr(void)
{
   		CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Interrupt Hit !!");
			delay_s(3);
			CmdLCD(CLEAR_LCD);
}

void Alert(u32 status)
{	
	switch(status)
	{
		case 0 :	 StrLCD1("ALERT: SMOKE");
						SendGSM_SMS("Alert Smoke detected");
						break;
		case 1 :	 StrLCD1("ALERT : LOW TEMP");
						SendGSM_SMS("Alert High Temperature Detected");
						break;
		case 2 :	 StrLCD1("ALERT : HIGH TEMP");
						SendGSM_SMS("Alert Low Temperature Detected");
						break;
		default : StrLCD1("ALERT : UNKNOWN");
						SendGSM_SMS("UNKNOWN ERROR DETECTED");
						break;
	}
	

	while(!ackSwitch())//while turn off switch is not pressed
	{
		RedLED(1);
		delay_ms(300);
		RedLED(0);
		delay_ms(300);
	}
}
void changePassword(void)
{
	memset(credentialBuff,'\0',16);
	GreenLED(1);
	StrLCD1("Enter Password");
	CmdLCD(GOTO_LINE2_POS0);
	for(counter=0;counter<=10;counter++)

	{	
		delay_ms(300);
		credentialBuff[counter] = KeyScan();
		//CmdLCD(GOTO_LINE2_POS0 + counter);
		CharLCD(credentialBuff[counter]);
		
		if(credentialBuff[counter]=='A')
		{
			credentialBuff[counter]='\0';
			break;
		}
		if(counter == 10)
		{
			credentialBuff[counter] = '\0';
		}
	
	 }

	 setPassword(credentialBuff);
	 StrLCD1("Password Set !!");
		delay_s(3);
		CmdLCD(CLEAR_LCD);
		RedLED(0);
		StrLCD("Return to main");
}
void changeThreshold(void)
{
		GreenLED(1);
	
		StrLCD1("Max temp : ");
		//CmdLCD(GOTO_LINE2_POS0);
		CmdLCD(GOTO_LINE1_POS0 + 12);
		
		for(counter=0;counter <=3;counter++)
		{
			delay_ms(300);
			Max[counter]= KeyScan();
			
			

			if(Max[counter]=='A')
			{
				Max[counter]='\0';
				break;
			}
			if(counter == 3)
			{
				Max[counter] = '\0';
				break;
			}
			//delay_ms(300); 
			CharLCD(Max[counter]);
		 }		

		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("Min temp : ");
		CmdLCD(GOTO_LINE2_POS0 + 12);		
		
		for(counter=0;counter <=3;counter++)
		{
			delay_ms(300);
			Min[counter]= KeyScan();
			//
			
			if(Min[counter]=='A')
			{
				Min[counter]='\0';
				break;
			}
			if(counter == 3)
			{
				Min[counter] = '\0';
				break;
			}
			CharLCD(Min[counter]);
		 }	

		setThreshold(Min,Max,&tempMin,&tempMax);
		GreenLED(0); // Turn off LED when interrupt over 
		CmdLCD(CLEAR_LCD);
		StrLCD("Threshold Set !!");
		delay_s(3);
		CmdLCD(CLEAR_LCD);
		RedLED(0);
		StrLCD("Return to main");
}
void checkPassword(void)
{
	StrLCD1("Enter Password");
	CmdLCD(GOTO_LINE2_POS0);
	//Password Display
	//When read from I2C works 	 
	//i2c_eeprom_seqread(I2C_EEPROM_SA,0x00,hashBuff,10);
	//strcpy(hashBuff, p);
		
	//strcpy(hashBuff, "1234567");
	memset(hashBuff,'\0',16);
	memset(credentialBuff,'\0',16);
	
	readPassword(hashBuff) ;

TRIAL: 
	StrLCD1("Enter Password");
	CmdLCD(GOTO_LINE2_POS0);
	for(counter=0;counter<=10;counter++)

	{	
		delay_ms(300);
		credentialBuff[counter] = KeyScan();
		//CmdLCD(GOTO_LINE2_POS0 + counter);
		CharLCD(credentialBuff[counter]);
		
		if(credentialBuff[counter]=='A')
		{
			credentialBuff[counter]='\0';
			break;
		}
		if(counter == 10)
		{
			credentialBuff[counter] = '\0';
		}
	
	 }

	if(!strcmp(credentialBuff, hashBuff))
	{
		do
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0); 
			StrLCD("1: Set Threshold");
			CmdLCD(GOTO_LINE2_POS0); 
			StrLCD("2: Set Password");


				delay_ms(300);
				keyPress = KeyScan();
				if(keyPress == '1'){
					changeThreshold();
					break;
					}
				else if(keyPress == '2'){
					changePassword();	
					break;	  
					}
	
		}	while(1);

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


