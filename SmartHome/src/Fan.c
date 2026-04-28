#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t fan_is_on = 0;		//0 = OFF, 1 = ON
uint8_t speed_level = 1;	//1 = (25%), 2 = (50%), 3 = High (75%), 4 = (100%)

static void Apply_Speed(void) {
	if (speed_level == 1) OCR0 = 64;
	else if (speed_level == 2) OCR0 = 128;
	else if (speed_level == 3) OCR0 = 192;
	else if (speed_level == 4) OCR0 = 255;
}
void FanInit(void) {
	DDRC |= (1 << PC0) | (1 << PC1);	//Output Pins
	// Initial Declaration
	PORTC |= (1 << PC0);	//High
	PORTC &= ~(1 << PC1);	//Low
	// PWM Pin
	DDRB |= (1 << PB3);
	TCNT0 = 0;	//Timer = 0
	OCR0 = 0;
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);
	DDRD &= ~((1 << PD2) | (1 << PD3));	//Input Pins
	PORTD |= (1 << PD2) | (1 << PD3);	//Enable Internal Pull-Up Resistors
}

void FanControl(void) {
	// --- Button 1: Start / Stop ---
	if (!(PIND & (1 << PD2))) {
		_delay_ms(30);
		if (!(PIND & (1 << PD2))) {
			fan_is_on = !fan_is_on;
			if (fan_is_on) Apply_Speed();
			else OCR0 = 0; // Turn OFF
			while (!(PIND & (1 << PD2))); // Wait for release
			}
	}
	// --- Button 2: Toggle 3 Speeds ---
	if (fan_is_on && !(PIND & (1 << PD3))) {
		_delay_ms(30);
		if (!(PIND & (1 << PD3))) {
			speed_level++;
			if (speed_level > 4) speed_level = 1; // Loop back
			Apply_Speed();
			while (!(PIND & (1 << PD3))); // Wait for release
			}
	}
}
