#include "mini_unit_test.h"

#include "../APIG24.h"

static u32 delta_max(u32 a, u32 b)
{
    return a > b ? a : b;
}

u32 cant_vertices(Grafo graph)
{
    u32 i = 0;
    Vertice *vertices = graph->vertices;

    while (i < graph->cant_vertices && vertices != NULL && vertices[i].id == UINT32_MAX)
    {
        i++;
    }
    return i;
}

u32 cant_lados(Grafo graph)
{
    u32 i = 0;
    u32 cant_lados_aux = 0;

    Vertice *vertices = graph->vertices;

    while (i < graph->cant_vertices && vertices != NULL && vertices[i].id == UINT32_MAX)
    {
        cant_lados_aux += vertices[i].grado;
        i++;
    }

    return ((cant_lados_aux) / 2);
}

u32 delta(Grafo graph)
{
    u32 i = 0;
    u32 z_aux = 0;

    Vertice *vertices = graph->vertices;

    while (i < graph->cant_vertices && vertices != NULL && vertices[i].id == UINT32_MAX)
    {
        z_aux = delta_max(z_aux, vertices[i].grado);
        i++;
    }

    return z_aux;
}

u32 pertenece(u32 a, u32 *vecinos)
{
    while (vecinos != NULL)
    {
        if (vecinos[0] == a)
        {
            return 1;
        }
        else
        {
            vecinos++;
        }
    }
    return 0;
}

u32 espejismo(Grafo graph)
{
    u32 i = 0;
    u32 z = 0;
    u32 z_aux = 0;
    u32 res = 1;

    Vertice *vertices = graph->vertices;

    while (i < graph->cant_vertices && vertices != NULL && vertices[i].id == UINT32_MAX && res)
    {
        while (z < vertices[i].grado && res)
        {
            z_aux = vertices[i].vecinos[z];
            res = pertenece(i, graph->vertices[z_aux].vecinos);
            z++;
        }
        i++;
    }

    return res;
}

Grafo grafo;
// Se definen los tests:
MU_TEST(cant_vertices_error)
{
    mu_assert(cant_vertices(grafo) == grafo->cant_vertices, "Error: La cantidad de vértice no es la esperada.\n");
}

MU_TEST(cant_lados_error)
{
    mu_assert(cant_lados(grafo) == grafo->cant_lados, "Error: Los lados no son los esperados.\n");
}

MU_TEST(delta_error)
{
    mu_assert(delta(grafo) == grafo->delta, "Error: El delta no es el esperado.\n");
}

MU_TEST(espejismo_error)
{
    mu_assert(espejismo(grafo) != 0, "Error: El lado (a,b) existe mientras que el lado (b,a) no.\n");
}

// Se define la suite de tests:
MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(cant_vertices_error);
    MU_RUN_TEST(cant_lados_error);
    MU_RUN_TEST(delta_error);
    MU_RUN_TEST(espejismo_error);
}

int main(int argc, char *argv[])
{
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

/*  Ejemplos de ejecución:
    Status  | Command

    OK      | make test FILE=tests/construirGrafo.test.c < tests/ejemplos_inputs/ejemplo_basico.txt
                    make test-valgrind FILE=tests/construirGrafo.test.out < tests/ejemplos_inputs/ejemplo_basico.txt
    ------------------------------------------------------------------------------------------------------------------
    OK      | make test FILE=tests/construirGrafo.test.c < tests/ejemplos_inputs/4CBQ10.txt
                    make test-valgrind FILE=tests/construirGrafo.test.out < tests/ejemplos_inputs/4CBQ10.txt
    ------------------------------------------------------------------------------------------------------------------
    OK      | make test FILE=tests/construirGrafo.test.c < tests/ejemplos_inputs/8suCBQ10.txt
                    make test-valgrind FILE=tests/construirGrafo.test.out < tests/ejemplos_inputs/8suCBQ10.txt
    ------------------------------------------------------------------------------------------------------------------
    OK      | make test FILE=tests/construirGrafo.test.c < tests/ejemplos_inputs/64gb.txt
                    make test-valgrind FILE=tests/construirGrafo.test.out < tests/ejemplos_inputs/64gb.txt
    ------------------------------------------------------------------------------------------------------------------
    OK      | make test FILE=tests/construirGrafo.test.c < tests/ejemplos_inputs/grafo_chico.txt
                    make test-valgrind FILE=tests/construirGrafo.test.out < tests/ejemplos_inputs/grafo_chico.txt
    ------------------------------------------------------------------------------------------------------------------
    OK      | make test FILE=tests/construirGrafo.test.c < tests/ejemplos_inputs/K5_con_lados_de_mas.txt
                    make test-valgrind FILE=tests/construirGrafo.test.out < tests/ejemplos_inputs/K5_con_lados_de_mas.txt
    ------------------------------------------------------------------------------------------------------------------
    OK      | make test FILE=tests/construirGrafo.test.c < tests/ejemplos_inputs/K5.txt
                    make test-valgrind FILE=tests/construirGrafo.test.out < tests/ejemplos_inputs/K5.txt
    ------------------------------------------------------------------------------------------------------------------
    OK      | make test FILE=tests/construirGrafo.test.c < tests/ejemplos_inputs/PGJ10_500.txt
                    make test-valgrind FILE=tests/construirGrafo.test.out < tests/ejemplos_inputs/PGJ10_500.txt
    ------------------------------------------------------------------------------------------------------------------
    OK      | make test FILE=tests/construirGrafo.test.c < tests/ejemplos_inputs/ejemplo_con_error.txt
                    make test-valgrind FILE=tests/construirGrafo.test.out < tests/ejemplos_inputs/ejemplo_con_error.txt
 */