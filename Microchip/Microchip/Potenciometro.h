/*
 * Potenciometro.h
 *
 * Created: 30/7/2024 16:15:59
 *  Author: manuc
 */ 


#ifndef POTENCIOMETRO_H_
#define POTENCIOMETRO_H_

#include <avr/io.h>

void initADC();

uint8_t leerPot();

#endif /* POTENCIOMETRO_H_ */