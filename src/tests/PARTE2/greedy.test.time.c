#include "../mini_unit_test.h"
#include "../../API2024Parte2.h"
#include <stdint.h>

Grafo grafo;

u32 *orden = NULL;

// Se definen los tests:
MU_TEST(test_greedy)
{
    u32 res = Greedy(grafo, orden);
    u32 error = MAX_u32;
    mu_assert(res != error, "La funcion greedy dio error. <-- ⛔\n");
}

// Se define la suite de tests:
MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_greedy);
}

int main(int argc, char *argv[])
{
    grafo = ConstruirGrafo();
    if (grafo == NULL)
    {
        printf("No se pudo construir el grafo.\n");
        exit(1);
    }

    orden = (u32 *)malloc(NumeroDeVertices(grafo) * sizeof(u32));
    if (orden == NULL)
        exit(1);
    for (u32 i = 0; i < NumeroDeVertices(grafo); i++)
    {
        orden[i] = i;
    }

    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    DestruirGrafo(grafo);
    free(orden);

    return 0;
}
/*
DOC:

make test-compile FILE=./tests/PARTE2/greedy.test.time.c

./tests/PARTE2/greedy.test.time.out < ./tests/ejemplos_inputs_extremos/harkon.txt
*/