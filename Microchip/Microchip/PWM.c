/*
 * PWM.c
 *
 * Created: 29/7/2024 20:17:30
 *  Author: manuc
 */ 

#include "PWM.h"
#include "Potenciometro.h"

#define PWM_PERIOD 256 // Periodo PWM de 8 bits
#define PWM_START DDRB |= (1 << PORTB5) // Configurar PB5 como salida
#define PWM_OFF PORTB &= ~(1 << PORTB5)
#define PWM_ON PORTB |= (1 << PORTB5)

static uint8_t pwm_r = 128; // Duty cycle inicial para rojo (PB5)

static uint8_t salir, valAnt=0, valAct=0;

static uint8_t PWM_position=0;

void init_puertos(){
	DDRB |= (1<<PORTB1 | 1<<PORTB2 | 1<<PORTB5);
	OCR1B = 128;
	OCR1A = 128;
}



void initPWM(){
	init_puertos();
	initADC();
}

void PWM_soft_Update(){
	if (++PWM_position>=PWM_PERIOD)
	PWM_position=0;

	if (PWM_position<=pwm_r)
	PWM_ON;
	else
	PWM_OFF;
}



void actualizar(COLOR *estado){
	valAct = leerPot();
	if (valAct != valAnt){
		salir = 0;
		valAnt = valAct;

		if (*estado == G) // Verde
			OCR1B = valAct;
		else if (*estado == B) // Azul
			OCR1A = valAct;
	}
	
	salir++;
	if (salir >= 30){ //Sale luego de 3 seg de inactividad (main tiene delay de 100ms)
		salir = 0;
		*estado = IDLE;
	}
}

void actualizarSW(COLOR *estado){
	valAct = leerPot();
	if (valAct != valAnt && *estado == R){
		salir = 0;
		valAnt = valAct;
		pwm_r = valAct;
	}
	
	salir++;
	if (salir >= 30){ //Sale luego de 3 seg de inactividad (main tiene delay de 100ms)
		*estado = IDLE;
		salir = 0;
	}
}