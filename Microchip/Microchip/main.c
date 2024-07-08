/*
 * Microchip.c
 *
 * Created: 1/7/2024 15:10:14
 * Author : Barcala
 */ 

#include <avr/io.h>
#include "MEF.h"
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<PORTB1 | 1<<PORTB2 | 1<<PORTB5);

	//PORTB &= ~(1<<PORTB1 | 1<<PORTB2 | 1<<PORTB5);
	
	PORTB |= (1<<PORTB1 | 1<<PORTB2 | 1<<PORTB5);
	//PORTB &= ~(1<<PORTB5);
    while (1) 
    {
		MEF_update();
		_delay_ms(100);
    }
}

