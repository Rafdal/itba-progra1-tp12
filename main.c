/*           			   TRABAJO PRÁCTICO N.º 12
 * Consigna: Lo que se pide es escribir este tercer módulo (que se ejecutara en la RPI).
* Se deberá integrar este módulo con el de visualización por consola de manera que todos los
* comandos que se reciba por teclado se vea reflejado tanto en la consola como en el
* hardware real.
 *
 *
 * Dependencias: A continuation se especifican las dependencias para la correcta ejecución del programa
 *
 *			1. pin_handler.c & pin_handler.h
 *			2. led.c & led.h
 *			3. puerto.c & puerto.h
 *			4. ledwrapper.c & ledwrapper.h
 *
 *
 *
 * Adicionales: A continuacion se describen los adicionales del programa
 *
 * 			1. Debug: Para ver los estados de los archivos (si se exportaron, si el archivo se abrio correctamente), para ello
 * 				definir la constante DEBUG, de caso contrario no mostrara estos estados
 *
 *
 */

#include <stdio.h>
#include "ledwrapper.h"

#undef DEBUG



	/************************/
	/* 			MAIN		*
	/************************/

int main(void)
{
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

		//Recibe letra "t"
        if(c== 't')     //si es el comando t, uso la funcion bitToggle...
		{
			printf("Nuevo estado de los LEDs:  ");

			toggleAll_w(); // Toggle Wrapper
		}

		//Recibe Numero
        else if (c>='0' && c<'8') // si es un numero ingresado  por teclado
        {
            c -= '0';    //traduzco de ASCII a numero
            printf("Nuevo estado de los LEDs:  ");

            setPin_w(c);	//Recibe un numero de bit y lo prende en la la consola y en el RaspberryPi
        }

		//Recibe letra "c"
        else if(c=='c') //si es 'c', debo apagar todos los bits
        {
			printf("Nuevo estado de los LEDs:  ");

            offAll_w();	//Apaga todos los leds de la consola y del RaspberryPi
        }

		//Recibe letra "s"
        else if (c== 's')   //si la letra es 's', todos los bits deben encenderse
        {
            printf("Nuevo estado de los LEDs:  ");

            onAll_w();	//Prende todos los leds
        }

		//Recibe letra "q"
        else if (c=='q') //solo si se oprime 'q' se debe terminar la ejecucion
        {
            printf("Se ha terminado la ejecucion del programa\n");

            quit_w(); //Unexport all leds
            return 0;                                              //asi que dejo un mensaje y hago un return
        }

		//Recibe cualquier otro caracter que no sea los anteriores
        else if (c!='\n') //el enter queda en el buffer de entrada asi que lo ignoro
        {
            printf("El comando %c no es valido\n", c);  //si no es un comando permitido lo rechazo y busco otro
        }
        
    }
}

