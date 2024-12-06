#include "../../../API2024Parte2.h"
#include <stdint.h>

//Esta funcion va en API2024Parte2.h"
/*

char Orden_Eleccion(Grafo G, u32 *Orden)
{
    assert(Orden != NULL);
    u32 n = NumeroDeVertices(G);

    // Caso base:
    if (n == 1) // PD: Si n > 1, entonces r > 1.
    {
        Orden[0] = 0;
        return OK;
    }

    // Calculamos r y la cantidad de vertices por color
    u32 r = 1; // cantidad de colores
    u32 *cant_verticesXcolor = (u32 *)calloc(n, sizeof(u32));

    r = Calcular_r(cant_verticesXcolor, r, n, G);

    assert(r >= 2 && r <= n);

    Bloque *arrayN = (Bloque *)calloc(r, sizeof(Bloque));

    // En verticesXbloque se iran guardando los vertices de cada cada color [r1r2,-----,r]
    u32 *verticesXbloque = (u32 *)calloc(n, sizeof(u32));
    if (arrayN == NULL || verticesXbloque == NULL)
    {
        free(arrayN);
        free(cant_verticesXcolor);
        free(verticesXbloque);
        return ERROR;
    }

    // Inicializamos los colores [r1,r2,----,r]
    u32 sum_parcial = 0;
    INIT_BLOCK(arrayN, 0, r, j + 1)
    assert(sum_parcial == n);

    for (u32 v = 0; v < n; v++)
    {
        u32 color = Color(v, G);
        u32 grado = Grado(v, G);

        assert(color > 0 && color <= r);
        // Actualizamos el bloque correspondiente recalculando todo
        putBloqueEG_N(arrayN, color - 1, v, grado);
    }

    // "Concatenamos" los r arreglos anidados de ArrayGD en Orden. O(n)
    u32 suma_parcial = 0;
    for (u32 b = 0; b < r; b++) // O(r) , b = bloque de color.
    {

        Bloque bloque = arrayN[b];

        for (u32 v = 0; v < bloque.cant_vertices; v++) // O(n/r), v = vertice.
        {
            Orden[suma_parcial + v] = bloque.vertices[v];
            assert(Orden[suma_parcial + v] < n);
        }
        suma_parcial += bloque.cant_vertices;
    }

    // Liberamos toda la memoria usada.
    free(arrayN);
    free(cant_verticesXcolor);
    free(verticesXbloque);

    return OK;
}



*/





Grafo grafo;


static u32 contar_colores(u32* orden, u32 n, Grafo grafo) {
    u32 cant_color = 0; 
    for (u32 i=0; i<n; i++) {
        if (Color(orden[i],grafo)!=cant_color) {
            cant_color++;
        }
    }
    return cant_color;
}

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

    for (u32 i = 0; i < numeroDeVertices; i++)
    {
        orden[i] = i;
    }

    u32 res = Greedy(grafo, orden);
    u32 error = MAX_u32;
    if (res == error)
    {
        printf("Error en greedy.\n");
        exit(1);
    }
    // Orden naturales
    char cres = Orden_Naturales(grafo, orden);
    char cerror = '1';
    if (cres == cerror)
    {
        printf("Error en GulDukat.\n");
        free(orden);
        exit(1);
    }

    // NOTE: verificamos que efectivamente esten ordenados como [r1,r2,-----,r] además revisamos si está
    // bien construida la lista

    u32 color = 0; 
    u32 color_aux = 0;
    u32 counter = 0;
    u32 cant_colores = contar_colores(orden, numeroDeVertices, grafo);
    for (u32 i=0; i<cant_colores; i++) {

        while (Color(orden[counter], grafo) == color && counter<numeroDeVertices-1) //nos movemos por lista orden preguntando por el color
        {                                                           
        counter++;
        } 
        color = Color(orden[counter], grafo);   //cuando encontremos un nuevo colo

        if (color-color_aux != 1) 
        {
        printf("Error en en el orden.\n");
        free(orden);
        exit(1);
        } 

        if (counter>=numeroDeVertices) 
        {
        printf("Error en el tamaño.\n");
        free(orden);
        exit(1);
        } 

        color_aux = color;
    }

    u32 res2 = Greedy(grafo, orden);
    if (res2 == error )
    {
        printf("Error en greedy.\n");
        free(orden);
        exit(1);
    }
    printf("\nun coloreo de %d\n\n", res2);
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
./orden_naturales.perf.out n < grafo.txt
n: cantidad de vertices del grafo

Ejemplo de compilacion y ejecucion:
    make test-compile FILE=tests/PARTE2/perf/orden_naturales.perf.c

    ./tests/PARTE2/perf/orden_naturales.perf.out < tests/PARTE2/inputs/ejemplo_basico.txt
*/