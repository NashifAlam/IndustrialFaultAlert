//adc_test_2.c
#include "adc.h"
#include "types.h"
#include "uart.h"
#include "lm35.h"
main()
{
	Init_UART0();
	Init_ADC();
	U0_TxStr("LM35 Test\n\r");
	while(1)
	{
	  U0_TxStr("Temperature ");
		U0_TxF32(ReadTempLM35(0),3);
		U0_TxStr(" degC \r");
	}
}
