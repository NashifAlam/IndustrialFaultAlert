#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "esp01.h"

extern char buff[100],dummy;
extern unsigned char i,ch,r_flag;

char arr[][4] = {"985","467","645"};

int main()
{
	char i;
  InitUART0();
	LCD_Init();
	Write_CMD_LCD(0x80);
	Write_str_LCD("ESP01 Interface");
  delay_ms(1000);
  while(1)
  {
		esp01_connectAP();
		for(i=0;i<3;i++)
		{
			esp01_sendToThingspeak(arr[i]);
			delay_ms(5000);
		}
		while(1);
  }
}

