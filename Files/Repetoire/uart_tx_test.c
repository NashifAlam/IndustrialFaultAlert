//uart_tx_test.c
#include "uart.h"
#include "delay.h"
main()
{
	Init_UART0();
	while(1)
	{
		UART0_Tx('A');
		U0_TxStr("\n\r");
		U0_TxU32(12345678);
		U0_TxStr("\n\r");
		U0_TxStr("Welcome\n\r");
		U0_TxF32(11.0592,6);
		U0_TxStr("\n\r");
		delay_ms(100);
	}
}
