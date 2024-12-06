#include "../../../API2024Parte2.h"
#include <stdint.h>

Grafo grafo;

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("El numero de argumentos esta mal!\n");
        printf("No deben pasarse argumentos\n");
        exit(1);
    }

    grafo = ConstruirGrafo();
    if (grafo == NULL)
    {
        printf("No se pudo construir el grafo.\n");
        exit(1);
    }

    u32 numeroDeVertices = NumeroDeVertices(grafo);
    u32 *orden = malloc(numeroDeVertices * sizeof(u32));

    // FIXME: esta funcion deben estar en el API2024Parte2.h, luego reemplazarlas
    // Orden de los naturales
    for (u32 i = 0; i < numeroDeVertices; i++)
    {
        orden[i] = i;
    }

    // Coloreamos con Greedy
    u32 res = Greedy(grafo, orden);
    u32 error = MAX_u32;
    if (res == error)
    {
        free(orden);
        printf("Error en greedy.\n");
        exit(1);
    }

    // Orden GulDukat
    char cres = GulDukat(grafo, orden);
    char cerror = '1';
    if (cres == cerror)
    {
        printf("Error en GulDukat.\n");
        free(orden);
        exit(1);
    }

    // NOTE: Verificamos que los vertices de un mismo color esten juntos.
    u32 *presentes = (u32 *)calloc(numeroDeVertices, sizeof(u32));
    if (presentes == NULL)
    {
        free(orden);
        exit(1);
    }
    for (u32 i = 1; i < numeroDeVertices; i++)
    {
        if (Color(orden[i - 1], grafo) != Color(orden[i], grafo))
        {
            presentes[orden[i - 1]] = 1;
        }

        if (presentes[orden[i]] != 0)
        {
            printf("Error en GulDUkat, existe algun vertice de un color separado de los demas vertices de su color\n");
            free(orden);
            free(presentes);
            exit(1);
        }
    }
    free(presentes);

    // NOTE: Verificamos que este ordenados por [d4 | d2_no_d4 | impar]
    u32 seccion_d4 = 1;       // TRUE
    u32 seccion_d2_no_d4 = 0; // FALSE
    u32 seccion_impar = 0;    // FALSE
    for (u32 i = 0; i < numeroDeVertices; i++)
    {
        if (seccion_d4 + seccion_d2_no_d4 + seccion_impar != 1)
        {
            printf("Error en las secciones de GulDUkat\n");
            free(orden);
            exit(1);
        }

        if (seccion_d4)
        {
            if (Color(orden[i], grafo) % 4 != 0)
            {
                seccion_d4 = 0;
                seccion_d2_no_d4 = 1;
            }
        }
        else if (seccion_d2_no_d4)
        {
            if (Color(orden[i], grafo) % 4 == 0)
            {
                printf("Error en los d2 no d4 de GulDUkat\n");
                free(orden);
                exit(1);
            }
            if (Color(orden[i], grafo) % 2 != 0)
            {
                seccion_d2_no_d4 = 0;
                seccion_impar = 1;
            }
        }
        else if (seccion_impar)
        {
            if (Color(orden[i], grafo) % 2 == 0)
            {
                printf("Error en los impares de GulDUkat\n");
                free(orden);
                exit(1);
            }
        }
        else
        {
            printf("Error en las secciones de GulDUkat\n");
            free(orden);
            exit(1);
        }
    }

    // NOTE: Verificamos que todos lo colores tengan almenos 1 vertice
    u32 *cant_verticeXcolor = (u32 *)calloc(res, sizeof(u32));
    if (cant_verticeXcolor == NULL)
    {
        free(orden);
        exit(1);
    }
    for (u32 i = 0; i < numeroDeVertices; i++)
    {
        cant_verticeXcolor[Color(orden[i], grafo) - 1]++;
    }
    for (u32 i = 0; i < res; i++)
    {
        if (cant_verticeXcolor[i] == 0)
        {
            printf("Error en GulDukat, hay un color sin vertices.\n");
            free(orden);
            free(cant_verticeXcolor);
            exit(1);
        }
    }
    free(cant_verticeXcolor);

    // NOTE: Verificamos que si volvemos a correr greedy nos deveria dar un coloreo <= al anterior.
    u32 res2 = Greedy(grafo, orden);
    if (res2 == error)
    {
        printf("Error en greedy.\n");
        free(orden);
        exit(1);
    }
    if (res2 > res)
    {
        printf("Error de coloreo en greedy.\n");
        free(orden);
        exit(1);
    }

    DestruirGrafo(grafo);
    free(orden);
    return 0;
}

/*
DOC:
Formato:
./GulDukat.perf.out n < grafo.txt
n: cantidad de vertices del grafo

Ejemplo de compilacion y ejecucion:
    make test-compile FILE=tests/PARTE2/perf/orden_GulDukat.perf.c

    ./tests/PARTE2/perf/GulDukat.perf.out < tests/PARTE2/inputs/ejemplo_basico.txt
*/