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

#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr

void init_i2c(void)
{
  //Cfg p0.2 for SCL 
  //&   p0.3 for SDA functions using PINSEL0
  PINSEL0|=0x00000050;
  //Cfg Speed for I2C Serial Communication
  I2SCLL=BITRATE;
  I2SCLH=BITRATE;
  //I2C Peripheral Enable for Communication
  SSETBIT(I2CONSET,I2EN_BIT); 
}

void i2c_start(void)
{
  // start condition
  SSETBIT(I2CONSET,STA_BIT);
  //wait for start bit status
  while(READBIT(I2CONSET,SI_BIT)==0);
  // clear start condition
  SCLRBIT(I2CONCLR,STA_BIT);
}	

void i2c_restart(void)
{
   // start condition
   SSETBIT(I2CONSET,STA_BIT);
   //clrprev SI_BIT
   SCLRBIT(I2CONCLR,SI_BIT);
   //wait for SI bit status
   while(READBIT(I2CONSET,SI_BIT)==0);
   // clear start condition
   SCLRBIT(I2CONCLR,STA_BIT);
}	

void i2c_write(u8 dat)
{
  //put data into I2DAT
  I2DAT=dat;	
  //clr SI_BIT using I2CON
  SCLRBIT(I2CONCLR,SI_BIT);
  //wait for SI bit status using I2CONSET
  while(READBIT(I2CONSET,SI_BIT)==0);
	//implies pack
}	

void i2c_stop(void)
{
  // issue stop condition
  SSETBIT(I2CONSET,STO_BIT);
  // clr SI bit status	
  SCLRBIT(I2CONCLR,SI_BIT);
  //stop will cleared automatically
}

u8 i2c_nack(void)
{	
  I2CONSET = 0x00; //Assert Not of Ack
  SCLRBIT(I2CONCLR,SI_BIT);
  while(READBIT(I2CONSET,SI_BIT)==0);
  return I2DAT;
}

u8 i2c_mack(void)
{	
  SSETBIT(I2CONSET,AA_BIT); //Assert Ack
  SCLRBIT(I2CONCLR,SI_BIT);
  while(READBIT(I2CONSET,SI_BIT)==0);
  SCLRBIT(I2CONCLR,AAC_BIT); //Clear Assert Ack
  return I2DAT;
}

void i2c_eeprom_bytewrite(u8 slaveAddr,
	                        u8 wBuffAddr,
                          u8 wByte)
{
    //issue i2c start
    i2c_start();	
    //slaveAddr + w,& implies pack
    i2c_write(slaveAddr<<1); 
    //wBuffAddr,implies pack
    i2c_write(wBuffAddr);    
    //wByte,implies pack
    i2c_write(wByte);   
    //issue i2c stop	
    i2c_stop();
    //write cycle delay
    delay_ms(10);
}			

u8 i2c_eeprom_randomread(u8 slaveAddr,
                         u8 rBuffAddr)
{
    u8 dat;	
    //start condition
    i2c_start();	
    //slaveAddr + w ,&take ack
    i2c_write(slaveAddr<<1);
    //rBuffAddr,&take ack
    i2c_write(rBuffAddr);
    //restart
    i2c_restart();	
    //slaveAddr + r, &take ack
    i2c_write(slaveAddr<<1|1); 
    dat=i2c_nack();	
    //stop condition
    i2c_stop();
    return dat;
}

void i2c_eeprom_pagewrite(u8 slaveAddr,
	                        u8 wBuffStartAddr,
                          s8 *p,
                          u8 nBytes)
{
  u8 i;
  i2c_start();	
  //slaveAddr + w
  i2c_write(slaveAddr<<1);    
  //wBuffStartAddr
  i2c_write(wBuffStartAddr);  
  for(i=0;i<nBytes;i++)
      i2c_write(p[i]); //wDATA            
  i2c_stop();
  delay_ms(10);
}	

void i2c_eeprom_seqread(u8 slaveAddr,
	                      u8 rBuffStartAddr,
                        s8 *p,
                        u8 nBytes)
{
   u8 i;
	 //start
   i2c_start();	
	 //slaveAddr + w,take ack
   i2c_write(slaveAddr<<1);
	 //rBuffStartAddr,take ack
   i2c_write(rBuffStartAddr);  
   //restart  
   i2c_restart();	
	 //slaveAddr + r,take ack  
	 i2c_write(slaveAddr<<1|1); 
	 for(i=0;i<nBytes-1;i++)
      p[i]=i2c_mack();//rbyte,& give mack	
	 //read last byte,&give nack
   p[i]=i2c_nack();
	 //stop
   i2c_stop();
}

u8 rByte __attribute__((at(0x40000010)));
s8 rArray[10] __attribute__((at(0x40000020)));

main()
{
	init_i2c();
	i2c_eeprom_bytewrite(0x50,0,'9');
	rByte=i2c_eeprom_randomread(0x50,0);
	i2c_eeprom_pagewrite(0x50,0x10,"12345678",8);
	i2c_eeprom_seqread(0x50,0x10,rArray,8);
	while(1);
}
