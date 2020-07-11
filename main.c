/*
 * p5.c
 *
 * Created: 6/3/2020 7:56:36 PM
 * Author : saima
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "avr.h"
#include "keypad.h"
#include "music.h"	

char KeyPad[] = {'X', '1', '2', '3', 'C',
	'4', '5', '6', 'B',
	'7', '8', '9', 'A',
	'*', '0', '#', 'D'};
	
int min=0,sec=0;
char buf[17];
int TimerTime=10;
int s=0,k=0;

int isNumber(int key)
{
	switch(key)
	{
		case 1:
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
		case 9:
		case 10:
		case 11:
		case 14:
		return 1;
		default:
		return 0;
	}
}
enum states{start, setTimer,wait, On, Off}states;
	
int get_sample(){
	ADMUX=0x40; //0100 0000
	ADCSRA=0xC0; //1100 0000
	avr_wait(100);
	while(GET_BIT(ADCSRA,6));
	return ADC;
	
}

int input(int size){	int count = 0;
	char buf[size];
	while (1)
	{
		int current_key = getKey();
		if (isNumber(current_key))
		{
			buf[count] = KeyPad[current_key];
			lcd_pos(0, 16 + count - size);
			lcd_put(KeyPad[current_key]);
			++count;
		}
		if(size == count)
		{
			break;
		}
		avr_wait(200);
	}
	return atoi(buf);
}

void TimerSet(){//gotta set it up
	int min,sec;
	lcd_clr();
	lcd_pos(0,2);
	sprintf(buf, "--SetTimer--");
	lcd_puts(buf);
	avr_wait(800);
	lcd_clr();
	
	do
	{
		lcd_clr();
		lcd_pos(0, 2);
		lcd_puts("Minute: ");
		min = input(2);
		avr_wait(450);
	} while (59 < min);
	
	do
	{
		lcd_clr();
		lcd_pos(0, 2);
		lcd_puts("Second: ");
		sec = input(2);
		avr_wait(450);
	} while (59 < sec);
	TimerTime = 60*min+sec;
	return;
}

void initialize(){
	lcd_init();
	SET_BIT(DDRB, 3);
	/*TCCR1A=0;
	TCCR1B=3;
	TCNT1=65536-(XTAL_FRQ/64)*0.5;
	SET_BIT(TIMSK,TOIE1);
	sei();*/
	
	// set the initial state

	//states=start;
} 



int lightOn(){
		s=get_sample();
		
		sprintf(buf,"%d",s);
		lcd_puts(buf);
		avr_wait(1000);
		lcd_clr();
		return (s<100);
}	



/*void setTimerVal(){
	
	int temp1=input(1);
	if(1 == temp1){
		TimerSet();
	}
	else{
		lcd_clr();
		lcd_pos(1,0);
		sprintf(buf,"NT");
		lcd_puts(buf);
	}
	avr_wait(20);
}*/

/*void displayScreen(){	//"light->start" && D -> back to SetTimer
	lcd_pos(0,2);
	sprintf(buf,"light->FanOn--");
	lcd_puts(buf);
	lcd_pos(1,2);
	sprintf(buf,"D->SetTimer---");
	lcd_puts(buf);
	if(getKey()==16){
		states=setTimer;
	}
}*/
void turnOn(){//start motor fan
		lcd_clr();
		lcd_put('O');
		
			SET_BIT(PORTB,3);
			avr_wait(1000);
			TimerTime--;
}
void ButtonWork(){
	lcd_clr();
	sprintf(buf,"Button Mode");
	lcd_puts(buf);
	
	do{
		k=getKey();
		
		if(4 == k){
			lcd_clr();
			sprintf(buf,"Fan-On");
			lcd_puts(buf);
			
			SET_BIT(PORTB,3);
			avr_wait(800);
		}
		else if(13 == k || TimerTime == 0){
			lcd_clr();
			sprintf(buf,"Fan-Off");
			lcd_puts(buf);
			CLR_BIT(PORTB,3);
			TimerTime=10;
		}
		else if (16 == k){
			TimerSet();
		}
		else if(GET_BIT(PORTB,3)){
			TimerTime--;
			avr_wait(1000);
		}
		
	}while(k !=4 || k!=13);
}

void lightWork(){
		lcd_clr();
		sprintf(buf,"PhotoSensor Mode");
		lcd_puts(buf);
		
		
		
		do{
			s=get_sample();
			k=getKey();
			
			if(s<100){
				lcd_clr();
				sprintf(buf,"Fan-On");
				lcd_puts(buf);
				SET_BIT(PORTB,3);
			}
			else if(13 == k){
				lcd_clr();
				sprintf(buf,"Fan-Off");
				lcd_puts(buf);
				avr_wait(800);
				CLR_BIT(PORTB,3);
				return;
			}
			else{
				lcd_clr();
				sprintf(buf,"Light-Off");
				lcd_puts(buf);
			}
		} while(k!=13 || s>100);
}
/*void SM(){
	switch (states)
	{
		case start:
			lcd_pos(0,2);
			sprintf(buf,"Project5");
			lcd_puts(buf);
			avr_wait(1000);
			states=setTimer;
			break;
		
		case setTimer:
			setTimerVal();  //gets the value of timer
			states=wait;
			break;
			
		case wait:
			if(lightOn()){//need to redo this
				states=On;
			}
			else{
				displayScreen();//"light->start" && D -> back to SetTimer
			}
			avr_wait(10);
			break;
			
		case On:
			turnOn(); //turn on the motorFan
			break;
			
		case Off:
			CLR_BIT(PORTB,3); //turn the motor fan off
			lcd_put('F');
			if(getKey()==16){
				states=setTimer;
			}
			avr_wait(10);
			break;	
			
		default:
			break;
	}
}

ISR(TIMER1_OVF_vect){
	TCNT1=65536 - (XTAL_FRQ/64)*.5;
	TimerFlag=1;
	if(TimerTime!=0){
	TimerTime--;}
}

void lightTest(){
	if(lightOn()){
		lcd_clr();
		lcd_put('L');
		int i=0;
		while(i!=10000){
			SET_BIT(PORTB,3);
			i++;
		}
	}
	else {
		lcd_clr();
		lcd_put('N');
	}
}
*/

int main(void)
{
	initialize();
	int key;
	while(1){
		lcd_clr();
		sprintf(buf,"Mode(L-C/B-B):");
		lcd_puts(buf);
		key=getKey();
		
		if(8 == key){//Button mode
			
			ButtonWork();
			
		}
		else if(12 == key){//Photosensor Mode
			lightWork();
		}
		
		
			//SM();
			//while(!TimerFlag){}
			//TimerFlag=0;
			//lightTest();
	}
}

