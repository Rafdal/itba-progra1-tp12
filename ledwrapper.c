//
// Created by agussolari on 6/11/21.
//

#include "ledwrapper.h"
#include "puerto.h"
#include "pin_handler.h"

#define mascara 0xFFFF //mascara para borrar todos los bits

static int arr[] = {17,4,18,23,24,25,22,27};


// Toggle all emulators
void toggleAll_w(void)
{
    maskToggle(PORT_A, 0xFF);
    printPort(PORT_A);


    // Invierte todos los LEDs de la raspberry
    int l;
    for( l = 0; l < 8 ; l++)
    {
        if( statusPin(arr[l]) ) //Si el led esta prendido
        {
            setPin( arr[l] , 0); //Set bit "l" to 0
        }
        else
        {
            setPin(arr[l], 1); //Set bit "l" to 1
        }
    }
}

// Enciende el PIN (solo enciende)
void setPin_w(uint8_t pin) // Set pin wrapper
{
    bitSet(PORT_A, pin); //uso bitset para encender ese bit del puerto
    printPort(PORT_A);

    int status = pinMode(arr[pin], "out");
    if(!status){
        setPin(arr[pin], true);
    }

    else
	{
        printf("Error pinMode retorno: %u\n", status);
    }
}

void offAll_w(void)
{
    maskOff(PORT_A, mascara);   /*uso maskOff con una mascara la cual
* tiene todos los bits en 1 asi todos los bits del puerto quedan en 0*/
    printPort(PORT_A);

    int j;
    for ( j=0 ;j < 8 ; j++)
    {
        int status = pinMode(arr[j], "out");
        if(!status){
            setPin(arr[j], 0);
        }
        else{
            printf("Error pinMode retorno: %u\n", status);
        }
    }
}

void onAll_w(void)
{
    maskOn(PORT_A, mascara); //Analogo al caso de la letra c pero con la funcion maskOn, que los deja en 1
    printPort(PORT_A);


    int i;
    for ( i=0 ; i < 8; i++)
    {
        int status = pinMode(arr[i], "out");
        if(!status){
            setPin(arr[i], 1);
        }
        else{
            printf("Error pinMode retorno: %u\n", status);
        }

    }
}


void quit_w (void)
{
    int k;
    for(k=0; k < 8 ; k++)
    {
        killPin(arr[k]); //Unexport all led's
    }
}