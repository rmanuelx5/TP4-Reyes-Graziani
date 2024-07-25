/*
 * timer.c
 *
 * Created: 4/5/2024 18:51:27
 *  Author: manuc
 */ 

#include "timer.h"


void timerInit(){
	
	cli();
	
	TCCR0B=0x00; //Timer apagado
	TCCR0A=0x02; //Modo ctc02
	OCR0A=0x3E;	 //Activo comparacion en A con 62
	TCNT0=0x00;	 //Reinicio contador para borrar basura
	
	TIMSK0=(1<<OCIE0A);
	
	sei();
	
	TCCR0B=0x04; //prescaler 256 0x04
}