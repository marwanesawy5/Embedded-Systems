#include <avr/io.h>
#include <util/delay.h>
#include "Header/adc.h"
#include "Header/lcd.h"
#include "Header/pwm.h"
#include "Header/motor.h"
#include "Header/flame.h"
#include "Header/interrupt.h"
#include "Header/outputs.h"

int main(void)
{
    // local variables
    unsigned int  temp_raw, ldr_raw;
    unsigned int  temp_C,   ldr_pct;
    unsigned char duty;
    unsigned char fire;

    // initialize all peripherals
    ADC_init();
    PWM_init();
    Motor_init();
    Outputs_init();
    FlameSensor_init();
    INT0_Init();
    LCD_init();

    /* startup message */
    LCD_goto(0, 0); LCD_writeStr("                ");
    LCD_goto(1, 0); LCD_writeStr("                ");
    _delay_ms(2000);
    LCD_clear();

    while(1)
    {
        /* read raw ADC values from sensors */
        ldr_raw  = ADC_read(ADC_LDR_CHANNEL);    /* PA0 - LDR  */
        temp_raw = ADC_read(ADC_TEMP_CHANNEL);    /* PA7 - LM35 */

        /* convert LM35 raw to celsius
         * LM35 = 10mV per degree, ADC step = 5000/1024 mV
         * temp = ADC * 5000 / 1024 / 10
         */
        temp_C = (unsigned int)((unsigned long)temp_raw * 5000UL / 1024 / 10);

        /* convert LDR raw to calibrated percentage 0-100%
         * LDR_MAX is the actual ADC reading at maximum brightness
         * clamp then map to full 0-100% range
         */
        if(ldr_raw > LDR_MAX) ldr_raw = LDR_MAX;   /* clamp to max  */
        if(ldr_raw < LDR_MIN) ldr_raw = LDR_MIN;   /* clamp to min  */
        ldr_pct = (unsigned char)((unsigned long)(ldr_raw - LDR_MIN)*100/(LDR_MAX - LDR_MIN));     /* map to 0-100% */


        fire = FlameSensor_detected(); // read flame sensor state

        /* -------------------------------------------------------
           PRIORITY 1: Fire detection (highest priority)
           ------------------------------------------------------- */
        if(fire)
        {
            LEDs_allOff();		 /* all LEDs ON       */
            Buzzer_on();     	   /* activate buzzer   */
            PWM_setDuty(0);    	/* fan at full speed */
            Motor_stop();     /* spin fan forward  */

            /* display fire alert on LCD */
            LCD_goto(0, 0); LCD_writeStr("Critical alert! ");
            LCD_goto(1, 0); LCD_writeStr("                ");

            _delay_ms(200);
            continue;   /* skip lower priority code */
        }

        Buzzer_off(); // no fire - silence buzzer

        /* -------------------------------------------------------
           PRIORITY 2: Emergency panic mode
           ------------------------------------------------------- */
        if(g_emergency)
        {
            LEDs_allOn();        /* all LEDs ON       */
            Buzzer_on();         /* activate buzzer   */
            PWM_setDuty(100);    /* fan at full speed */
            Motor_forward();     /* spin fan forward  */

            /* display emergency message on LCD */
            LCD_goto(0, 0); LCD_writeStr("!! EMERGENCY !! ");
            LCD_goto(1, 0); LCD_writeStr("PANIC ACTIVATED ");

            _delay_ms(200);
            continue;   /* skip lower priority code */
        }
        /* no emergency - silence buzzer */
        Buzzer_off();

        /* -------------------------------------------------------
           PRIORITY 3: Normal automatic operation
           ------------------------------------------------------- */

        /* fan speed control based on temperature thresholds */
        if(temp_C >= 40)		duty = 100;   /* full speed */
        else if(temp_C >= 35)	duty = 75;    /* 75% speed  */
        else if(temp_C >= 30)	duty = 50;    /* 50% speed  */
        else if(temp_C >= 25)	duty = 25;    /* 25% speed  */
        else					duty = 0;     /* fan OFF    */

        /* apply fan duty cycle */
        if(duty > 0)
        {
            PWM_setDuty(duty);
            Motor_forward();
        }
        else
        {
            PWM_setDuty(0);
            Motor_stop();
        }

        /* LED lighting control based on LDR intensity */
        if(ldr_pct <= 15)		LEDs_allOn();          /* all 3 LEDs ON - very dark  */
        else if(ldr_pct <= 50)	LEDs_set(1, 1, 0);     /* Red and Green ON           */
        else if(ldr_pct <= 70)	LEDs_set(1, 0, 0);     /* Red only ON                */
        else					LEDs_allOff();         /* all LEDs OFF - bright room */

        /* LCD row 0 - fan status */
        LCD_goto(0, 0);
        if(duty > 0)	LCD_writeStr("FAN is ON       ");
        else			LCD_writeStr("FAN is OFF      ");

        /* LCD row 1 - temperature and LDR percentage */
        LCD_goto(1, 0);
        LCD_writeStr("Temp=");
        LCD_writeNum(temp_C);
        LCD_writeChar('C');
        LCD_writeStr(" LDR=");
        LCD_writeNum(ldr_pct);
        LCD_writeChar('%');
        LCD_writeStr("   ");   /* clear leftover characters */
        _delay_ms(300);   /* refresh rate ~3Hz */
    }
}
