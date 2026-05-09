/*
 * outputs.h
 *
 * Created: 2026
 * Author: Smart Home Project
 */

#ifndef OUTPUTS_H_
#define OUTPUTS_H_

// Output
#define RED_LED     PC0
#define GREEN_LED   PC1
#define BLUE_LED    PC2
#define BUZZER      PC5

// Output function names
void Outputs_init(void);
void Buzzer_on(void);
void Buzzer_off(void);
void LEDs_allOn(void); //for all leds
void LEDs_allOff(void);
void LEDs_set(unsigned char r, unsigned char g, unsigned char b);

#endif
