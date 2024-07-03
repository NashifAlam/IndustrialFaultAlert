//uart_defines.h
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define BAUD 9600
#define LOADVAL  (PCLK/(16 * BAUD))

//defines for sfr U0LCR
#define WORD_LEN_SEL      3
#define DLAB_BIT          7

//define for sfr U0LSR
#define RDR_BIT           0
#define THRE_BIT          5
#define TEMT_BIT          6

