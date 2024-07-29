/*
 * MEF.h
 *
 * Created: 8/7/2024 14:20:29
 *  Author: Barcala
*/


#ifndef MEF_H_
#define MEF_H_
#define BR9600 (0x67)	//para la consola
#define F_CPU 16000000UL

#include <avr/io.h>

void MEF_update(void);

void inits(void);

void PWM_soft_Update(void);

typedef enum{R, G, B, IDLE} COLOR;

#endif /* MEF_H_ */
