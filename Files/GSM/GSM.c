#include "uart.h"



void SendGSM_SMS(unsigned char *Message)
{
	u8 Buff[40];
	Init_UART0();
	if(UART0_StrRx(&Buff))
		U0_TxStr("AT");
	if(UART0_OK());
	//Send message

	return;
}
