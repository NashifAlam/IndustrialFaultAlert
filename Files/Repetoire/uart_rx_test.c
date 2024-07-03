//uart_rx_test.c
#include "uart.h"
#include<string.h>

s8 rBuff[20];

main()
{
	s32 i;
	Init_UART0();
	for(i=0;;i++)
	{
		rBuff[i]=UART0_Rx();
		UART0_Tx(rBuff[i]);
		if(rBuff[i]=='\r')
		{
			rBuff[i]='\0';
			U0_TxStr("\n\r");
			break;
		}
	}
		
	while()

	U0_TxStr(rBuff);
	while(1);
}
