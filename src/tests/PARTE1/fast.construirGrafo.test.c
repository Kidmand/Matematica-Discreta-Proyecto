#include <stdio.h>
#include "../APIG24.h"

int main()
{
    printf("Test rapido:\n");
    Grafo grafo = ConstruirGrafo();
    if (grafo == NULL)
        return 1;

    printf("\n\nGrafo construido:\n");
    u32 cant_v = NumeroDeVertices(grafo);
    printf("Cantidad de vertices: %u\n", cant_v);
    printf("Cantidad de lados: %u\n\n", NumeroDeLados(grafo));
    for (u32 i = 0; i < cant_v; i++)
    {
        printf("\n---------------\n");
        printf("Vertice ( %u )\n", i);
        printf("Color: %u\n", Color(i, grafo));
        printf("Grado:%u\n", Grado(i, grafo));
        printf("Vecinos: ");
        for (u32 j = 0; j < grafo->vertices[i].grado; j++)
        {
            printf("%u ", grafo->vertices[i].vecinos[j]);
        }
        printf("\n----------------\n");
    }
    DestruirGrafo(grafo);
    return 0;
}

// Ejemplo de ejecución:
// make test FILE=tests/fast.construirGrafo.test.c <./tests/ejemplos_inputs/ejemplo_basico.txt