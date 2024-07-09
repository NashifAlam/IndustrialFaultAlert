//uart.c
#include <LPC21xx.h>
#include <string.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "uart_defines.h"
#include "pin.h"

char ch;
char buff[99]; 
int  i;
extern int Flag;
char dummy;
	  
void UART0_isr(void) __irq
{
  if((U0IIR & 0x04)) 			//check if receive interrupt
  {
		ch = U0RBR;				// Read to Clear Receive Interrupt 
		if(i<99)
		{
			buff[i++] = ch; 
			if(strstr(buff,"+CMTI"))
				Flag=1;
		}
  }
  else
      dummy=U0IIR; 						//Read to Clear transmit interrupt
   
	VICVectAddr = 0; 
   VICVectAddr = 0; /* dummy write */
}

void Init_UART0(void)
{
   //cfg pin connect block 
   //for p0.0 as TXD0,p0.1 as RXD0
   PINSEL0 |= UARTPINS;
	 //cfg for 8N1,DLAB enable
	 U0LCR=1<<DLAB_BIT|WORD_LEN_SEL;
	 //cfg baudrate
   U0DLM=LOADVAL>>8;
   U0DLL=LOADVAL;
   //disable DLAB bit
   CLRBIT(U0LCR,DLAB_BIT);	

	VICIntSelect = 0x00000000; // IRQ
	VICVectAddr0 = (unsigned)UART0_isr;
  	VICVectCntl0 = 0x20 | 6; /* UART0 Interrupt */
  	VICIntEnable = 1 << 6;   /* Enable UART0 Interrupt */
 
 // U0IIR = 0xc0;
 // U0FCR = 0xc7;
  U0IER = 0x03;       /* Enable UART0 RX and THRE Interrupts */   
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

u32 UART0_StrRx(u8 *Buff[])
{

	int i = 0;

	do{
		*Buff[i] = UART0_Rx();
		if(*Buff[i] == 'K' && *Buff[i-1] == 'O')
			break;
	}while(i++);

	if(*Buff[i] == 'K' && *Buff[i-1] == 'O')
		return 1;
	else 
		return 0;


}

u32 UART0_OK(void)
{
	if((UART0_Rx() == 'K') && (UART0_Rx() == 'O'))
		return 1;
	else
		return 0;
}
