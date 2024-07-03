//uart.h
#include "types.h"
void Init_UART0(void);
void UART0_Tx(u8 sByte);
void U0_TxU32(u32 );
void U0_TxStr(s8 *);
void U0_TxF32(f32,u8);
u8   UART0_Rx(void);
