/*
 * lcd.h
 *
 * Created: 2026
 * Author: Smart Home Project
 */

#ifndef LCD_H_
#define LCD_H_

/* LCD pin definitions on PORTA (4-bit mode) */
#define LCD_RS   PA1   /* Register Select pin */
#define LCD_EN   PA2   /* Enable pin          */
#define LCD_D4   PA3   /* Data pin 4          */
#define LCD_D5   PA4   /* Data pin 5          */
#define LCD_D6   PA5   /* Data pin 6          */
#define LCD_D7   PA6   /* Data pin 7          */

/* LCD function prototypes */
void LCD_init(void);
void LCD_clear(void);
void LCD_goto(unsigned char row, unsigned char col);
void LCD_writeChar(char c);
void LCD_writeStr(const char *s);
void LCD_writeNum(unsigned int val);

#endif /* LCD_H_ */
