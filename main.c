#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pin_handler.h"

int arr[] = {17,4,18,23,24,25,22,27};

int main(void)
{
    for (int i = 0 ; i<8 ; i++)
    {
        pinMode(arr[i], "out");
        setPin(arr[i], 1);
    }

    return 0;
}
