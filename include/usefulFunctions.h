#include <time.h>
#include <stdlib.h>

int getRandomNumber(int rangoSuperior, int rangoInferior);

int getRandomNumber(int rangoSuperior, int rangoInferior)
{
    int rango = (rangoSuperior - rangoInferior) + 1;
    return rand() % rango + rangoInferior;
}