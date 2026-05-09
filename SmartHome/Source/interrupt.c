#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Header/interrupt.h"

volatile unsigned char g_emergency = 0;

//pressing the button
ISR(INT0_vect)
{
    g_emergency ^= 1;   //Toggle
}

void INT0_Init(void) //sets up external interrupt
{
    DDRD  &= ~(1<<PANIC_PIN);   //button
    PORTD |=  (1<<PANIC_PIN);   //byshaghal el pull up bykhaleh high=OFF
    MCUCR |=  (1<<ISC01);       /* trigger INT0 on falling edge      */
    MCUCR &= ~(1<<ISC00);       /* falling edge selection complete   */
    GICR  |=  (1<<INT0);        // enable interrupt
    SREG  |=  (1<<7);           //by'enable el interrupt globaly
}
