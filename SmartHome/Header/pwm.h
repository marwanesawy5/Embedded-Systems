/*
 * pwm.h
 *
 * Created: 2024
 * Author: Smart Home Project
 */

#ifndef PWM_H_
#define PWM_H_

/* PWM output pin - OC1A = PD5 */
#define PWM_PIN   PD5

/* PWM function prototypes */
void PWM_init(void);
void PWM_setDuty(unsigned char pct);

#endif /* PWM_H_ */