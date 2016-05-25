/*********************************************
* Chip type           : ATTINY461
*********************************************/

/*
	BLINK LED on PA7 pin using timer 0 to generate interrupts every 1ms.
*/


#define F_CPU 8000000UL  // 8.0 MHz

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>

void led_on() { PORTA |= _BV(PA7); }
void led_off() { PORTA &= ~_BV(PA7); }
void led_toggle() { PORTA ^= _BV(PA7); }

void init_led() {
	DDRA  |=  _BV(PA7); // OUTPUT (Configure PA7 pin as an output)
	PORTA &= ~_BV(PA7); // Set output LOW (LED off)  
}

void init_timer() {
	TIMSK = 0x02;	// Set interrupt mask so that timer overflow
	TCCR0A = 0x00; 	// Select 8bits mode and use normal up counter mode
	TCCR0B = 0x01; 	// feed timer by system clock (counting at 8MHz)
	TCNT0L = 0x00;
}

volatile uint16_t counter = 0;
volatile uint16_t led = 0;


void init_tristate() { // connected on PA0..3
	// Put all in high impedance state
	DDRA  &=  ~0b00001111; // all as inputs
	PORTA &=  ~0b00001111; // all 0 (no pullup)
}

void set_high_impedance(uint8_t pin) {
	pin = pin-1;
	DDRA  &=  ~(1<<pin); // INPUT
	PORTA &=  ~(1<<pin); // NO PULLUP
} 

void set_positive(uint8_t pin) {
	pin = pin-1;
	PORTA |=  (1<<pin); // HIGH
	DDRA  |=  (1<<pin); // OUTPUT
} 

void set_negative(uint8_t pin) {
	pin = pin-1;
	PORTA &=  ~(1<<pin); // LOW
	DDRA  |=  (1<<pin); // OUTPUT
} 

void set_led(int8_t led) {
	switch (led) {
		case 0: set_negative(4); set_positive(1); break;
		case 1: set_negative(1); set_positive(2); break;
		case 2: set_negative(2); set_positive(1); break;
		case 3: set_negative(1); set_positive(3); break;
		case 4: set_negative(3); set_positive(1); break;
		case 5: set_negative(2); set_positive(3); break;
		case 6: set_negative(3); set_positive(2); break;
		case 7: set_negative(2); set_positive(4); break;
		case 8: set_negative(4); set_positive(2); break;
		case 9: set_negative(3); set_positive(4); break;
		case 10: set_negative(4); set_positive(3); break;
		case 11: set_negative(1); set_positive(4); break;
	
	}
}

volatile uint16_t period = 1000;

ISR(SIG_OVERFLOW0)
{

	
	if (counter > period) {
		counter = 0;
		init_tristate();
		set_led(led);
		led= (led+1)%12;
		if (led == 0) led_toggle();
	}
	counter++;
}



int main(void)
{
	init_led();
	init_timer();
	sei();         	//Globally enable all interrupts

	while (1) {
		// NOTHING (all is happening in the timer interrupt)		
	}
}

