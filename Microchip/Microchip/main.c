/*
 * Microchip.c
 *
 * Created: 1/7/2024 15:10:14
 * Author : Barcala
 */ 

#include "MEF.h"
#include <util/delay.h>
#include "timer.h"


int main(void)
{
	inits(); //Inicia consola, puertos, y ADC
	timerInit(); //Inicia interrupciones cada 1ms
	
    while (1) 
    {
		MEF_update();
		_delay_ms(100);
    }
}

ISR(TIMER0_COMPA_vect){
	PWM_soft_Update();
}