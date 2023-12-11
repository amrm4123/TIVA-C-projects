



#include "KeyPad.h"
static u8 keys[4][4] = {{'7','8','9','/'},
						{'4','5','6','*'},
						{'1','2','3','-'},
						{'c','0','=','+'}} ;


u8 KEYPAD_Entry(void)
{
	u8 r = 0 , c = 0 ;
	u8 key = DEFAULT_KEY ;
	DIO_WritePin(FIRST_OUT,HIGH) ;
	DIO_WritePin(FIRST_OUT+1,HIGH) ;
	DIO_WritePin(FIRST_OUT+2,HIGH) ;
	DIO_WritePin(FIRST_OUT+3,HIGH) ;
	
	for(r = 0 ; r < 4 ; r++)
	{
		DIO_WritePin(FIRST_OUT+r,LOW);
		for(c = 0 ; c < 4 ; c++)
		{
			if(!DIO_ReadPin(FIRST_IN+c))
			{
				key = keys[r][c] ;
				while(!DIO_ReadPin(FIRST_IN+c));
			}
		}
		DIO_WritePin(FIRST_OUT+r ,HIGH);
	}
	
	return key;
	
}
