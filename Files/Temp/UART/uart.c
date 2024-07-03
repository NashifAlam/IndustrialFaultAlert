//uart.c
#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "uart_defines.h"

void Init_UART0(void)
{
   //cfg pin connect block 
   //for p0.0 as TXD0,p0.1 as RXD0
   PINSEL0=0x00000005;
	 //cfg for 8N1,DLAB enable
	 U0LCR=1<<DLAB_BIT|WORD_LEN_SEL;
	 //cfg baudrate
   U0DLM=LOADVAL>>8;
   U0DLL=LOADVAL;
   //disable DLAB bit
   CLRBIT(U0LCR,DLAB_BIT);	
}

void UART0_Tx(u8 sByte)
{
	//write 2 transmit buffer
	U0THR=sByte;
	//wait until transmission completion
	while(READBIT(U0LSR,TEMT_BIT)==0);
}

void U0_TxU32(u32 n)
{
	u8 a[10];
	s32 i=0;
	if(n==0)
	{
		UART0_Tx('0');
	}
	else
	{
		while(n>0)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
		for(--i;i>=0;i--)
		  UART0_Tx(a[i]);
	}
}

void U0_TxStr(s8 *p)
{
	while(*p)
		UART0_Tx(*p++);
}

void U0_TxF32(f32 f,u8 nDP)
{
	s32 n,i;
	if(f<0.0)
	{
		UART0_Tx('-');
		f=-f;
	}
  n=f;
  U0_TxU32(n);
  UART0_Tx('.');
  for(i=0;i<nDP;i++)
  {
		f=(f-n)*10;
		n=f;
		UART0_Tx(n+48);
  }			
}

u8 UART0_Rx(void)
{
	//wait for reception completion status
	while(READBIT(U0LSR,RDR_BIT)==0);
	//read & return recvd byte;
	return U0RBR;
}
