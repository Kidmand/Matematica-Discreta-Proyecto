#include "../mini_unit_test.h"
#include "../../API2024Parte2.h"
#include <stdint.h>

Grafo grafo;

// Inicializacion de valores esperados (argumentos, variables globales)
u32 numeroCromatico = MAX_u32;
u32 *orden = NULL;
u32 *coloreo = NULL;

// Se definen los tests:
MU_TEST(test_greedy)
{
    u32 res = Greedy(grafo, orden);
    u32 error = MAX_u32;
    char mensaje[100];
    mu_assert(res != error, "La funcion greedy dio error. <-- ⛔\n");
    sprintf(mensaje, "El número cromático es %u y se espera %u. <-- ⛔\n", res, numeroCromatico);
    mu_assert(res == numeroCromatico, mensaje);
    for (u32 i = 0; i < NumeroDeVertices(grafo); i++)
    {
        u32 vertice = orden[i];
        u32 color = Color(orden[i], grafo);
        u32 color_esperado = coloreo[i];
        char mensaje[100];
        sprintf(mensaje, "El color del vertice %u es %u y se espera %u. <-- ⛔\n", vertice, color, color_esperado);
        mu_assert(color == color_esperado, mensaje);
    }
    for (u32 i = 0; i < NumeroDeVertices(grafo); i++)
    {
        u32 vertice = orden[i];
        u32 color = Color(orden[i], grafo);
        char mensaje[100];
        sprintf(mensaje, "El color del vertice %u es %u. <-- ⛔\n", vertice, color);
        mu_assert(color != 0, mensaje);
    }
    printf("\nColoreo de Greedy: [");
    for (u32 i = 0; i < NumeroDeVertices(grafo) - 1; i++)
    {
        printf("'%u', ", Color(orden[i], grafo));
    }
    printf("'%u']\n", Color(orden[NumeroDeVertices(grafo) - 1], grafo));
}

// Se define la suite de tests:
MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_greedy);
}

int main(u32 argc, char *argv[])
{
    if (argc % 2 != 0 || argc <= 3)
    {
        printf("El numero de argumentos esta mal!\n");
        printf("Posibles causas: |zs|!=|ys| o no pasaron x\n");
        exit(1);
    }
    u32 n = argc / 2 - 1;
    orden = (u32 *)malloc(n * sizeof(u32));
    if (orden == NULL)
        exit(1);
    coloreo = (u32 *)malloc((n * sizeof(u32)));
    if (coloreo == NULL)
    {
        free(orden);
        exit(1);
    }

    numeroCromatico = atoi(argv[1]);
    /// printf("numeroCromatico = %u\n", numeroCromatico);
    for (u32 i = 2; i < argc / 2 + 1; i++)
    {
        u32 j = i - 2;
        orden[j] = atoi(argv[i]);
        // printf("orden[%u] = %u\n", j, orden[j]);
    }
    for (u32 i = argc / 2 + 1; i < argc; i++)
    {
        u32 j = i - n - 2;
        coloreo[j] = atoi(argv[i]);
        // printf("coloreo[%u] = %u\n", j, coloreo[j]);
    }

    grafo = ConstruirGrafo();
    if (grafo == NULL)
    {
        printf("No se pudo construir el grafo.\n");
        free(coloreo);
        free(orden);
        exit(1);
    }

    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    DestruirGrafo(grafo);
    free(orden);
    free(coloreo);

    return 0;
}

/*
DOC:
Formato:
./greedy.test.out z ys xs < grafo.txt
x: numero cromatico esperado ej: 3
ys: orden[] para greedy ej: 1 2 3 4 5 6 7 8
zs: colores esperados para cada vertice (en el mismo orden) ej: 1 2 2 1 2 3 3 1

Ejemplo de compilacion y ejecucion:
    make test-compile FILE=tests/PARTE2/greedy.tests.c

                                   x    ys     zs
                                   | |-----| |-----|
    ./tests/PARTE2/greedy.test.out 4 0 1 2 3 1 2 3 4 < tests/PARTE2/inputs/ejemplo_basico.txt
*/