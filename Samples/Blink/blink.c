/*********************************************
* Chip type           : ATTINY461
*********************************************/

/*
	BLINK LED on PA7 pin
*/


#define F_CPU 8000000UL  // 8.0 MHz

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>


/* new style */
int main(void)
{
	/* INITIALIZE */
	DDRA  |=  _BV(PA7); // OUTPUT (Configure PA7 pin as an output)
	PORTA &= ~_BV(PA7); // Set output LOW (LED off)  
	
	// Blink
	while (1) {
		PORTA &= ~_BV(PA7); // Set output LOW (LED OFF)  
		_delay_ms(250);
		PORTA |=  _BV(PA7); // Set output HIGH (LED ON)  
		_delay_ms(250);
	}
}

