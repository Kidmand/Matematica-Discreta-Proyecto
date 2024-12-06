#include "../../../API2024Parte2.h"
#include <stdint.h>
#include <assert.h>

/*
TODO: Hacer macro para ir tomando tiempos de ejecución... en ciertas partes del código.
PD: Utilizar variables globales para guardar los tiempos de ejecución.

- Ejemplo:

    clock_t start_time = clock(); // Guardar el tiempo de inicio

    // Codigo a medir 1

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);

    // Codigo a medir 2

    clock_t time_anterior = elapsed_time;
    end_time = clock();
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("1) el orden natural 0,1,...,n-1 de los vertices\n");
    printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
    printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);
*/
/*
Ideas para el punto 5)
- Algoritmo 1:
    1. Agregar vertice V de mayor grado sin agregar.
    2. Agregar sus vecinos sin agregar en orden de su por grado.
    3. Repetir 1 y 2 hasta que no queden vertices sin colorear.

- Algoritmo 2:
    1. Buscar i-vertice V de mayor grado.
    2. Agregar sus vecinos sin agregar en orden de su por grado.
    3. Agregar V si no ha sido agregado.
    4. Repetir 1, 2 y 3 hasta que no queden vertices sin colorear.
- Algoritmo 3:
Igual que las funciones VIT, con alguna o ambas modificaciones:
1. Cambiando que los vertices de los bloques se ordenan por grado.
2. Cambiando que los bloques de los colores X se ordenen por el promedio de los
grados de sus vertices en vez de por el mayor grado de sus vertices.
*/

/**
 * @brief Macro que libera la memoria de a lo sumo 3 punteros array1, array2 y array3 si se cumple la condición y retorna el valor ret.
 *
 * @param cond Es la condición que se va a evaluar.
 * @param array1 Es el primer puntero a liberar.
 * @param array2 Es el segundo puntero a liberar.
 * @param array3 Es el tercer puntero a liberar.
 * @param ret Es el valor que se va a retornar si se cumple la condición.
 * @param msj Es el mensaje que se va a imprimir si se cumple la condición.
 *
 * @note Los punteros array1, array2 y array3 pueden ser NULL.
 */
#define FREE_AND_RETURN_IF(cond, array1, array2, array3, ret, msj) \
    do                                                             \
    {                                                              \
        if (cond)                                                  \
        {                                                          \
            printf("%s\n", (msj));                                 \
            if (array1 != NULL)                                    \
            {                                                      \
                free(array1);                                      \
            }                                                      \
            if (array2 != NULL)                                    \
            {                                                      \
                free(array2);                                      \
            }                                                      \
            if (array3 != NULL)                                    \
            {                                                      \
                free(array3);                                      \
            }                                                      \
            return (ret);                                          \
        }                                                          \
    } while (0)

/**
 * @brief Verifica si el arreglo de vértices está ordenado de manera descendente por grado.
 * 
 * @param arr 
 * @param n 
 * @param G 
 * @return u32 1 si está ordenado, 0 en caso contrario.
 */
u32 checkOrden(u32 *arr, u32 n, Grafo G)
{
    for (u32 i = 1; i < n; i++)
    {
        u32 grado1 = Grado(arr[i - 1], G);
        u32 grado2 = Grado(arr[i], G);
        if (grado1 < grado2)
        {
            printf("Error en el ordenamiento.\n");
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Ordena los vértices de un grafo en `orden descendente` de sus grados utilizando el algoritmo de ordenamiento por selección.
 *
 * @param ordenXgrado Es un array que contiene los vértices a ordenar.
 * @param n Es el número de vértices en el grafo.
 * @param G Es el grafo cuyos vértices se van a ordenar.
 *
 * @note `Complejidad`: O(n^2).
 */
void selectionSort(u32 *ordenXgrado, u32 n, Grafo G)
{
    for (u32 j = 0; j < n; j++)
    {
        u32 max = j;
        for (u32 k = j + 1; k < n; k++)
        {
            if (Grado(ordenXgrado[k], G) > Grado(ordenXgrado[max], G))
                max = k;
        }
        u32 temp = ordenXgrado[max];
        ordenXgrado[max] = ordenXgrado[j];
        ordenXgrado[j] = temp;
    }

    assert(checkOrden(ordenXgrado, n, G));
}

/**
 * @brief Ordena los vértices de un grafo en `orden descendente` de sus grados utilizando el algoritmo de ordenamiento por conteo.
 *
 * @param ordenXgrado Es un array que contiene los vértices a ordenar.
 * @param n Es el número de vértices en el grafo.
 * @param G Es el grafo cuyos vértices se van a ordenar.
 *
 * @return 0 si se ordenaron los vértices correctamente, 1 en caso contrario.
 *
 * @note `Complejidad`: O(n).
 */
u32 countingSort(u32 *ordenXgrado, u32 n, Grafo G)
{
    // Calculo del maximo y minimo valor posible en el arreglo y el rango de valores.
    u32 max = 0;
    u32 min = MAX_u32;
    for (u32 i = 0; i < n; i++)
    {
        u32 grado = Grado(ordenXgrado[i], G);
        if (grado > max)
            max = grado;
        if (grado < min)
            min = grado;
    }
    u32 range = max - min + 1;

    // Inicialización del arreglo de frecuencias y del arreglo de salida.
    u32 *count = calloc(range, sizeof(u32));
    u32 *output = malloc(n * sizeof(u32));
    if (count == NULL || output == NULL)
    {
        printf("Error en la reserva de memoria para count o/y output.\n");
        free(count);
        free(output);
        return 1;
    }

    // Conteo de la frecuencia de cada grado.
    // Se resta el minimo grado para que el arreglo de frecuencias comience en 0.
    // Servira para determinar cuantos elementos de cierto grado iran en la i-esima
    // posición de cada conjunto de elementos equivalentes (en orden) en la lista ordenada.
    for (u32 i = 0; i < n; i++)
        count[Grado(ordenXgrado[i], G) - min]++;

    // Suma acumulativa de las frecuencias.
    // Servira para determinar las posiciones finales de los elementos en la lista ordenada.
    for (u32 i = 1; i < range; i++)
        count[i] += count[i - 1];

    // Ordenamiento de los vértices por grado.
    // Para cada elemento se utiliza su posicion en el arreglo de frecuencias
    // acumlativas para determinar su posición en la lista ordenada.
    // Obs: Al guardar un elemento con cierto grado, se decrementa la posición
    // del siguiente elemento con ese grado en el arreglo de frecuencias acumulativas.
    for (u32 i = n; i > 0; i--)
    {
        output[count[Grado(ordenXgrado[i-1], G) - min] - 1] = ordenXgrado[i-1];
        count[Grado(ordenXgrado[i-1], G) - min]--;
    }

    // Copia del arreglo ordenado al arreglo original.
    for (u32 i = 0; i < n; i++)
        ordenXgrado[n - i - 1] = output[i];

    assert(checkOrden(ordenXgrado, n, G));

    free(count);
    free(output);
    return 0;
}


/**
 * @brief - Algoritmo 2:
 * @brief 1. Buscar i-vertice V de mayor grado.
 * @brief 2. Agregar sus vecinos sin agregar en orden de su por grado.
 * @brief 3. Agregar V si no ha sido agregado.
 * @brief 4. Repetir 1, 2 y 3 hasta que no queden vertices sin colorear.
 *
 * @param arr Array a ordenar
 * @param n tamano del array
 * @param G grafo
 *
 * @note Complejidad: O(complegidadOrdenamiento(m))
 */
u32 algOrd5(u32 *arr, u32 n, Grafo G)
{
    assert(arr != NULL && G != NULL);
    // 1. Crear un arreglo de tamano n donde cada indice representa un vertice,
    //    estara en 1 si ha sido agregado a Orden, en 0 si no.
    u32 *presentes = calloc(n, sizeof(u32));
    FREE_AND_RETURN_IF(presentes == NULL, NULL, NULL, NULL, 1, "Error en la reserva de memoria para presentes.");

    // 2. Crear un arreglo para los vertices ordenados por su grado de mayor a menor.
    u32 *ordenXgrado = malloc(n * sizeof(u32));
    FREE_AND_RETURN_IF(ordenXgrado == NULL, presentes, NULL, NULL, 1, "Error en la reserva de memoria para ordenXgrado.");

    // 3. Llenar el arreglo ordenXgrado con los vertices ordenados por su grado de mayor a menor.
    for (u32 i = 0; i < n; i++)
        ordenXgrado[i] = i;

    u32 res = countingSort(ordenXgrado, n, G);
    if (res == 1)
    {
        printf("Error en countingSort.\n");
        free(presentes);
        free(ordenXgrado);
        return 1;
    }

    // 4. Crear un contador count.
    //    (Indicara fin de programa cuando count == n)
    u32 count = 0;

    for (u32 i = 0; i < n && count < n; i++)
    {
        // 5. Buscar el vertice V de mayor grado en el arreglo.
        u32 V = ordenXgrado[i];

        // 6. Ordenar en un arreglo los vecinos de V por su grado de mayor a menor.
        u32 *vecinosXgrado = malloc(n * sizeof(u32));
        FREE_AND_RETURN_IF(vecinosXgrado == NULL, presentes, ordenXgrado, NULL, 1, "Error en la reserva de memoria para vecinosXgrado.");

        // Creamos el arreglo de vecinos de V sin ordenar
        u32 gradoV = Grado(V, G);
        for (u32 j = 0; j < gradoV; j++)
        {
            u32 vecino = Vecino(j, V, G);
            vecinosXgrado[j] = vecino;
        }

        // Ordenamos los vecinos de V por su grado de mayor a menor
        res = countingSort(vecinosXgrado, gradoV, G);
        if (res == 1)
        {
            printf("Error en countingSort.\n");
            free(presentes);
            free(ordenXgrado);
            free(vecinosXgrado);
            return 1;
        }

        // 7. Agregar los vecinos sin agregar de V en orden por su grado,
        //    al agregar marcarlos como agregados y hacer count ++.
        for (u32 i = 0; i < gradoV; i++)
        {
            u32 vecino = vecinosXgrado[i];
            if (!presentes[vecino])
            {
                presentes[vecino] = 1;
                arr[count] = vecino;
                count++;
            }
        }

        // 8. Si no ha sido agregado a Orden, agregar el vertice V a Orden,
        //    marcarlo como agregado en su posicion en el array y count++.
        if (!presentes[V])
        {
            presentes[V] = 1;
            arr[count] = V;
            count++;
        }

        free(vecinosXgrado);
    }
    free(presentes);
    free(ordenXgrado);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("El numero de argumentos esta mal!\n");
        printf("No deben pasarse argumentos\n");
        exit(1);
    }

    Grafo G = ConstruirGrafo();
    if (G == NULL)
    {
        printf("No se pudo construir el grafo.\n");
        exit(1);
    }

    u32 numeroDeVertices = NumeroDeVertices(G);

    u32 *orden5 = malloc(numeroDeVertices * sizeof(u32));
    if (orden5 == NULL)
    {
        printf("Error en la reserva de memoria para orden5.\n");
        DestruirGrafo(G);
        exit(1);
    }

    u32 res = algOrd5(orden5, numeroDeVertices, G);
    if (res == 1)
    {
        printf("Error en algOrd5.\n");
        free(orden5);
        DestruirGrafo(G);
        exit(1);
    }

    // Coloreamos con Greedy
    res = Greedy(G, orden5);
    u32 error = MAX_u32;
    if (res == error)
    {
        printf("Error en greedy.\n");
        free(orden5);
        DestruirGrafo(G);
        exit(1);
    }

    printf("Cantidad de colores luego de greedy con alg5: %u\n", res);

    printf("Corriendo 500 veces greedy con GulDukat y ElimGarak intercalados:\n");
    printf("Cambio del numero de colores: \n ");
    for (u32 i = 0; i < 500; i++)
    {
        if (i % 2 == 0)
        {
            char cres = ElimGarak(G, orden5);
            char cerror = '1';
            if (cres == cerror)
            {
                printf("Error en ElimGarak.\n");
                free(orden5);
                DestruirGrafo(G);
                exit(1);
            }
        }
        else
        {
            // TODO: Cambiar GulDukat por una funcion que ordene todos los bloques de
            //       colores de mayor a menor segun el valor promedio de los grados de
            //       sus vertices.
            char cres = GulDukat(G, orden5);
            char cerror = '1';
            if (cres == cerror)
            {
                printf("Error en GulDukat.\n");
                free(orden5);
                DestruirGrafo(G);
                exit(1);
            }
        }

        res = Greedy(G, orden5);
        if (res == error)
        {
            printf("Error en greedy.\n");
            free(orden5);
            DestruirGrafo(G);
            exit(1);
        }

        if (i % 2 == 0)
        {
            printf("-%u  ", res);
        }
        else
        {
            printf("+%u  ", res);
        }
    }
    printf("\n\n");

    DestruirGrafo(G);
    free(orden5);
    return 0;
}

// Coloreo alg5 harkon actual: 534
// Coloreo final harkon actual: 222
// Tiempo aprox: 4 minutos
