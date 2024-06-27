#include <LPC21xx.h>
#include "types.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "delay.h"


#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr
#define rLED 1<<16 //P1.16
#define gLED 1<<17 //P1.17

int main()
{
	 u8 t='a';
	 init_i2c();
	 IODIR1=gLED|rLED;
	 
	 delay_ms(2000);
	 i2c_eeprom_write(I2C_EEPROM_SA,0x0000,'a');
	 t=i2c_eeprom_read(I2C_EEPROM_SA,0x0000);
	 delay_ms(2000);
	 if(t=='a')
	 {
		 IOPIN1^=gLED;
   }		
	 else
   {
		  IOPIN1^=rLED;
   }
	 while(1);
}
