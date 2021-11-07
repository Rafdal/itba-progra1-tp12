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
    char *pin_name = malloc(BUFFER * sizeof(char));
    sprintf(pin_name, "%u", pin);
    nWritten = fputs(pin_name, handle);

    if (nWritten == -1)
    {
        printf("Cannot UNEXPORT PIN . Try again later.\n");
        fclose(handle);
    }
    else
    {
#ifdef DEBUG
        printf("UNEXPORT File opened succesfully \n");
#endif
    }
    free(pin_name);
    fclose(handle); // Be carefull do this for EACH pin !!!
    
    return 0;
}

void setPin(unsigned int pin, bool value)
{
    FILE *handle;
    
    char *pin_path = malloc( BUFFER * sizeof(char) );

    sprintf(pin_path, "/sys/class/gpio/gpio%u/value", pin);

    if ((handle = fopen(pin_path, "w")) == NULL)
    {
        printf("Cannot open device. Try again later.\n");
    }
    else
    {
#ifdef DEBUG
        printf("Device successfully opened\n");
#endif
    }
    if (fputc('0'+value, handle) == -1) // Set pin low
    {
        printf("Clr_Pin: Cannot write to file. Try again later.\n");
    }
    else
    {
        fflush(handle);
#ifdef DEBUG
        printf("Write to file %s successfully done.\n", pin_path);
        printf("\n"); //Enter para distinguir comandos de los pines
#endif
    }

    free(pin_path);
    fclose(handle);
}

// retorna 0 si fue exitoso
int pinMode(unsigned int pin, char* direction)
{
    FILE *handle_export;
    int nWritten;
    int statusCode = 0; // Valor retornado por pinMode para saber si salio bien

    if ((handle_export = fopen("/sys/class/gpio/export", "w+")) == NULL)
    {
        printf("Cannot open EXPORT File. Try again later.\n");
        statusCode = 1;
    }

    char *pin_name = malloc(BUFFER * sizeof(char));
    sprintf(pin_name, "%u", pin);
    nWritten = fputs(pin_name, handle_export);

    if (nWritten == -1)
    {
        printf("Cannot EXPORT PIN . Try again later.\n");
        fclose(handle_export);
        statusCode = 2;
    }
    else
    {
#ifdef DEBUG
        printf("EXPORT File opened succesfully, nWritten return %u\n", nWritten);
#endif
    }

    free(pin_name);
    fclose(handle_export); // Be carefull do this for EACH pin !!!

    // *** Set direction *** //
    FILE *handle_direction;

    char *pin_path = malloc( BUFFER * sizeof(char) );

    sprintf(pin_path, "/sys/class/gpio/gpio%u/direction", pin);

    handle_direction = fopen(pin_path, "w+");

    if(handle_direction == NULL)
    {
        printf("Error: %d \n", errno);
        printf("It´s NULL");
    }

    if ((nWritten = fputs(direction, handle_direction)) == -1)
    {
        printf("Cannot open DIRECTION pin. Try again later.\n");
        statusCode = 3;
    }
    else
    {
#ifdef DEBUG
        printf("DIRECTION File for PIN opened succesfully, nWritten return %u\n", nWritten);
#endif
    }

    free (pin_path); //Libera memoria dinámica
    fclose(handle_direction); // Be careful do this for EACH pin !!!
    return statusCode; // retorno si fue exitoso (=0) o no
}

int statusPin (int pin)
{
    FILE *handle;
    bool out = false;

    char *pin_path = malloc( BUFFER * sizeof(char) );

    sprintf(pin_path, "/sys/class/gpio/gpio%u/value", pin);

    if ((handle = fopen(pin_path, "r")) == NULL)
    {
        printf("Cannot open device. Try again later.\n");
    }
    else
    {
#ifdef DEBUG
        printf("Device successfully opened\n");
#endif
    }
    free (pin_path);    //libero memoria dinamica

    if ( fgetc(handle) == '1' )
    {
        out = true;
    }
    else if (fgetc(handle) == '0')
    {
        out = false;
    }

    fclose(handle);
    return out;
}