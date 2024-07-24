/*
 * timer.c
 *
 * Created: 8/7/2024 14:45:30
 *  Author: Barcala
 */ 

#include "timer.h"

void init_timer(void){
	//se setea timer0 modo fast pwm no inversor
	TCCR0A |= ((1<<COM0A1) | (1<<WGM01) | (1<<WGM00));
	//frecuencia aprox 61Hz
	TCCR0B |= ((1<<CS00) | (1<<CS02)); //prescaler 1024
}

//void PWM(Colores datos){
	//OCR0A = (intensidad + 1) * 100 / 256;
//}
//DDRD |= 
//OCR0A 