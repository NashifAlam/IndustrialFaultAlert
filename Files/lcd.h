#include "types.h"
void writeLCD(u8 byte);
void cmLCD(u8 cmd);
void charLCD(u8 asciival);
void initLCD(void);

void strLCD(s8*);
void u32LCD(u32);
				
void WriteLCD(u8 dat) ;
void CmdLCD(u8 cmd);
void CharLCD(u8 asciiVal);

void InitLCD(void);
void StrLCD(s8 *p);
void U32LCD(u32 n);
void S32LCD(s32 n);
void F32LCD(f32 f,u8 nDP);
void BinLCD(u32 n,u8 nBD);
void HexLCD(u32 n);
void OctLCD(u32 n);
void BuildCGRAM(u8 *p,u8 nBytes);
