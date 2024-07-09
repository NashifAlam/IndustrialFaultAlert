#include <string.h>
#include "uart.h"
#include "delay.h"
#include "lcd.h"
#include "types.h"

extern char buff[20];
extern unsigned char i;

void Gsm_Init()
{
	delay_s(5);	
	StrLCD("GSM STARTUP");
	CmdLCD(0xc0);
	delay_s(5);

	//StrLCD("CONNECTED");

	CmdLCD(0x01);
	StrLCD("AT");
	delay_ms(1000);
	UART0_Str("AT\r\n");
	i=0;memset(buff,'\0',20);

		while(i<4);

	delay_ms(500);
	buff[i] = '\0';
	CmdLCD(0x01);
	StrLCD(buff);

	if(strstr(buff,"OKEY"))
	{
		CmdLCD(0xC0);
		StrLCD("OKEY");
		delay_ms(1000);		
	}

	else
	{
		CmdLCD(0xC0);
		StrLCD("ERORR");
		delay_ms(1000);		
		return;
	}
	CmdLCD(0x01);
	StrLCD("ATE0");
	delay_ms(1000);
	UART0_Str("ATE0\r\n");

	i=0;memset(buff,'\0',20);
		while(i<4);
	delay_ms(500);
	buff[i] = '\0';
	CmdLCD(0x01);
	StrLCD(buff);
	if(strstr(buff,"OKEY"))
	{
		CmdLCD(0xC0);
		StrLCD("OKEY");
		delay_ms(1000);		
	}
	else
	{
		CmdLCD(0xC0);
		StrLCD("ERROR");
		delay_ms(1000);		
		return;
	}
	CmdLCD(0x01);
	StrLCD("AT+CMGF=1\r\n");
	delay_ms(1000);
	UART0_Str("AT+CMGF=1\r\n");
	i=0;memset(buff,'\0',20);
		while(i<4);

	delay_ms(500);
	buff[i] = '\0';
	CmdLCD(0x01);
	StrLCD(buff);
	if(strstr(buff,"OKEY"))
	{
		CmdLCD(0xC0);
		StrLCD("OK INITIALIZED GSM");
		delay_ms(1000);
	}
	else
	{
		CmdLCD(0xC0);
		StrLCD("ERROR");
		delay_ms(1000);		
		return;
	}
}

void gsm_sms()
{
delay_ms(100);
	CmdLCD(0x01);
	StrLCD("SENDING MSG ALERT");
	//UART0_Str("AT+CMGS="7666480528"\r\n");
	UART0_Str("AT+CMGS=");
	delay_ms(50);
	UART0_Tx('"');
  	UART0_Str("7666480528");
	UART0_Tx('"');
	UART0_Str("\r\n");
	delay_ms(500);
	UART0_Str("!!AlEART MSG!!High temp DECTEDTED");
	delay_ms(100);
	UART0_Tx(0x1A);
	i=0;memset(buff,'\0',20);
	while(i<4);
	delay_ms(500);
	buff[i] = '\0';
	CmdLCD(0x01);
	StrLCD(buff);
	delay_ms(500);
	if(strstr((const char *)buff,"OKEY"))
	{
		CmdLCD(0x01);
		StrLCD("MESSAGE SENT..");
		delay_ms(1000);
	}
	else
	{
		CmdLCD(0x01);
		StrLCD("MESSAGE FAILED..");
		delay_ms(1000);
	}

}
void gsm_sms1()
{
	CmdLCD(0x01);
	StrLCD("SENDING MSG ALERT");
	//UART0_Str("AT+CMGS="7666480528"\r\n");

	UART0_Str("AT+CMGS=");
	delay_ms(50);
	UART0_Tx('"');
  	UART0_Str("7666480528");
	UART0_Tx('"');
	UART0_Str("\r\n");
	delay_ms(500);
	UART0_Str("!!HIGH AlEART!! SMOKE DECTEDTED");
	delay_ms(100);
	UART0_Tx(0x1A);
	i=0;memset(buff,'\0',20);
	while(i<4);
	delay_ms(500);
	buff[i] = '\0';
	CmdLCD(0x01);
	StrLCD(buff);
	delay_ms(500);
	if(strstr((const char *)buff,"OKEY"))
	{
		CmdLCD(0x01);
		StrLCD("MESSAGE SENT..");
		delay_ms(1000);
	}
	else
	{
		CmdLCD(0x01);
		StrLCD("MESSAGE FAILED..");
		delay_ms(1000);
	}
}
