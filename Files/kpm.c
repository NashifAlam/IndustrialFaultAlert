#include "types.h"
#include "kpm_defines.h"
#include <LPC21xx.h>
#include "defines.h"

char kpmLUT[4][4]=
{
	{'1','2','3','+'},
	{'4','5','6','-'},
	{'7','8','9','*'},
	{'#','0','A','/'}
};

void InitKPM(void)
{
  //ground all row lines
  WRITENIBBLE(IODIR0,ROW0,15);
  //default all col lines are input high	
}

u32  ColScan(void)
{
  return (READNIBBLE(IOPIN0,COL0)==15) ? 1 : 0; 	
}

u32  RowCheck(void)
{
	u32 r;
	for(r=0;r<4;r++)
	{
		WRITENIBBLE(IOPIN0,ROW0,~(1<<r));
		if(ColScan()==0)
			 break;
	}
	WRITENIBBLE(IOPIN0,ROW0,0);
	return r;
}

u32 ColCheck(void)
{
	u32 c;
	for(c=0;c<4;c++)
	{
		if(READBIT(IOPIN0,COL0+c)==0)
			break;
	}
	return c;
}

char  KeyScan(void)
{
	u32 keyV,r,c;
  //wait for any key press
	while(ColScan()==1);
	//identify row in which key was pressed
	r=RowCheck();
	//identify col in which key was pressed
	c=ColCheck();
	//map key pressed to key value from LUT
	keyV=kpmLUT[r][c];
	return keyV;
}
