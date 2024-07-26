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
	OCR0A=0x3E;	 //Activo comparacion en A con 62
	TCNT0=0x00;	 //Reinicio contador para borrar basura
	
	TIMSK0=(1<<OCIE0A);
	
	sei();
	
	TCCR0B=0x04; //prescaler 256 0x04
}

void timer1Init() {
	// Configuración de Timer1 en modo Fast PWM, 8 bits
	TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << WGM12) | (1 << CS10); // No prescaler
	DDRB |= (1 << PB1) | (1 << PB2); // PB1 y PB2 como salida
}