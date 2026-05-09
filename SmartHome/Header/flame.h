/*
 * flame.h
 *
 * Created: 2024
 * Author: Smart Home Project
 */

#ifndef FLAME_H_
#define FLAME_H_

/* Flame sensor pin - PB2 (active LOW, internal pull-up) */
#define FLAME_PIN   PB2

/* Flame sensor function prototypes */
void FlameSensor_init(void);
unsigned char FlameSensor_detected(void);

#endif /* FLAME_H_ */