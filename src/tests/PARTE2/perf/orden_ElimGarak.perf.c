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

    u32 *ordenEG = malloc(numeroDeVertices * sizeof(u32));

    // FIXME: esta funcion deben estar en el API2024Parte2.h, luego reemplazarlas
    // Orden de los naturales
    for (u32 i = 0; i < numeroDeVertices; i++)
    {
        ordenEG[i] = i;
    }

    // Coloreamos con Greedy
    u32 res = Greedy(grafo, ordenEG);
    u32 error = MAX_u32;
    if (res == error)
    {
        free(ordenEG);
        printf("Error en greedy.\n");
        exit(1);
    }

    // Orden ElimGarak

    char cres = ElimGarak(grafo, ordenEG);
    char cerror = '1';
    if (cres == cerror)
    {
        printf("Error en ElimGarak.\n");
        free(ordenEG);
        exit(1);
    }

    // NOTE: Verificamos que los vertices de un mismo color esten juntos.
    u32 *presentes = (u32 *)calloc(numeroDeVertices, sizeof(u32));
    if (presentes == NULL)
    {
        free(ordenEG);
        exit(1);
    }
    for (u32 i = 1; i < numeroDeVertices; i++)
    {
        if (Color(ordenEG[i - 1], grafo) != Color(ordenEG[i], grafo))
        {
            presentes[ordenEG[i - 1]] = 1;
        }

        if (presentes[ordenEG[i]] != 0)
        {
            printf("Error en ElimGarak, existe algun vertice de un color separado de los demas vertices de su color\n");
            free(ordenEG);
            free(presentes);
            exit(1);
        }
    }
    free(presentes);

    // NOTE: Verificamos que los colores esten ordenados de menor a mayor por la cantidad de vertices que tienen
    //       que tiene el mismo color.
    u32 *cant_verticeXcolor = (u32 *)calloc(res, sizeof(u32));
    if (cant_verticeXcolor == NULL)
    {
        free(ordenEG);
        exit(1);
    }
    for (u32 i = 0; i < numeroDeVertices; i++)
    {
        cant_verticeXcolor[Color(ordenEG[i], grafo) - 1]++;
    }

    u32 verticeActual = 0;
    while (verticeActual < numeroDeVertices)
    {
        u32 colorActual = Color(ordenEG[verticeActual], grafo);
        u32 cantDeVerticesDelColorActual = cant_verticeXcolor[colorActual - 1];
        // NOTE: Verificamos que los vertices de un mismo color esten juntos.
        for (u32 i = verticeActual; i < cantDeVerticesDelColorActual; i++)
        {
            if (Color(ordenEG[i], grafo) != colorActual)
            {
                printf("Error en ElimGarak,. Existe un vertice de un color separado de los demas vertices de su color\n");
                free(ordenEG);
                free(cant_verticeXcolor);
                exit(1);
            }
        }
        u32 proximoVerticeDelSiguienteColor = verticeActual + cantDeVerticesDelColorActual;
        u32 colorSiguiente = Color(ordenEG[proximoVerticeDelSiguienteColor], grafo);
        if (colorSiguiente == 1 || colorSiguiente == 2)
            break;
        u32 cantDeVerticesDelSiguienteColor = cant_verticeXcolor[colorSiguiente - 1];

        // printf("colorActual = %u, cantDeVerticesDelColorActual = %u\n", colorActual, cantDeVerticesDelColorActual);

        if (cantDeVerticesDelColorActual > cantDeVerticesDelSiguienteColor)
        {

            printf("Error en ElimGarak, no se respeto el orden de los colores.\n");
            free(ordenEG);
            free(cant_verticeXcolor);
            exit(1);
        }
        verticeActual = proximoVerticeDelSiguienteColor;
    }

    // NOTE: Verificamos que todos los colores tengan almenos 1 vertice:
    for (u32 i = 0; i < res; i++)
    {
        if (cant_verticeXcolor[i] == 0)
        {
            printf("Error en ElimGarak, hay un color sin vertices.\n");
            free(ordenEG);
            free(cant_verticeXcolor);
            exit(1);
        }
    }

    free(cant_verticeXcolor);

    // NOTE: Lo que hace esto es sumarme cuantos vertices ocupan los colores r1 y r2 en la lista ordenEG
    // Entonces nos fijamos en la lista de ordenEG y si encontramos un color r1 o r2 necesariamente tiene que estar en:
    // length(ordenEG) -  cant_color1_2
    // Es decir que el índice de la lista tiene que ser mayor o igual que  length(ordenEG) -  cant_color1_2
    // Ejemplo: Vertice 3 con color 1, verificamos si esta en el rango [0,------,length(ordenEG) - cant_color1_2] o está en el rango
    // [numeroDeVertices - cant_color1_2,------, numeroDevertices] ya que si està en el primer bloque te da error, en cambio
    // si está en el segundo bloque está todo bien.
    u32 cant_color1_2 = 0;
    for (u32 i = 0; i < numeroDeVertices; i++)
    {
        if (Color(ordenEG[i], grafo) == 1 || Color(ordenEG[i], grafo) == 2)
        {
            cant_color1_2++;
        }
    }

    // NOTE: Verificamos que este ordenados por [r3,r4,-----,r,r2,r1]
    for (u32 i = 0; i < numeroDeVertices; i++)
    {
        if (Color(ordenEG[i], grafo) < 3 && i < (numeroDeVertices - cant_color1_2))
        {
            printf("Error(ElimGarak) en la seccion [r3,-----,r]. Se encontró un color = [1,2] en esa seccion\n");
            free(ordenEG);
            exit(1);
        }
        // NOTE: Verificamos que este ordenados los r-2 y r-1
        if (Color(ordenEG[i], grafo) >= 3 && i >= (numeroDeVertices - cant_color1_2))
        {
            printf("Error(ElimGarak) en la seccion [r2,r1]. No se encontraron los colores adecuados.\n");
            free(ordenEG);
            exit(1);
        }
    }

    // NOTE: Verificamos que este ordenados los r-2 y r-1
    if (res > 2 && Color(ordenEG[numeroDeVertices - 2], grafo) != 2 && Color(ordenEG[numeroDeVertices - 1], grafo) != 1)
    {
        printf("Error en la seccion [r2,r1]. No se encontraron los colores adecuados.\n");
        free(ordenEG);
        exit(1);
    }

    // NOTE: Verificamos que si volvemos a correr greedy nos deveria dar un coloreo <= al anterior.

        u32 res2 = Greedy(grafo, ordenEG);
        if (res2 == error)
        {
            printf("Error(ElimGarak) en greedy al ejecutarlo por segunda vez.\n");
            free(ordenEG);
            exit(1);
        }
        if (res2 > res)
        {
            printf("Error(ElimGarak) de coloreo en greedy por segunda vez.\n");
            free(ordenEG);
            exit(1);
    }

    DestruirGrafo(grafo);
    free(ordenEG);
    return 0;
}
