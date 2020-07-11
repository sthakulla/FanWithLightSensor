
/*
 * lcd.h
 *
 * Created: 5/14/2020 10:18:31 PM
 *  Author: saima
 */ 

#ifndef _LCD_H_
#define _LCD_H_

void lcd_init(void);

void lcd_clr(void);

void lcd_pos(unsigned char r, unsigned char c);

void lcd_put(char c);

void lcd_puts(const char *s);
void lcd_adjust();

#endif /* _LCD_H_ */