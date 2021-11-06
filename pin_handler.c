#include "pin_handler.h"
#include <errno.h>

int killPin(unsigned int pin)
{
    FILE *handle;
    int nWritten;
    if ((handle = fopen("/sys/class/gpio/unexport", "w")) == NULL)
    {
        printf("Cannot open UNEXPORT File. Try again later.\n");
    }
    char *pin_name = malloc(16 * sizeof(char));
    sprintf(pin_name, "%u", pin);
    nWritten = fputs(pin_name, handle);

    if (nWritten == -1)
    {
        printf("Cannot UNEXPORT PIN . Try again later.\n");
        fclose(handle);
    }
    else
    {
        printf("UNEXPORT File opened succesfully \n");
    }
    free(pin_name);
    fclose(handle); // Be carefull do this for EACH pin !!!
    
    return 0;
}

void setPin(unsigned int pin, bool value)
{
    FILE *handle;
    
    char *pin_path = malloc( 64 * sizeof(char) );

    sprintf(pin_path, "/sys/class/gpio/gpio%u/value", pin);

    if ((handle = fopen(pin_path, "w")) == NULL)
    {
        printf("Cannot open device. Try again later.\n");
    }
    else
    {
        printf("Device successfully opened\n");
    }
    if (fputc('0'+value, handle) == -1) // Set pin low
    {
        printf("Clr_Pin: Cannot write to file. Try again later.\n");
    }
    else
    {
        fflush(handle);
        printf("Write to file %s successfully done.\n", pin_path);
        printf("\n"); //Enter para distinguir comandos de los pines
    }

    free(pin_path);
    fclose(handle);
}

int pinMode(unsigned int pin, char* direction)
{
    errno= 0;
    FILE *handle_export;
    int nWritten;

    if ((handle_export = fopen("/sys/class/gpio/export", "w+")) == NULL)
    {
        printf("Cannot open EXPORT File. Try again later.\n");
        return 1; // error
    }

    char *pin_name = malloc(16* sizeof(char));
    sprintf(pin_name, "%u", pin);
    nWritten = fputs(pin_name, handle_export);

    if (nWritten == -1)
    {
        printf("Cannot EXPORT PIN . Try again later.\n");
        fclose(handle_export);
        return 1; // error
    }
    else
    {
        printf("EXPORT File opened succesfully \n");
    }

    free(pin_name);
    fclose(handle_export); // Be carefull do this for EACH pin !!!

    // *** Set direction *** //
    FILE *handle_direction;

    char *pin_path = malloc( 64 * sizeof(char) );

    sprintf(pin_path, "/sys/class/gpio/gpio%u/direction", pin);

    handle_direction = (fopen(pin_path, "w+"));

    if(handle_direction == NULL)
    {
        printf("Error: %d \n", errno);
        printf("It´s NULL");
    }


    if ((nWritten = fputs(direction, handle_direction)) == -1)
    {
        printf("Cannot open DIRECTION pin. Try again later.\n");
        fclose(handle_direction); // Be carefull do this for EACH pin !!!
    }
    else
    {
        printf("DIRECTION File for PIN opened succesfully\n");
    }

    free (pin_path);
    fclose(handle_direction); // Be carefull do this for EACH pin !!!
    return 0;
}

int statusPin (int pin)
{
    FILE *handle;

    char *pin_path = malloc( 64 * sizeof(char) );

    sprintf(pin_path, "/sys/class/gpio/gpio%u/value", pin);

    if ((handle = fopen(pin_path, "w")) == NULL)
    {
        printf("Cannot open device. Try again later.\n");
    }
    else
    {
        printf("Device successfully opened\n");
    }

    if ( fgetc(handle) == '1' )
    {
        return 1;
    }
    return 0;
}