#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <avr/io.h> 
#include <string.h>

#define F_CPU 8000000 
#define BUAD 9600 
#define BUAD_RATE_CALC ((F_CPU/16/BUAD) - 1)  

void sendserial(char *);
#endif