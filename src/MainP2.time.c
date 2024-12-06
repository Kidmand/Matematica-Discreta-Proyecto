
// #include "./API2024Parte2.h"
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// void swap(u32 *a, u32 *b)
// {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

// void customSort(u32 *arr, u32 n)
// {
//     // Mueve todos los múltiplos de 3 al principio
//     u32 pivot = 0;
//     for (u32 i = 0; i < n; i++)
//     {
//         if (arr[i] % 3 == 0)
//         {
//             swap(&arr[i], &arr[pivot]);
//             pivot++;
//         }
//     }
// }

// void selectionSort(u32 *arr, u32 n, Grafo G)
// {
//     u32 i, j, max_grado, max_index;
//     clock_t start_time = clock(); // Guardar el tiempo de inicio

//     // Recorremos el arreglo
//     for (i = 0; i < n - 1; i++)
//     {
//         max_grado = Grado(i, G);
//         max_index = i;
//         // Buscamos el índice del máximo elemento
//         for (j = i + 1; j < n; j++)
//         {
//             if (Grado(j, G) > max_grado)
//             {
//                 max_grado = Grado(j, G);
//                 max_index = j;
//             }
//         }
//         // Intercambiamos el elemento máximo con el elemento en la posición actual
//         swap(&arr[max_index], &arr[i]);
//     }
//     clock_t end_time = clock();
//     double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("selectionSort tarda:\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
// }

// // Inicializa la semilla para los números aleatorios.
// void initRand()
// {
//     srand(time(NULL));
// }
// //  Retrona 0 o 1 con una probabilidad de 50%.
// u32 getRand()
// {
//     // Generar un número aleatorio entre 0 y 99
//     int random_num = rand() % 100;

//     // Determinar el resultado basado en el rango del número aleatorio
//     if (random_num < 50)
//     {
//         return 0;
//     }
//     else
//     {
//         return 1;
//     }
// }

// // Recibe un grafo y un orden de los vertices y corre Greedy, GulDukat y ElimGarak cant_iteraciones veces.
// // Imprime los resultados de Greedy con GulDukat y ElimGarak.
// // Retorna la cantidad de colores obtenida con el ultimo Greedy.
// // Y el coloreo del mimso esta en el array de orden.
// u32 CorrerGreedyConGluDukatYElimGarak(Grafo grafo, u32 cant_iteraciones, char *orden_name, u32 *orden, u32 ERROR_GREEDY, u32 *coloreo_orden)
// {
//     u32 res_greedy, res_GulDukat, res_ElimGarak;
//     printf("\n-----------------------------------------\n");
//     printf("Iteramos Greedy con GulDukat y ElimGarak para el orden %s:\n", orden_name);
//     for (u32 i = 0; i < cant_iteraciones; i++)
//     {
//         res_GulDukat = GulDukat(grafo, orden);
//         if (res_GulDukat != '0')
//         {
//             printf("Error en greedy con GulDukat en el orden %s:\n", orden_name);
//             exit(1);
//         }
//         res_greedy = Greedy(grafo, orden);
//         if (res_greedy == ERROR_GREEDY)
//         {
//             printf("Error en greedy con orden %s:\n", orden_name);
//             exit(1);
//         }

//         // printf("  - (i=%u) Cantidad de colores con el orden de GulDukat:  %u\n", i, res_greedy);
//         res_ElimGarak = ElimGarak(grafo, orden);
//         if (res_ElimGarak != '0')
//         {
//             printf("Error en greedy con ElimGarak en el orden %s:\n", orden_name);
//             exit(1);
//         }
//         res_greedy = Greedy(grafo, orden);
//         if (res_greedy == ERROR_GREEDY)
//         {
//             printf("Error en greedy con orden %s:\n", orden_name);
//             exit(1);
//         }
//         // printf("  - (i=%u) Cantidad de colores con el orden de ElimGarak: %u\n", i, res_greedy);
//     }
//     printf("-----------------------------------------\n");
//     ExtraerColores(grafo, coloreo_orden);
//     return res_greedy;
// }

// u32 CorrerConGluDukatYElimGarak_500_veces(Grafo grafo, u32 *orden, u32 ERROR_GREEDY)
// {
//     u32 res_greedy, res_GulDukat, res_ElimGarak;
//     printf("\n-----------------------------------------\n");
//     printf("Iteramos Greedy con GulDukat o Elimgarak 500 veces con el último orden\n");
//     for (u32 i = 0; i < 500; i++)
//     {
//         if (getRand())
//         {
//             res_GulDukat = GulDukat(grafo, orden);
//             if (res_GulDukat != '0')
//             {
//                 printf("Error en greedy con GulDukat con el útimo orden dado.\n");
//                 exit(1);
//             }
//         }
//         else
//         {
//             res_ElimGarak = ElimGarak(grafo, orden);
//             if (res_ElimGarak != '0')
//             {
//                 printf("Error en greedy con ElimGarak con el útimo orden dado.\n");
//                 exit(1);
//             }
//         }
//         res_greedy = Greedy(grafo, orden);
//         if (res_greedy == ERROR_GREEDY)
//         {
//             printf("Error en greedy con el último orden dado.\n");
//             exit(1);
//         }
//         // printf(" - (i=%u) Cantidad de colores: %u\n", i, res_greedy);
//     }

//     return res_greedy;
// }

// int main(int argc, char *argv[])
// {

//     // FIXME: IMPORTANTE, REVISAR BIEN EL COMPORTAMEINTO DE importar y exportar (DE LA PARTE 1)
//     // FIXME: Y ASEGURARSE DE QUE ESTE BIEN IMPLEMENTADO.
//     // FIXME: (NO SE SI ESTA BIEN IMPLEMENTADO PORQUE ESA FUNCIONES NO TE GARATIZAN NADA DEL ARRELGO DE LOS COLORES)
//     clock_t start_time = clock(); // Guardar el tiempo de inicio

//     Grafo grafo;

//     grafo = ConstruirGrafo();
//     if (grafo == NULL)
//     {
//         printf("No se pudo construir el grafo.\n");
//         exit(1);
//     }

//     // Calcular el tiempo transcurrido
//     clock_t end_time = clock();
//     double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("ConstruirGrafo\n Tiempo transcurrido: %.2f segundos\n", elapsed_time);

//     u32 n = NumeroDeVertices(grafo);
//     // 1) el orden natural 0,1,...,n-1 de los vertices,
//     u32 *orden_1 = calloc(n, sizeof(u32));
//     for (u32 i = 0; i < n; i++)
//     {
//         orden_1[i] = i;
//     }

//     // Calcular el tiempo transcurrido
//     clock_t time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("1) el orden natural 0,1,...,n-1 de los vertices\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     // 2) el orden n-1,...,2,1,0
//     u32 *orden_2 = calloc(n, sizeof(u32));
//     for (u32 i = 0; i < n; i++)
//     {
//         orden_2[i] = (n - 1) - i;
//     }

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("2) el orden n-1,...,2,1,0 de los vertices\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     // 3) el orden poniendo primero todos los pares en orden decreciente y luego todos los impares, en orden creciente.
//     u32 *orden_3 = calloc(n, sizeof(u32)); // FIXME: REVISAR.
//     for (u32 i = 0; i < n / 2; i++)
//     {
//         orden_3[i] = ((n / 2) - 1 - i) * 2;
//     }
//     for (u32 i = 0; i < n / 2; i++)
//     {
//         orden_3[i + n / 2] = i * 2 + 1;
//     }

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("3) primero todos los pares en orden decreciente y luego todos los impares, en orden creciente.\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     // 4) ordenar los vertices de acuerdo con su grado, comenzando por el mayor grado y terminando con el menor grado.
//     u32 *orden_4 = calloc(n, sizeof(u32));
//     for (u32 i = 0; i < n; i++)
//     {
//         orden_4[i] = i;
//     }
//     selectionSort(orden_4, n, grafo); // FIXME: ESTO TARDA MUUUCHO (cambiar por el countingSort).

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("4) ordenar los vertices de acuerdo con su grado, comenzando por el mayor grado y terminando con el menor grado.\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     // 5) algun orden extra, elegido por ustedes
//     u32 *orden_5 = calloc(n, sizeof(u32));
//     for (u32 i = 0; i < n; i++)
//     {
//         orden_5[i] = i;
//     }
//     customSort(orden_5, n);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("5) algun orden extra, elegido por ustedes\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     u32 *coloreo_orden1 = malloc(n * sizeof(u32));
//     u32 *coloreo_orden2 = malloc(n * sizeof(u32));
//     u32 *coloreo_orden3 = malloc(n * sizeof(u32));
//     u32 *coloreo_orden4 = malloc(n * sizeof(u32));
//     u32 *coloreo_orden5 = malloc(n * sizeof(u32));
//     if (coloreo_orden1 == NULL ||
//         coloreo_orden2 == NULL ||
//         coloreo_orden3 == NULL ||
//         coloreo_orden4 == NULL ||
//         coloreo_orden5 == NULL)
//     {
//         printf("Error en la reserva de memoria para los colores.\n");
//         exit(1);
//     }

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("malloc de coloreo_ordenn\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     u32 ERROR_GREEDY = MAX_u32;

//     u32 res_greedy_orden_1 = Greedy(grafo, orden_1);
//     if (res_greedy_orden_1 == ERROR_GREEDY)
//         printf("Error en greedy con orden 1\n");
//     ExtraerColores(grafo, coloreo_orden1);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("greedy_orden_1\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     u32 res_greedy_orden_2 = Greedy(grafo, orden_2);
//     if (res_greedy_orden_2 == ERROR_GREEDY)
//         printf("Error en greedy con orden 2\n");
//     ExtraerColores(grafo, coloreo_orden2);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("greedy_orden_2\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     u32 res_greedy_orden_3 = Greedy(grafo, orden_3);
//     if (res_greedy_orden_3 == ERROR_GREEDY)
//         printf("Error en greedy con orden 3\n");
//     ExtraerColores(grafo, coloreo_orden3);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("greedy_orden_3\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     u32 res_greedy_orden_4 = Greedy(grafo, orden_4);
//     if (res_greedy_orden_4 == ERROR_GREEDY)
//         printf("Error en greedy con orden 4\n");
//     ExtraerColores(grafo, coloreo_orden4);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("greedy_orden_4\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     u32 res_greedy_orden_5 = Greedy(grafo, orden_5);
//     if (res_greedy_orden_5 == ERROR_GREEDY)
//         printf("Error en greedy con orden 5\n");
//     ExtraerColores(grafo, coloreo_orden5);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("greedy_orden_5\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     if (res_greedy_orden_1 == ERROR_GREEDY ||
//         res_greedy_orden_2 == ERROR_GREEDY ||
//         res_greedy_orden_3 == ERROR_GREEDY ||
//         res_greedy_orden_4 == ERROR_GREEDY ||
//         res_greedy_orden_5 == ERROR_GREEDY)
//     {
//         exit(1);
//     }

//     printf("\n-----------------------------------------\n");
//     printf("Cantidad de colores con el primer Greedy: \n");
//     printf("  - Orden 1: %u\n", res_greedy_orden_1);
//     printf("  - Orden 2: %u\n", res_greedy_orden_2);
//     printf("  - Orden 3: %u\n", res_greedy_orden_3);
//     printf("  - Orden 4: %u\n", res_greedy_orden_4);
//     printf("  - Orden 5: %u\n", res_greedy_orden_5);
//     printf("-----------------------------------------\n");

//     u32 cant_iteraciones = 50;

//     ImportarColores(coloreo_orden1, grafo);
//     u32 min_colores_orden_1 = CorrerGreedyConGluDukatYElimGarak(grafo, cant_iteraciones, "1", orden_1, ERROR_GREEDY, coloreo_orden1);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("min_colores_orden_1\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     ImportarColores(coloreo_orden2, grafo);
//     u32 min_colores_orden_2 = CorrerGreedyConGluDukatYElimGarak(grafo, cant_iteraciones, "2", orden_2, ERROR_GREEDY, coloreo_orden2);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("min_colores_orden_2\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     ImportarColores(coloreo_orden3, grafo);
//     u32 min_colores_orden_3 = CorrerGreedyConGluDukatYElimGarak(grafo, cant_iteraciones, "3", orden_3, ERROR_GREEDY, coloreo_orden3);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("min_colores_orden_3\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     ImportarColores(coloreo_orden4, grafo);
//     u32 min_colores_orden_4 = CorrerGreedyConGluDukatYElimGarak(grafo, cant_iteraciones, "4", orden_4, ERROR_GREEDY, coloreo_orden4);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("min_colores_orden_4\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     ImportarColores(coloreo_orden5, grafo);
//     u32 min_colores_orden_5 = CorrerGreedyConGluDukatYElimGarak(grafo, cant_iteraciones, "5", orden_5, ERROR_GREEDY, coloreo_orden5);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("min_colores_orden_5\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     u32 min_coloreo = MAX_u32;
//     u32 *orden_min_coloreo = NULL;
//     u32 *coloreo_min_coloreo = NULL;
//     if (min_colores_orden_1 <= min_coloreo)
//     {
//         min_coloreo = min_colores_orden_1;
//         orden_min_coloreo = orden_1;
//         coloreo_min_coloreo = coloreo_orden1;
//     }
//     if (min_colores_orden_2 < min_coloreo)
//     {
//         min_coloreo = min_colores_orden_2;
//         orden_min_coloreo = orden_2;
//         coloreo_min_coloreo = coloreo_orden2;
//     }
//     if (min_colores_orden_3 < min_coloreo)
//     {
//         min_coloreo = min_colores_orden_3;
//         orden_min_coloreo = orden_3;
//         coloreo_min_coloreo = coloreo_orden3;
//     }
//     if (min_colores_orden_4 < min_coloreo)
//     {
//         min_coloreo = min_colores_orden_4;
//         orden_min_coloreo = orden_4;
//         coloreo_min_coloreo = coloreo_orden4;
//     }
//     if (min_colores_orden_5 < min_coloreo)
//     {
//         min_coloreo = min_colores_orden_5;
//         orden_min_coloreo = orden_5;
//         coloreo_min_coloreo = coloreo_orden5;
//     }

//     printf("\n-----------------------------------------\n");
//     printf("Vamos a iterar 500 veces Greedy con GulDukat y ElimGarak con el orden que dio la menor cantidad de colores:\n");
//     ImportarColores(coloreo_min_coloreo, grafo);
//     u32 min_colores_orden_final = CorrerConGluDukatYElimGarak_500_veces(grafo, orden_min_coloreo, ERROR_GREEDY);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("min_colores_orden_final\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     printf("\n-----------------------------------------\n");

//     printf("Cantidad de colores con el orden que dio la menor cantidad de colores: %u\n", min_colores_orden_final);
//     // Desalojamos memoria:
//     DestruirGrafo(grafo);
//     free(orden_1);
//     free(orden_2);
//     free(orden_3);
//     free(orden_4);
//     free(orden_5);

//     free(coloreo_orden1);
//     free(coloreo_orden2);
//     free(coloreo_orden3);
//     free(coloreo_orden4);
//     free(coloreo_orden5);

//     // Calcular el tiempo transcurrido
//     time_anterior = elapsed_time;
//     end_time = clock();
//     elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("Final\n");
//     printf("Tiempo transcurrido: %.2f segundos\n", elapsed_time);
//     printf("Tiempo transcurrido desde la anterior medicion: %.2f segundos\n", elapsed_time - time_anterior);

//     return 0;
// }

// /*
// DOC: Compilacion y ejecucion:
// - Compilar: make mainParte2
// - Ejecutar: ./MainParte2.out < tests/PARTE2/inputs/ejemplo_basico.txt
//             ./MainParte2.out < tests/PARTE2/inputs/PGJ10_500.txt
//             ./MainParte2.out < tests/ejemplos_inputs_extremos/harkon.txt
// */