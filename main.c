/*
 *          CONSIGNA EJERCICIO 5
* Escribir un programa que utilice la librería escrita en el ejercicio 4 para simular que se
* tienen 8 LED conectados al puerto A. Se debe usar la librería creada en el ejercicio 1,
* y mostrar el estado de los LED en pantalla.
 */

/* 
* Por teclado, el usuario ingresará el número (del 0 al 7) del LED que se desea
* prender, en tiempo real.
* Con la letra 't', todos los LEDs deben cambiar al estado opuesto (si están encendidos
* apagarse y si están apagados encenderse).
* Con la letra 'c', se deberán apagar todos, y con 's', prender.
* Con la letra 'q', el programa finalizará.
 */

#include <stdio.h>
#include "stdint.h"

#undef DEBUG
#include "ledwrapper.h"


/*
 * 
 */
int main(void) {
    int c;

    printf("Lista de Comandos:\n"); //Imprimo una lista con los comandos posibles para el usuario
    printf("Para numeros del 0 al 7: se enciende el bit del numero ingresado\n");
    printf("La letra \"t\" intercambia el estado de todos los leds\n");
    printf("La letra \"c\" apaga todos los bits\n");
    printf("La letra \"s\" prende todos los bits\n");
    printf("La letra \"r\" lee todos los LEDs de la raspberry\n");
    printf("Presione la letra \"q\" para finalizar del programa\n");
    printf("\nEstado Inicial de los LEDs:   ");

    offAll_w(); // Apaga todos los leds y muestra por pantalla

    while ((c =getchar()))      //Busco el caracter ingresado por el usuario
    {

        if(c== 't')     //si es el comando t, uso la funcion bitToggle...
        {
			printf("Nuevo estado de los LEDs:  ");

            toggleAll_w(); // Toggle Wrapper
        }
        else if (c>='0' && c<'8') // si es un numero ingresado  por teclado
        {
            c -= '0';    //traduzco de ASCII a numero
            printf("Nuevo estado de los LEDs:  ");

            setPin_w(c);
        }
            
        
        else if(c=='c') //si es 'c', debo apagar todos los bits
        {
			printf("Nuevo estado de los LEDs:  ");

            offAll_w();
        } 
        else if (c== 's')   //si la letra es 's', todos los bits deben encenderse
        {
            printf("Nuevo estado de los LEDs:  ");

            onAll_w();
        }
        else if (c=='q') //solo si se oprime 'q' se debe terminar la ejecucion
        {
            printf("Se ha terminado la ejecucion del programa\n");
            quit_w(); //Unexport all leds
            return 0;                                              //asi que dejo un mensaje y hago un return
        }
        else if (c!='\n') //el enter queda en el buffer de entrada asi que lo ignoro
        {
            printf("El comando %c no es valido\n", c);  //si no es un comando permitido lo rechazo y busco otro
        }
        
    }
}

