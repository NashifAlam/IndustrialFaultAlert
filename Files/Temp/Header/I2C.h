							 				//i2c_eeprom_test.c
#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "delay.h"

//defines for I2C_SPEED Configuration 
#define FOSC      12000000
#define CCLK      (5*FOSC)
#define PCLK      (CCLK/4)  //Hz
#define I2C_SPEED 100000    //Hz
#define BITRATE   ((PCLK/I2C_SPEED)/2)

//bit defines for I2CONSET sfr
#define   AA_BIT 2
#define   SI_BIT 3
#define  STO_BIT 4
#define  STA_BIT 5
#define I2EN_BIT 6

//bit defines for I2CONCLR sfr
#define   AAC_BIT 2
#define   SIC_BIT 3
#define  STAC_BIT 5
#define I2ENC_BIT 6

void init_i2c(void);
void i2c_start(void) ;
void i2c_restart(void);
void i2c_write(u8 dat);
void i2c_stop(void);
u8 i2c_nack(void);
u8 i2c_mack(void);






