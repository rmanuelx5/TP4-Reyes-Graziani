/*
 * timer.c
 *
 * Created: 4/5/2024 18:51:27
 *  Author: manuc
 */ 

#include "timer.h"


void timer0Init(){
	
	cli();
	
	TCCR0B=0x00; //Timer apagado
	TCCR0A=0x02; //Modo ctc02
	OCR0A=0x04;	 //Activo comparacion en A con 04  Comparador hasta 4 para un frecuencia de led roja de aprox 61Hz
	TCNT0=0x00;	 //Reinicio contador para borrar basura
	
	
	TIMSK0=(1<<OCIE0A);
	
	sei();
	
	TCCR0B=0x04; //prescaler 256 0x04
}

void timer1Init() {
	DDRB |= (1 << PB1) | (1 << PB2);
	
	// Configura el Timer 1 para el modo Fast PWM con el prescaler a 64
	TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1); // Fast PWM, no inverting mode
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11) | (1 << CS10); // Prescaler = 64
	
	// Configura el top value para 8 bits (0xFF)
	ICR1 = 0xFF;
}