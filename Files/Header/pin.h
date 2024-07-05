//LCD defines
#define LCD_DATA 8 //p1.16 to p1.23
#define LCD_RS   6 //p1.24
#define LCD_RW   7 //p1.25
#define LCD_EN   5 //p1.26


//KPM defines
#define ROW0 20 //p1.16
#define ROW1 21 //p1.17
#define ROW2 22 //p1.18
#define ROW3 23 //p1.19

#define COL0 16 //p1.20
#define COL1 17 //p1.21
#define COL2 18 //p1.22
#define COL3 19 //p1.23

//UART interrupt defines
#define FUNC1 0
#define FUNC2 1
#define FUNC3 2
#define FUNC4 3

//LEDs
#define GREENLED 17 //P1.16
#define REDLED 18 //P1.17

//Switches
#define ACKSWITCH 19	   //For turning off the  alert

//EEPROM
#define I2CPINS 0x00000050
//Interrupt
//0x15400001 
#define PININTERRUPT  0x15400001  //0x0000000C	//	
//StopAlert

//GSM
