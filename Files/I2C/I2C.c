#include "I2C.h"

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
  while(READBIT(I2CONSET,SI_BIT)==0);		//Check this shit 
  														//	while(((I2CONSET>>SI_BIT)&1)==0);
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





