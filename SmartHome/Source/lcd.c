#include <avr/io.h>
#include <util/delay.h>
#include "../Header/lcd.h"

static void LCD_pulseEN(void) //send pulse to lcd enable pin
{
    PORTA |=  (1<<LCD_EN);   /* EN HIGH - LCD starts reading */
    _delay_us(1);             // minimum EN HIGH time
    PORTA &= ~(1<<LCD_EN);   //3lshan el falling edge yread el data
    _delay_us(50);            //mstny LCD to process
}

/* send upper 4 bits of n onto data lines D7:D4 */
static void LCD_sendNibble(unsigned char n)
{
    if(n & 0x80) PORTA |= (1<<LCD_D7); else PORTA &= ~(1<<LCD_D7);
    if(n & 0x40) PORTA |= (1<<LCD_D6); else PORTA &= ~(1<<LCD_D6);
    if(n & 0x20) PORTA |= (1<<LCD_D5); else PORTA &= ~(1<<LCD_D5);
    if(n & 0x10) PORTA |= (1<<LCD_D4); else PORTA &= ~(1<<LCD_D4);
    LCD_pulseEN(); //to read the nibble
}

/* send full byte to LCD in two nibbles, rs=0 command rs=1 data */
static void LCD_sendByte(unsigned char byte, unsigned char rs)
{
    if(rs) PORTA |=  (1<<LCD_RS);   /* data mode    */
    else   PORTA &= ~(1<<LCD_RS);   /* command mode */
    LCD_sendNibble(byte);            /* high nibble first  */
    LCD_sendNibble(byte << 4);       /* low  nibble second */
    _delay_us(50);
}

/* initialize LCD in 4-bit mode */
void LCD_init(void)
{
    //to use lcd as output
    DDRA |= (1<<LCD_RS)|(1<<LCD_EN)|(1<<LCD_D4)
           |(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7);

    // start all LCD pins LOW
    PORTA &= ~((1<<LCD_RS)|(1<<LCD_EN)|(1<<LCD_D4)
              |(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7));

    _delay_ms(50);

    /* HD44780 4-bit initialization sequence */
    LCD_sendNibble(0x30); _delay_ms(5);    /* first reset  */
    LCD_sendNibble(0x30); _delay_us(150);  /* second reset */
    LCD_sendNibble(0x30);                  /* third reset  */
    LCD_sendNibble(0x20);                  /* switch to 4-bit mode */

    LCD_sendByte(0x28, 0);   // 3lshan el LCD tebaa 2 lines
    LCD_sendByte(0x0C, 0);   // display ON, cursor OFF
    LCD_sendByte(0x06, 0);   // entry mode: auto-increment
    LCD_sendByte(0x01, 0);   // clear display
    _delay_ms(2);
}

/* clear LCD display */
void LCD_clear(void)
{
    LCD_sendByte(0x01, 0);   /* clear display command      */
    _delay_ms(2);             /* wait for clear to complete */
}

/* move cursor to row and column */
void LCD_goto(unsigned char row, unsigned char col)
{
    /* row 0 base address = 0x00, row 1 base address = 0x40 */
    unsigned char addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    LCD_sendByte(addr, 0);   /* send as command */
}

/* write single character to LCD */
void LCD_writeChar(char c)
{
    LCD_sendByte((unsigned char)c, 1);   /* send as data */
}

/* write string to LCD */
void LCD_writeStr(const char *s)
{
    while(*s) LCD_writeChar(*s++);   /* write until null terminator */
}

/* write unsigned integer to LCD without sprintf */
void LCD_writeNum(unsigned int val)
{
    char buf[6];
    unsigned char i = 0;
    unsigned char a, b;

    if(val == 0) { LCD_writeChar('0'); return; }   /* special case zero */

    /* extract digits right to left */
    while(val > 0) { buf[i++] = '0' + (val % 10); val /= 10; }

    /* reverse buffer to get correct order */
    a = 0; b = i - 1;
    while(a < b)
    {
        char t = buf[a]; buf[a] = buf[b]; buf[b] = t;
        a++; b--;
    }
    buf[i] = '\0';

    LCD_writeStr(buf);   /* send digits to LCD */
}

