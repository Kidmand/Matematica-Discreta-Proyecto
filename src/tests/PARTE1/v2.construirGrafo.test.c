#include "mini_unit_test.h"

#include "../APIG24.h"
#include <stdint.h>

Grafo grafo;

u32 vertices_esperados = MAX_u32;
u32 lados_esperados = MAX_u32;
u32 delta_esperado = MAX_u32;

// Se definen los tests:
MU_TEST(cant_vertices)
{
    mu_assert(NumeroDeVertices(grafo) == vertices_esperados, "Error: La cantidad de vértice no es la esperada.\n");
}

MU_TEST(cant_lados)
{
    mu_assert(NumeroDeLados(grafo) == lados_esperados, "Error: Los lados no son los esperados .\n");
}

MU_TEST(delta)
{
    mu_assert(Delta(grafo) == delta_esperado, "Error: El delta no es el esperado.\n");
}

MU_TEST(delta_recalculado)
{
    u32 delta = Delta(grafo);
    u32 delta_aux = 0;
    u32 grado_aux = 0;
    for (u32 i = 0; i < NumeroDeVertices(grafo); i++)
    {
        grado_aux = Grado(i, grafo);
        if (grado_aux > delta_aux)
            delta_aux = grado_aux;
    }
    mu_assert(delta == delta_aux, "Error: El delta recalculado no coindide.\n");
}

MU_TEST(vecinos_correctos_y_espejismo)
{
    u32 check_vecinos = 1; // true
    for (u32 i = 0; i < NumeroDeVertices(grafo) && check_vecinos; i++)
    {
        for (u32 j = 0; j < Grado(i, grafo) && check_vecinos; j++)
        {

            u32 v = Vecino(j, i, grafo);
            if (v == UINT32_MAX)
            {
                check_vecinos = 0;
                break;
            }
            u32 existe_i_en_j = 0; // false
            for (u32 h = 0; h < Grado(v, grafo); h++)
            {
                if (Vecino(h, v, grafo) == i)
                {
                    existe_i_en_j = 1; // true
                    break;
                }
            }
            if (!existe_i_en_j)
            {
                check_vecinos = 0;
                break;
            }
        }
    }
    mu_assert(check_vecinos == 1, "Error: Algun vecino no es correcto.\n");
}

MU_TEST(cantidad_de_lados)
{
    u32 lados = 0;
    for (u32 i = 0; i < NumeroDeVertices(grafo); i++)
    {
        lados += Grado(i, grafo);
    }
    mu_assert(lados / 2 == NumeroDeLados(grafo), "Error: La cantidad de lados no es correcta.\n");
}

MU_TEST(coloreo_vacio)
{
    color *c = malloc(NumeroDeVertices(grafo) * sizeof(color));
    ExtraerColores(grafo, c);
    u32 check = 1;
    for (u32 i = 0; i < NumeroDeVertices(grafo) && check; i++)
    {
        check = check && c[i] == 0;
    }
    free(c);
    mu_assert(check, "Error: Los colores no son 0 al inicializar.\n");
}

MU_TEST(coloreo_correcto)
{
    for (u32 i = 0; i < NumeroDeVertices(grafo); i++)
    {
        AsignarColor(i, i, grafo);
    }

    color *c_asignados = malloc(NumeroDeVertices(grafo) * sizeof(color));

    ExtraerColores(grafo, c_asignados);
    u32 check = 1;
    for (u32 i = 0; i < NumeroDeVertices(grafo) && check; i++)
    {
        check = check && c_asignados[i] == Color(i, grafo) && c_asignados[i] == i;
    }

    free(c_asignados);
    mu_assert(check, "Error: Los colores asignados no coinciden.\n");
}

// Se define la suite de tests:
MU_TEST_SUITE(test_suite)
{
    if (vertices_esperados != UINT32_MAX)
        MU_RUN_TEST(cant_vertices);
    if (lados_esperados != UINT32_MAX)
        MU_RUN_TEST(cant_lados);
    if (delta_esperado != UINT32_MAX)
        MU_RUN_TEST(delta);

    MU_RUN_TEST(delta_recalculado);
    MU_RUN_TEST(vecinos_correctos_y_espejismo);
    MU_RUN_TEST(cantidad_de_lados);
    MU_RUN_TEST(coloreo_vacio);
    MU_RUN_TEST(coloreo_correcto);
}

int main(int argc, char *argv[])
{
    if (argv[1] != NULL)
        vertices_esperados = atoi(argv[1]);
    if (argv[2] != NULL)
        lados_esperados = atoi(argv[2]);
    if (argv[3] != NULL)
        delta_esperado = atoi(argv[3]);

    // printf("Testeando ConstruirGrafo con:\n");
    // if (vertices_esperados != UINT32_MAX)
    //     printf("    Vertices Esperados %u\n", vertices_esperados);
    // if (lados_esperados != UINT32_MAX)
    //     printf("    Lados Esperados %u\n", lados_esperados);
    // if (delta_esperado != UINT32_MAX)
    //     printf("    Delta Esperado %u\n", delta_esperado);

    grafo = ConstruirGrafo();
    if (grafo == NULL)
    {
        printf("Error: No se pudo construir el grafo. ⛔\n");
    }
    else
    {
        MU_RUN_SUITE(test_suite);
        MU_REPORT();
        DestruirGrafo(grafo);
    }
    return 0;
}

/*
Ejemplo de compilacion y ejecucion:
    make test-compile FILE=tests/v2.construirGrafo.test.c

                                       -->cantidad de vertices
                                       | -->cantidad de lados
                                       | |  -->delta
                                       | |  |
    ./tests/v2.construirGrafo.test.out 8 10 3 < tests/ejemplos_inputs/grafo_chico.txt
*/