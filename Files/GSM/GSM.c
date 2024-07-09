
#include <string.h>
#include "uart.h"
#include "delay.h"
#include "lcd.h"
#include "types.h"

extern char buff[99];
extern unsigned int i;

void checkOK(char *buff)
{
	if(strstr(buff,"OK")){
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("   DATA SEND    ");		delay_s(1);}
	else{
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD(" DATA NOT SEND  ");	delay_s(1);} 
}

void  Init_GSM()
{
	StrLCD1("AT");										delay_s(1);
	i=0;memset(buff,'\0',99);
	U0_TxStr("AT\r\n");								delay_s(1);	
	while(i<4);											delay_ms(500);
	buff[i] = '\0';
	StrLCD1(buff);										delay_s(2);
	checkOK(buff);

	StrLCD1("ATE0");									delay_s(1);
	U0_TxStr("ATE0\r\n");
	i=0;memset(buff,'\0',99);
	while(i<4);											delay_ms(500);
	buff[i] = '\0';
	StrLCD1(buff);										delay_s(2);
	checkOK(buff);

	StrLCD1("AT+CMGF");								delay_s(1);
	U0_TxStr("AT+CMGF=1\r\n");
	i=0;memset(buff,'\0',99);
	while(i<4);											delay_ms(500);
	buff[i] = '\0';
	StrLCD1(buff);										delay_s(2);
	checkOK(buff);

	StrLCD1("AT+CMGD");								delay_s(1);
	U0_TxStr("AT+CMGD=1\r\n");
	i=0;memset(buff,'\0',99);
	while(i<4);											delay_s(2);
	buff[i] = '\0';
	StrLCD1(buff);										delay_s(2);
	checkOK(buff);

	StrLCD1("AT+CNMI");								delay_s(1);
	U0_TxStr("AT+CNMI=2,1,0,0,0\r\n");
	i=0;memset(buff,'\0',99);
	while(i<4);											delay_s(2);
	buff[i] = '\0';
	StrLCD1(buff);										delay_s(2);
	checkOK(buff);
}
void readGSM_SMS()
{
	StrLCD1("AT+CMGR");								delay_s(1);
	U0_TxStr("AT+CMGR=1\r\n");
	i=0;memset(buff,'\0',99);
	while(i<4);											delay_s(2);
	buff[i] = '\0';
	StrLCD1(buff);										delay_s(2);
	checkOK(buff);
	StrLCD1("AT+CMGD");								delay_s(1);
	U0_TxStr("AT+CMGD=1\r\n");
	checkOK(buff);
}

void SendGSM_SMS(char *msg)
{
	StrLCD1("AT+CMGS");								delay_s(1);
	i=0;memset(buff,'\0',99);
	U0_TxStr("AT+CMGS=\"7089306995\"\r\n");	delay_s(1);
	U0_TxStr(msg);
	UART0_Tx(0x1A);									delay_s(5);
	while(i<4);											delay_s(1);
	buff[i] = '\0';
	StrLCD1(buff);										delay_ms(500);
	checkOK(buff);
	return;
}
 
void GSM_SEND_VALUE(char *msg,int val )
{
	StrLCD1("AT+CMGS");								delay_s(1);
	i=0;memset(buff,'\0',99);
	U0_TxStr("AT+CMGS=\"7089306995\"\r\n");	delay_s(1);
	U0_TxStr(msg);
	if(val!=0)
		U0_TxU32(val);
	UART0_Tx(0x1A);									delay_s(5);
	while(i<4);											delay_s(1);
	buff[i] = '\0';
	StrLCD1(buff);										delay_ms(500);
}

