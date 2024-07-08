/*
 * MEF.c
 *
 * Created: 8/7/2024 14:20:13
 *  Author: Barcala
*/
#include "MEF.h"
#include "serialPort.h"
#include "timer.h"
#include <avr/io.h>

typedef enum{R, G, B, IDLE} COLOR;
	
static COLOR estado = IDLE;
//static uint8_t red=0, green=0, blue=0, 
static uint8_t letra;

static uint8_t salir, valAnt=0, valAct=0;

void Actualizar(uint8_t);
/*
Puerto B
Rojo : 5
Verde : 2
Azul : 1
*/

void initADC(){
	DDRC &= ~( 1<<PORTC3);
	ADCSRA = 0x87;//make ADC enable and select ck/128
	ADMUX = 0x03;//Ref external VCC, ADC3, right-justified
}

uint8_t leerPot(){
	uint8_t val;
	ADCSRA |= (1<<ADSC);//start conversion
	while((ADCSRA&(1<<ADIF))==0); //wait for end of conversion
		ADCSRA |= (1<<ADIF); //clear the ADIF flag
	val = (ADCW*10)/93;// adc value/9.3
	return val;
}

void actualizar(uint8_t Puerto){
	valAct = leerPot();
	if (valAct != valAnt){
		salir = 0;
		valAnt = valAct;
	}
	
	PORTB &= ~(1<<Puerto);
	
	salir++;
	if (salir >= 50) //Sale luego de 5 seg de inactividad (main tiene delay de 100ms)
		estado = IDLE;
}

void Init_consola(){
		SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
		SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
		SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
		//SerialPort_Send_String(msg1);   // Envío el mensaje de Bienvenida

		
}

uint8_t leerConsola(uint8_t letra){

	SerialPort_Wait_Until_New_Data();	  // Pooling - Bloqueante, puede durar indefinidamente.
	letra = SerialPort_Recive_Data();
	
	if(letra == 'R' || letra == 'G' || letra == 'B' || letra == 'r' || letra == 'g' || letra == 'b'){
		if (letra == 'r' || letra == 'g' || letra == 'b')
			letra-=32;		//se pasa a mayusculas segun tabla ascii				
		return 1;
	}
	else return 0;
}

void MEF_update(){
	switch (estado){
		case R:
			actualizar(PORTB5);
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
