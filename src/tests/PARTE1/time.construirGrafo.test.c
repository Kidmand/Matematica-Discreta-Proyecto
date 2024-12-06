#include <stdio.h>
#include "../APIG24.h"

int main()
{
    Grafo grafo = ConstruirGrafo();
    DestruirGrafo(grafo);
    return 0;
}

// Ejemplo de complación:
// make test-compile FILE=tests/time.construirGrafo.test.c