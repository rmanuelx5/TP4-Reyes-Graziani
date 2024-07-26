/*
 * timer.h
 *
 * Created: 5/5/2024 14:45:37
 *  Author: manuc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

#ifndef TIMER_H_
#define TIMER_H_


void timer0Init();
void timer1Init();

#endif /* TIMER_H_ */