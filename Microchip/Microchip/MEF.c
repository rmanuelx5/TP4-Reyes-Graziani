/*
 * MEF.c
 *
 * Created: 8/7/2024 14:20:13
 *  Author: Barcala
*/
#include "MEF.h"
#include "serialPort.h"
#include "PWM.h"

#include <string.h>
#include <stdio.h>
	
static COLOR estado = IDLE;

void Init_consola(){
	SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
}

void inits(){
	Init_consola();
	initPWM();
}

uint8_t leerConsola(){

	SerialPort_Wait_Until_New_Data();	  // Pooling - Bloqueante, puede durar indefinidamente.
	uint8_t letra = SerialPort_Recive_Data();	
	
	if(letra == 'R' || letra == 'G' || letra == 'B' || letra == 'r' || letra == 'g' || letra == 'b'){
		if (letra == 'r' || letra == 'g' || letra == 'b')
			letra-=32;		//se pasa a mayusculas segun tabla ascii		
			
		char msg1[100]; // Aumenta el tamaño del buffer para el mensaje completo

		// Construir el mensaje dependiendo de la letra recibida
		switch (letra) {
			case 'R':
			strcpy(msg1, "\r\nCambiando LED: Rojo (esperar 3 segundos para volver a elegir)\r\n");
			estado = R;
			break;
			case 'G':
			strcpy(msg1, "\r\nCambiando LED: Verde (esperar 3 segundos para volver a elegir)\r\n");
			estado = G;
			break;
			case 'B':
			strcpy(msg1, "\r\nCambiando LED: Azul (esperar 3 segundos para volver a elegir)\r\n");
			estado = B;
			break;
		}
		
		SerialPort_Wait_For_TX_Buffer_Free(); // Espero a que el canal de transmisión este libre (bloqueante)
		SerialPort_Send_String(msg1);
					
		return 1;
	}
	else return 0;
}

void MEF_update(){
	char msg1[100];
	switch (estado){
		case R:
			actualizarSW(&estado);
			break;
		case G:
			actualizar(&estado);
			break;
		case B:
			actualizar(&estado);
			break;
		case IDLE:
			strcpy(msg1, "\r\nElija el color a modificar\r\n");
			SerialPort_Wait_For_TX_Buffer_Free(); // Espero a que el canal de transmisión este libre (bloqueante)
			SerialPort_Send_String(msg1);
			
			leerConsola();
			
			break;
	}
}
