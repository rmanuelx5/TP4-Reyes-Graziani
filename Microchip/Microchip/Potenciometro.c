/*
 * Potenciometro.c
 *
 * Created: 30/7/2024 16:15:48
 *  Author: manuc
 */ 

#include "Potenciometro.h"

void initADC(){
	DDRC &= ~(1<<PORTC3);
	ADCSRA = 0x87;//make ADC enable and select ck/128
	ADMUX = (0 << REFS1) | (1 << REFS0) | (1 << ADLAR) | 0x03;//Ref external VCC, ADC3, left-justified
}

uint8_t leerPot(){
	//uint8_t val;
	ADCSRA |= (1<<ADSC);// Iniciar conversión
	while((ADCSRA&(1<<ADIF))==0); // Esperar a que termine la conversión
	ADCSRA |= (1<<ADIF); // Limpiar la bandera ADIF
	//val = ADCH;// // Escalar el valor ADC (valor máximo 1024/4 = 256)

	return ADCH;
}