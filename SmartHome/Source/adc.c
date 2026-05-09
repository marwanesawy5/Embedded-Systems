#include <avr/io.h>
#include "../Header/adc.h"

/* ADC initialization function */
void ADC_init(void)
{
    /* ADMUX:
     * REFS1:0 = 01 -> AVCC (5V) as reference voltage
     * ADLAR   = 0  -> right-adjusted result
     */
    ADMUX = (1<<REFS0);

    /* ADCSRA:
     * ADEN    = 1   -> enable ADC
     * ADPS2:0 = 111 -> prescaler /128 -> 125kHz @ 16MHz
     */
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

/* ADC read function - returns 10-bit result (0-1023) */
unsigned int ADC_read(unsigned char ch)
{
    ADMUX  = (ADMUX & 0xE0) | (ch & 0x07);   /* select channel       */
    ADCSRA |= (1<<ADSC);                      /* start conversion     */
    while(!(ADCSRA & (1<<ADIF)));             /* wait for completion  */
    ADCSRA |= (1<<ADIF);                      /* clear ADIF flag      */
    return ADC;                               /* return 10-bit result */
}
