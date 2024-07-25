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
	inits();
	timerInit();
	
    while (1) 
    {
		MEF_update();
		_delay_ms(100);
    }
}

ISR(TIMER0_COMPA_vect){
	PWM_soft_Update();
}