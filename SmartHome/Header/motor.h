/*
 * motor.h
 *
 * Created: 2024
 * Author: Smart Home Project
 */

#ifndef MOTOR_H_
#define MOTOR_H_

/* H-Bridge L293D control pins on PORTB */
#define MOTOR_IN1   PB0   /* L293D IN1 pin */
#define MOTOR_IN2   PB1   /* L293D IN2 pin */

/* Motor function prototypes */
void Motor_init(void);
void Motor_forward(void);
void Motor_stop(void);

#endif /* MOTOR_H_ */