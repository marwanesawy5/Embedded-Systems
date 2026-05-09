#include <avr/io.h>
#include "../Header/pwm.h"

/* initialize Timer1 Fast PWM 8-bit on OC1A (PD5) */
void PWM_init(void)
{
    DDRD |= (1<<PWM_PIN);   /* OC1A pin as output */

    /* TCCR1A:
     * COM1A1 = 1, COM1A0 = 0 -> non-inverting PWM on OC1A
     * WGM10  = 1              -> Fast PWM 8-bit (part 1)
     */
    TCCR1A = (1<<COM1A1)|(1<<WGM10);

    /* TCCR1B:
     * WGM12      = 1  -> Fast PWM 8-bit (part 2)
     * CS11, CS10 = 11 -> prescaler /64 -> ~977Hz PWM frequency
     */
    TCCR1B = (1<<WGM12)|(1<<CS11)|(1<<CS10);

    OCR1A = 0;   /* start at 0% duty cycle */
}

/* set PWM duty cycle (0-100 percent) */
void PWM_setDuty(unsigned char pct)
{
    if(pct == 0)
    {
        TCCR1A &= ~(1<<COM1A1);   // disconnect OC1A from timer
        PORTD  &= ~(1<<PWM_PIN);  // force pin LOW to stop motor
    }
    else
    {
        TCCR1A |= (1<<COM1A1);   // reconnect OC1A to timer
        OCR1A = (unsigned char)((unsigned long)pct * 255 / 100); // convert percentage to 8-bit OCR value (0-255)
    }
}

