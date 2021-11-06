/*
*		CONSIGNA EJERICIO 4
*  Se pide escirbir una libreria que permita emular el funcionamiento de los puertso A, B y D. Siendo A y B puertos de 8 bits, y D de 16 bits.
*	Requerimientos:
*			1. Libreria "stdint.h" 
* 
*	Para usarla dentro de un proyecto solo basta con incluir el header en el main del proyecto.
*/

#include <stdio.h>
#include "stdint.h"
#include "puerto.h"	//Libreria de emulacion de puerto

//***********************
//*	Variables	*
//***********************


typedef struct	    //Definimos una estructura que contiene los puerto A y B
{
    uint8_t B;
    uint8_t A;
}puerto_t;

static union PortD  //Definimos una union compuesta por los Puertos A y B mas un dato de 16 bits, el cual nos permitira acceder a un PuertoD
{
    puerto_t port;
    uint16_t portD;
} gpio;



//***********************
//*	Funciones	*
//***********************

// • bitSet: Dado un puerto y un número de bit, debe cambiar su estado a 1.
// • bitClr: Dado un puerto y un número de bit, debe cambiar su estado a 0.
// • bitGet: Dado un puerto y un número de bit, debe devolver su valor.
// • bitToggle: Dado un puerto y un numero de bit, debe cambiar al estado opuesto en el que esta.

void bitSet(uint8_t port, uint8_t n_bit)
{
    switch (port)   //Hacemos un Switch Case dependiendo el puerto a trabajar
    {
    case PORT_A:
        gpio.port.A |= 0x1 << n_bit;	//Shifteo tantas veces el numero 1 como el numero de bit al que queremos cambiar indica, y luego hacemos un OR para que solo cambie ese bit
        break;

    case PORT_B:
        gpio.port.B |= 0x1 << n_bit;
        break;

    case PORT_D:
        gpio.portD |= 0x1 << n_bit;
        break;

    default:
        break;
    }
}

// Imprime todos los bits del puerto seleccionado
void printPort(uint8_t port)
{
    if (port == PORT_A || port == PORT_B)
    {
        for(int n=7; n>=0 ; n--)        //imprimo en pantalla el valor de los bits del puerto
        {
            uint8_t bit= bitGet(port, n); //con un ciclo donde obtenemos el valor de los bits
            printf("%u", bit);
        }
    }
    else if(port == PORT_D)
    {
        for(int n=15; n>=0 ; n--)        //imprimo en pantalla el valor de los bits del puerto
        {
            uint8_t bit= bitGet(port, n); //con un ciclo donde obtenemos el valor de los bits
            printf("%u ", bit);
        }
    }
    putchar('\n');
}

void bitClr(uint8_t port, uint8_t n_bit)
{
    switch (port)
    {
    case PORT_A:
        gpio.port.A &= ~(0x1 << n_bit); //Shifteamos tantas veces el nuemero 1 como el numero de bit nos indica, y luego le realizamos un complemento a uno para que se inviertan los bits
        break;				// Y poder hacer un AND  con el valor actual del puerto y la mascara, esto nos permitira poner solamente el bit indicado en cero

    case PORT_B:
        gpio.port.B &= ~(0x1 << n_bit);
        break;

    case PORT_D:
        gpio.portD &= ~(0x1 << n_bit);
        break;

    default:
        break;
    }
}

uint8_t bitGet(uint8_t port, uint8_t n_bit)
{
    uint8_t out=0;
    switch (port)
    {
    case PORT_A:
        out = (gpio.port.A & (0x1 << n_bit)) >> n_bit; //Primero shifteamos tantas veces el numero 1 como el numero de bit nos indica, luego haciendo un AND con el valor actual del puerto 
        break;			    //logramos limpiar aquellos bits que no es el indicado y luego shiftenado a la derecha el valor tantas veces como el numero de bit nos indica, logramos obtener el valor del bit
			
    case PORT_B:	
        out = (gpio.port.B & (0x1 << n_bit)) >> n_bit;
        break;

    case PORT_D:
        out = (gpio.portD & (0x1 << n_bit)) >> n_bit;
        break;

    default:
        break;
    }
    return out;	    //Guardamos el valor en una variable y la devolvemos por la funcion
}

void bitToggle(uint8_t port, uint8_t n_bit)
{
    switch (port)
    {
    case PORT_A:
        gpio.port.A ^= (0x1 << n_bit);	//Shifteamos el numeor 1 tantas veces como el numero de bit a modificar nos indica, luego con esta mascara hacemos un XOR y cambiamos su valor al contrario al que tenia
        break;

    case PORT_B:
        gpio.port.B ^= 0x1 << n_bit;
        break;

    case PORT_D:
        gpio.portD ^= 0x1 << n_bit;
        break;

    default:
        break;
    }
}

// • maskOn: Dado un puerto y una máscara, debe prender todos aquellos bits que
// estén prendidos en la máscara.

// • maskOff: Dado un puerto y una máscara, debe apagar todos aquellos bits que
// estén prendidos en la máscara, sin cambiar el estado de los restantes.

// • maskToggle: Dado un puerto y una máscara, debe cambiar el estado de todos
// aquellos bits que estén prendidos en la máscara al opuesto, sin cambiar el
// estado de los restantes.

void maskOn(uint8_t port, uint16_t mask)
{
    switch (port)
    {
    case PORT_A:
        gpio.port.A |= mask; 	//A partir de una mascara recibida, lo que hace esta funcion es prender todos aquellos bits que esten prendidos en la mascara, para ello hacemos un OR entre el valor actual del puerto y de la mascara
        break;

    case PORT_B:
        gpio.port.B |= mask;
        break;

    case PORT_D:
        gpio.portD |= mask;
        break;

    default:
        break;
    }
}


void maskOff(uint8_t port, uint16_t mask) 
{
    switch (port)
    {
    case PORT_A:
        gpio.port.A &= ~mask;	//A partir de una mascara dada, apagamos todos los bits que esten predidos en la mascara, para ello hacemos un complemento a uno al valor de la mascara, invirtiendo todos sus bits
        break;			//Y luego realizamos un XOR con el valor actual y el de la mascara, esto tiene como finalidad cambiar los bits del puerto de solo aquellos bits que esten prendidos en la mascara 

    case PORT_B:
        gpio.port.B &= ~mask;
        break;

    case PORT_D:
        gpio.portD &= ~mask;
        break;

    default:
        break;
    }
}

void maskToggle(uint8_t port, uint16_t mask)
{
    switch (port)
    {
    case PORT_A:
        gpio.port.A ^= mask; 	//A partir de una mascara dada realizamos un operacion de XOR entre el valor de la mascara y el valor actual del puerto, con esto logramos unicamente invertir aquellos bits del puerto que esten prendidos en la mascara
        break;

    case PORT_B:
        gpio.port.B ^= mask;
        break;

    case PORT_D:
        gpio.portD ^= mask;
        break;

    default:
        break;
    }
}
