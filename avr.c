
/*
 * avr.c
 *
 * Created: 5/14/2020 10:18:22 PM
 *  Author: saima
 */ 
#include "avr.h"
#include <stdio.h>

void
avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}
void custom_wait(int time){
	TCCR0 = 2;
	while (time--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ/8) * 0.00005);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}