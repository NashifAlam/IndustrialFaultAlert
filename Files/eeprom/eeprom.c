#include<stdlib.h>
//#include "types.h"
//#include "delay.h"
#include "I2C.h"
#include "defines.h"

#include<string.h>
extern char hashBuff[16];


u8 rByte;//__attribute__((at(0x40000010)));
s8 rArray[10];// __attribute__((at(0x40000020)));
int temp;

void itos(int num, char* str)
{
    int i = 0, j = 0, k = 0;
    int sign = num;
    if (num < 0) {
        num = -num;
    }
    do {
        str[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (sign < 0) {
        str[i++] = '-';
    }
    str[i] = '\0';

    for (j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}   
void i2c_eeprom_bytewrite(u16 slaveAddr,
	                        u16 wBuffAddr,
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

u8 i2c_eeprom_randomread(u16 slaveAddr,
                         u16 rBuffAddr)
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
	                        u16 wBuffStartAddr,
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
	                      u16 rBuffStartAddr,
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
   p[i]=i2c_nack();	i++;
   p[i] = '\0';
   
	 //stop
   i2c_stop();
}


void setThreshold(char* Min, char* Max, int* min, int* max)
{
    //wBuffStartAddr for min
		//wBuffStartAddr for max
	/*
	i2c_eeprom_pagewrite(0x50, 0x20,min,8) ;

	i2c_eeprom_pagewrite(0x50, 0x30,max,8) ;

	  */
	*min = atoi(Min);
	*max = atoi(Max);
	
	return;
}

int readThresholdMin(void)
{	
	  	/*
	i2c_eeprom_seqread(0x50,0x20,rArray,8);*/
	temp = atoi("10");
	return 10;
}
int readThresholdMax(void)
{	   
	  	/*	*/
	//i2c_eeprom_seqread(0x50,0x30,rArray,8);
	temp = atoi("40");

	return temp;
}

void setPassword(char * pass)
{
		 i2c_eeprom_pagewrite(0x50,0x00,pass,8);
		 return;
}
void readPassword(char* readBuffer)
{	
	/**/
	i2c_eeprom_pagewrite(0x50,0x00,"12345",8);
	i2c_eeprom_seqread(0x50,0x00,hashBuff,8);
	//strcpy(readBuffer,rArray);
	return;
}
