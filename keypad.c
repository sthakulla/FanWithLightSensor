
#include "keypad.h"


int isPressed(int r, int c)
{
	for(int i=0; i < 8; ++i)
	{
		CLR_BIT(DDRC,i);
	}
	
	SET_BIT(DDRC,r);
	CLR_BIT(PORTC,r);
	SET_BIT(PORTC,(4+c));
	avr_wait(10);
	return(!GET_BIT(PINC,(4+c)));
}

int getKey()
{	int a=0;
	int r,c;
	for(r=0; r<4; ++r)
	{
		for(c=0; c<4; ++c)
		{
			if(isPressed(r,c))
			{
				a=(r*4+c+1);
				return a;
			}
		}
	}
	return a;
}

char getChar(int key)
{
	switch(key)
	{
		case 1:
		return '1';
		case 2:
		return '2';
		case 3:
		return '3';
		case 4:
		return 'A';
		case 5:
		return '4';
		case 6:
		return '5';
		case 7:
		return '6';
		case 8:
		return 'B';
		case 9:
		return '7';
		case 10:
		return '8';
		case 11:
		return '9';
		case 12:
		return 'C';
		case 13:
		return '*';
		case 14:
		return '0';
		case 15:
		return '#';
		case 16:
		return 'D';
		default:
		return 0;
	}
}
