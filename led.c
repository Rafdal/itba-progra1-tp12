//
// Created by agussolari on 6/11/21.
//

#include "led.h"
#include "pin_handler.h"

void led(int led)
{
    pinMode(arr[led], "out");
    setPin(arr[led], 1);
    killPin(arr[led] );
}

//Hacer funcion que ponga el led apagado
