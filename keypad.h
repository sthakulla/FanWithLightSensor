/*
 * keypad.h
 *
 * Created: 5/17/2020 8:18:33 PM
 *  Author: Noah
 */ 

#ifndef KEYPAD_H
#define KEYPAD_H

#include "avr.h"
#include "lcd.h"

int isPressed(int r, int c);
int getKey();
char getChar(int key);

#endif