/*
 * MEF.c
 *
 * Created: 8/7/2024 14:20:13
 *  Author: Barcala
*/
#include "MEF.h"
#include "serialPort.h"

#include <stdio.h>

#define PWM_PERIOD 256 // Periodo PWM de 8 bits
#define PWM_START DDRB |= (1 << PB5) // Configurar PB5 como salida
#define PWM_OFF PORTB &= ~(1 << PB5)
#define PWM_ON PORTB |= (1 << PB5)

static uint8_t pwm_r = 128; // Duty cycle inicial para rojo (PB5)

static uint8_t PWM_position=0;


typedef enum{R, G, B, IDLE} COLOR;
	
static COLOR estado = IDLE;
static uint8_t letra;

static uint8_t salir, valAnt=0, valAct=0;



void PWM_soft_Update(){
	if (++PWM_position>=PWM_PERIOD)
		PWM_position=0;

	if (PWM_position<pwm_r)
		PWM_ON;
	else
		PWM_OFF;
}
			
void init_puertos(){	
	DDRB |= (1<<PORTB1 | 1<<PORTB2 | 1<<PORTB5);
}
void initADC(){
	DDRC &= ~( 1<<PORTC3);
	ADCSRA = 0x87;//make ADC enable and select ck/128
	ADMUX = 0x03;//Ref external VCC, ADC3, right-justified
}
void Init_consola(){
	SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
}

void inits(){
	init_puertos();
	initADC();
	Init_consola();
}

//uint8_t leerPot(){
	//uint8_t val;
	//ADCSRA |= (1<<ADSC);//start conversion
	//while((ADCSRA&(1<<ADIF))==0); //wait for end of conversion
		//ADCSRA |= (1<<ADIF); //clear the ADIF flag
	//val = (ADCW*10)/93;// adc value/9.3
	//return val;
//}

uint8_t leerPot(){
	uint8_t val;
	ADCSRA |= (1<<ADSC); // Iniciar conversión
	while((ADCSRA & (1<<ADIF)) == 0); // Esperar a que termine la conversión
	ADCSRA |= (1<<ADIF); // Limpiar la bandera ADIF
	val = (ADCW * 255) / 1023; // Escalar el valor ADC al rango 0-255
	return val;
}

void actualizar(uint8_t Puerto){
	valAct = leerPot();
	if (valAct != valAnt){
		salir = 0;
		valAnt = valAct;
		if(Puerto == PORTB2) //Verde
			OCR1B = valAct;
		else
			if (Puerto == PORTB1) //Azul
				OCR1A = valAct;
	}
	
	salir++;
	if (salir >= 50) //Sale luego de 5 seg de inactividad (main tiene delay de 100ms)
		estado = IDLE;
}

void actualizarSW(){
	valAct = leerPot();
	if (valAct != valAnt){
		salir = 0;
		valAnt = valAct;
		pwm_r = valAct;
	}
	
	salir++;
	if (salir >= 50) //Sale luego de 5 seg de inactividad (main tiene delay de 100ms)
	estado = IDLE;
}

uint8_t leerConsola(uint8_t letra){

	SerialPort_Wait_Until_New_Data();	  // Pooling - Bloqueante, puede durar indefinidamente.
	letra = SerialPort_Recive_Data();	
	
	if(letra == 'R' || letra == 'G' || letra == 'B' || letra == 'r' || letra == 'g' || letra == 'b'){
		if (letra == 'r' || letra == 'g' || letra == 'b')
			letra-=32;		//se pasa a mayusculas segun tabla ascii		
			
		char  msg1[50];
		sprintf(msg1, "\r\nTecla presionada: %c \r\n",letra);
		
		SerialPort_Wait_For_TX_Buffer_Free(); // Espero a que el canal de transmisión este libre (bloqueante)
		SerialPort_Send_String(msg1);
					
		return 1;
	}
	else return 0;
}

void MEF_update(){
	switch (estado){
		case R:
			actualizarSW();
			break;
		case G:
			actualizar(PORTB2);
			break;
		case B:
			actualizar(PORTB1);
			break;
		case IDLE:
			if(leerConsola(letra)){
				estado=letra;
				salir = 0;
			}
			break;
	}
}
