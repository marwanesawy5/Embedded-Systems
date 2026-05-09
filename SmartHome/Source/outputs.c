#include <avr/io.h>
#include "../Header/outputs.h"

// led & buzzer initialization
void Outputs_init(void)
{
    //setting as uotput
    DDRC  |=  (1<<RED_LED)|(1<<GREEN_LED)|(1<<BLUE_LED)|(1<<BUZZER);

    //starts as low
    PORTC &= ~((1<<RED_LED)|(1<<GREEN_LED)|(1<<BLUE_LED)|(1<<BUZZER));
}

void Buzzer_on(void)
{
    PORTC |= (1<<BUZZER);
}


void Buzzer_off(void)
{
    PORTC &= ~(1<<BUZZER);
}

void LEDs_allOn(void)
{
    PORTC |= (1<<RED_LED)|(1<<GREEN_LED)|(1<<BLUE_LED);
}

void LEDs_allOff(void)
{
    PORTC &= ~((1<<RED_LED)|(1<<GREEN_LED)|(1<<BLUE_LED));
}

void LEDs_set(unsigned char r, unsigned char g, unsigned char b)//to control leds individually aw to make it more flexible
{
    if(r) PORTC |= (1<<RED_LED);
    else  PORTC &= ~(1<<RED_LED);
    if(g) PORTC |= (1<<GREEN_LED);
    else  PORTC &= ~(1<<GREEN_LED);
    if(b) PORTC |= (1<<BLUE_LED);
    else  PORTC &= ~(1<<BLUE_LED);
}

