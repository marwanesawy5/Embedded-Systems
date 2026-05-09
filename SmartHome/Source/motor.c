#include <avr/io.h>
#include "../Header/motor.h"

/* initialize H-Bridge control pins */
void Motor_init(void)
{
    DDRB  |=  (1<<MOTOR_IN1)|(1<<MOTOR_IN2);    /* IN1, IN2 as output     */
    PORTB &= ~((1<<MOTOR_IN1)|(1<<MOTOR_IN2));   /* motor stopped initially */
}

/* spin motor in forward direction */
void Motor_forward(void)
{
    PORTB |=  (1<<MOTOR_IN1);   /* IN1 = HIGH */
    PORTB &= ~(1<<MOTOR_IN2);   /* IN2 = LOW  */
}

/* stop motor completely */
void Motor_stop(void)
{
    PORTB &= ~((1<<MOTOR_IN1)|(1<<MOTOR_IN2));   /* IN1=LOW, IN2=LOW */
}
