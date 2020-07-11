
/*
 * avr.h
 *
 * Created: 5/14/2020 10:18:11 PM
 *  Author: saima
 */ 
#ifndef _AVR_H_
#define _AVR_H_

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <stdio.h>

#define XTAL_FRQ 8000000lu

#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

#define NOP() asm volatile("nop"::)

void avr_wait(unsigned short msec);
void custom_wait(int time);

#endif /* _AVR_H_ */