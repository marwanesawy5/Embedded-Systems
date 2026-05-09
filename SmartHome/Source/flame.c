#include <avr/io.h>
#include "../Header/flame.h"
void FlameSensor_init(void)
{
    DDRB  &= ~(1<<FLAME_PIN);   /* PB2 as input pin        */
    PORTB |=  (1<<FLAME_PIN);   /* enable internal pull-up */
}

// returns 1 if fire detected, 0 if not
unsigned char FlameSensor_detected(void)
{
    /* sensor is active LOW:
     * pin HIGH = no fire
     * pin LOW  = fire detected (at the falling edge)
     */
    return (!(PINB & (1<<FLAME_PIN))) ? 0 : 1;
}
