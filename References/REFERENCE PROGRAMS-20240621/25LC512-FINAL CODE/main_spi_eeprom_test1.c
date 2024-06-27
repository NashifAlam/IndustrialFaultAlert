                             /* main_spi_eeprom_test1.c */
#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "spi.h"
#include "spi_eeprom.h"
#include "spi_eeprom_defines.h"
#include "defines.h"

#define sLED 8
#define fLED 9

u8  rDat __attribute__((at(0x40000000)));

main(void)
{
	 
	 SETBIT(IODIR0,sLED);
	 Init_SPI();
	 ByteWrite_25LC512(0,'B');
	 delay_ms(100);
	 rDat=ByteRead_25LC512(0);
	 delay_ms(100); 
	(rDat=='B') ?  CPLBIT(IOPIN0,sLED): CPLBIT(IOPIN0,fLED);
	 while(1);
}
          /* end of main25LC512.c */                                                    
  
