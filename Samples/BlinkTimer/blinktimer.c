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

void init_led() {
	DDRA  |=  _BV(PA7); // OUTPUT (Configure PA7 pin as an output)
	PORTA &= ~_BV(PA7); // Set output LOW (LED off)  
}

void init_timer() {
	TIMSK = 0x02;	// Set interrupt mask so that timer overflow
	TCCR0A = 0x80; 	// Select 16bits mode and use normal up counter mode
	TCCR0B = 0x02; 	// feed timer by system clock/8 (counting at 1MHz up to 2^16)
	TCNT0H = 0xFC;	// 0xFC18 = 2^16-1000 so that we count 1ms (at 1MHz) before the next overflow happens 
	TCNT0L = 0x18;
}

volatile uint16_t counter = 0;

ISR(SIG_OVERFLOW0)
{
	// The 2 next statements allow resetting the 16bits counter. Bytes have to be written in this order for a proper 16bits write to happen.
	// 0xFC18 = 2^16-1000 so that we count 1ms (at 1MHz) before the next overflow happens 
	TCNT0H = 0xFC;
	TCNT0L = 0x18 + 12; // Added 12 cycles to account for the cycles used to generate the interrupt and write the registers

	// Blink the LED at 1Hz
	if (counter > 499) {
		counter = 0;
		PORTA ^= _BV(PA7); // Toggle the LED on PA7
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

