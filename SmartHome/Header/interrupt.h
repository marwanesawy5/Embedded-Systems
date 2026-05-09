/*
 * interrupt.h
 *
 * Created: 2026
 * Author: Smart Home Project
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

//El button
#define PANIC_PIN   PD2

// Volatile 3lshan y3rf el compiler bytghyar fe ay lahza fe el c
extern volatile unsigned char g_emergency;  //0=no emergency, 1=emergency

void INT0_Init(void);

#endif
