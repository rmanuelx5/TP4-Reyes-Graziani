/*
 * Microchip.c
 *
 * Created: 1/7/2024 15:10:14
 * Author : Barcala
 */ 

#include <avr/io.h>


int main(void)
{
    DDRC |= 1<<PORTC3;
	DDRB |= (1<<PORTB1 || 1<<PORTB2 || 1<<PORTB5);
	PORTC |= 1<<PORTC3;
	PORTB |= (1<<PORTB1 || 1<<PORTB2 || 1<<PORTB5);
	
	PORTB &= ~(1<<PORTB5);
    while (1) 
    {
    }
}

