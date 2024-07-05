//#include "types.h"
//#include "delay.h"
#include "I2C.h"
#include "defines.h"

u8 rByte;//__attribute__((at(0x40000010)));
s8 rArray[10];// __attribute__((at(0x40000020)));

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



void setThreshold(char* min, char* max)
{
    //wBuffStartAddr for min
	
	
	//i2c_eeprom_pagewrite(0x50, 0x20,min,8) ;
	//wBuffStartAddr for max
	//i2c_eeprom_pagewrite(0x50, 0x30,max,8) ;

	return;
}

int readThresholdMin(void)
{		
	//i2c_eeprom_seqread(0x50,0x20,Min,8);
	//convert from string to int hen return int
	return 10;
}
int readThresholdMax(void)
{	   

	//i2c_eeprom_seqread(0x50,0x30,Max,8);
	//covert from string to int then return the int
	   return 45;
}

void readPassword(char** readBuffer)
{	
	i2c_eeprom_pagewrite(0x50,0x10,"1234567",8);
	//i2c_eeprom_seqread(0x50,0x10,readBuffer,8);
	return;
}
