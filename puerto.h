/*
*           HEADER DE EJERCICIO 4 
*/

#ifndef PUERTO_H
#define PUERTO_H


enum {PORT_A, PORT_B, PORT_D};

//***********************
//*	Prototipos	*
//***********************

void bitSet(uint8_t port, uint8_t n_bit);
void bitClr(uint8_t port, uint8_t n_bit);
void bitToggle(uint8_t port, uint8_t n_bit);
uint8_t bitGet(uint8_t port, uint8_t n_bit);

void printPort(uint8_t port); // Imprime todos los bits del puerto seleccionado

void maskOn(uint8_t port, uint16_t mask);
void maskOff(uint8_t port, uint16_t mask);
void maskToggle(uint8_t port, uint16_t mask);


#endif




