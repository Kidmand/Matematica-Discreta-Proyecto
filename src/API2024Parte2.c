#include "API2024Parte2.h"
#include <assert.h>
// FIXME: DESCOMENTAR ESTO ANTES DE ENTREGAR. (anula todos los asserts)
#define NDEBUG                 // Flag para deshabilitar los asserts.
#define assert(expr) ((void)0) // Que los asserts no hagan nada.
#define ERROR '1'
#define OK '0'
#define MAYOR_A_MENOR 1
#define MENOR_A_MAYOR 0

/*
NOTE: Hacer primero los TODO: y FIXME: del codigo,
luego los de IMPLEMENTACION, TESTEAR, MAIN y FIN.

TODO: IMPLEMENTACION:
Implementar los siguientes ordenes:
[x] el orden natural 0,1,...,n-1 de los vertices,
[x] el orden n-1,...,2,1,0
[x] el orden poniendo primero todos los pares en orden decreciente y luego todos los impares,
en orden creciente.
[x] ordenar los vertices de acuerdo con su grado, comenzando por el mayor grado y
terminando con el menor grado.
[x] algun orden extra, elegido por ustedes. (ideas en el .h)

TODO: TESTEAR:
[ ] Greedy:
    { } Testear los casos en los que debe devolver error.
    { } Pasar grafos completos grandes y chequear que el numero cromatico sea el esperado.
    { } OPTIONAL: Para testear que greedy sea O(m) hay que pasarle dos grafos distintos
        con la misma cantidad de aristas y que no cambie mucho el tiempo y menos
        aun el numero de instrucciones.

[X] Funcion de ordenamiento:

[ ] GulDukat:
    { } Testear los casos en los que debe devolver error.
[ ] ElimGarak:
    {x} Que el numero cromatico sea a o sumo el mismo luego de correr greedy
        con el orden de GulDukat. (VIT dice eso)
        (Puede ser un error del greedy tm si da mal)
    {x} Velocidad razonable. Menor a 5 minutos.
    {x} Usar valgrind con todas las flags activas. Que no haya errores.
    { } Testear los casos en los que debe devolver error.
    {x} Que los bloques de colores resultantes solo aparezcan una vez y en orden.

TODO: MAIN: leer en la consigna. La parte 4.

TODO: FIN:
[ ] Ultima revision
    { } Usar valgrind con todas las flags activas en todos los tests. Que no haya errores.
    { } Que ningun test de error.
    { } Velocidad total razonable. Menor a 5 minutos.
    {x} Que las funciones auxiliares sean static.
*/
// *~~~~~~~~~~~~~~~~ Estructura de datos auxiliar ~~~~~~~~~~~~~~~~* //
typedef struct Bloque
{
    color color;   // color que representa
    u32 min_grado; // m(x) = min{Grado(i, G) : Color(i, G) = x}
    u32 max_grado; // M (x) = max{Grado(i, G) : Color(i, G) = x}
    u32 cant_vertices;
    u32 *vertices; // vertices de ese color
} Bloque;

// *~~~~~~~~~~~~~~~~ Codigo auxiliar para asserts ~~~~~~~~~~~~~~~~* //

/**
 * @brief Verifica si un grafo tiene un coloreo propio.
 *
 * @param G Es el grafo que se va a verificar.
 *
 * Un coloreo propio es aquel en el que dos vértices adyacentes no tienen el mismo color.
 *
 * La función recorre todos los vértices del grafo. Para cada vértice, obtiene su color y luego recorre todos sus vértices adyacentes.
 * Si encuentra un vértice adyacente con el mismo color, la función retorna 0, indicando que el grafo no tiene un coloreo propio.
 * Si después de recorrer todos los vértices y sus adyacentes no encuentra dos con el mismo color, la función retorna 1, indicando que el grafo tiene un coloreo propio.
 *
 * @return u32 Retorna 0 si el grafo no tiene un coloreo propio, y 1 si lo tiene.
 */
static u32 coloreoPropio(Grafo G)
{
    u32 n = NumeroDeVertices(G);
    for (u32 v = 0; v < n; v++)
    {
        color color_v = Color(v, G);
        for (u32 j = 0; j < Grado(v, G); j++)
        {
            u32 vecino = Vecino(j, v, G);
            color color_vecino = Color(vecino, G);
            if (color_v == color_vecino)
                return 0;
        }
    }
    return 1;
}

// *~~~~~~~~~~~~~~~~ Codigo auxiliar compartido ~~~~~~~~~~~~~~~~* //

/**
 * @brief Ordena un arreglo de estructuras Bloque utilizando el algoritmo Counting Sort(Ordenamiento por Cuentas).
 *
 * @param array El arreglo de estructuras Bloque a ordenar.
 * @param size El tamaño del arreglo array.
 * @param valor Una función que toma un puntero a una estructura Bloque y devuelve el valor
 *              utilizado para ordenar los elementos en array.
 * @param mayorAmenor MAYOR_A_MENOR para ordenar de mayor a menor, si no, de menor a mayor.
 *
 * @return Devuelve el char '0' si todo anduvo bien, '1' si hubo algún problema.
 *
 * @note - `Eficiencia`:
 * @note  Sea D la diferencia entre el maximo y minimo valor(array[i]) donde i = 0, 1, ..., size - 1.
 * @note  Muestra mayor eficiencia cuanto menor es D con respecto a size.
 * @note - `Complegidad`: O(n + k), donde n es la cantidad de elementos y k es el rango de valores.
 */
static char countingSort(Bloque *array, u32 size, u32 (*valor)(Bloque *), u32 mayorAmenor)
{
    // Calculamos el maximo y minimo valor posible en el arreglo.
    u32 min = valor(&array[0]);
    u32 max = valor(&array[0]);
    for (u32 i = 1; i < size; i++)
    {
        u32 val = valor(&array[i]);
        if (val < min)
            min = val;
        if (val > max)
            max = val;
    }

    u32 rango = max - min + 1;
    // Inicialización del arreglo de frecuencias
    u32 *frecuencia = (u32 *)calloc(rango, sizeof(u32));
    if (frecuencia == NULL)
    {
        free(frecuencia);
        return ERROR;
    }

    // Recorremos la lista original y se contamos el número de ocurrencias de cada elemento,
    // almacenando esta información en el arreglo de frecuencias.
    for (u32 i = 0; i < size; i++)
    {
        Bloque *bloque = &array[i];
        u32 pos = valor(bloque) - min;
        assert(pos < rango);
        frecuencia[pos]++; // Incrementamos la frecuencia en la posicion del valor
    }

    // Calculamos las sumas acumulativas en el arreglo de frecuencias para determinar
    // las posiciones finales de los elementos en la lista ordenada.
    for (u32 i = 1; i < rango; i++)
        frecuencia[i] += frecuencia[i - 1];

    // Creamos un arreglo auxiliar para almacenar la lista ordenada.
    Bloque *aux = (Bloque *)malloc(size * sizeof(Bloque));
    if (aux == NULL)
    {
        free(frecuencia);
        free(aux);
        return ERROR;
    }

    // Recorremos la lista original nuevamente, y para cada elemento utilizamos su posicion en
    // el arreglo de frecuencias acumlativas para determinar su posición en la lista ordenada.
    for (u32 i = size; i > 0; i--)
    {
        Bloque *bloque = &array[i - 1];
        u32 pos = valor(bloque) - min;
        assert(pos < rango);
        aux[frecuencia[pos] - 1] = *bloque;
        frecuencia[pos]--;
    }

    // Ordenamos el arreglo original con el arreglo auxiliar.
    for (u32 i = 0; i < size; i++)
    {
        if (mayorAmenor == MAYOR_A_MENOR)
        {
            array[size - i - 1] = aux[i];
        }
        else
        {
            array[i] = aux[i];
        }
    }

    free(aux);
    free(frecuencia);
    return OK;
}

/**
 * Macro que inicializa un bloque de elementos en un array de tipo Bloque.
 *
 * @param array_GD_EG El array de estructuras a inicializar.
 * @param inicio El índice de inicio del bloque.
 * @param fin El índice de fin del bloque.
 * @param expresion La expresión que determina el color de los elementos.
 *
 * @note `r, n y sum_parcial` son variables que quedan definidas en el contexto/alcance de donde se llama la macro.
 * @note Luego la `expresion` se evalua en el contexto de la macro y debe usar los  i,j.
 */
#define INIT_BLOCK(array_GD_EG, inicio, fin, expresion)          \
    for (u32 i = inicio, j = 0; i < fin; i++, j++)               \
    {                                                            \
        u32 f_color = (expresion);                               \
        assert(f_color <= r);                                    \
        array_GD_EG[i].color = f_color;                          \
        array_GD_EG[i].min_grado = n;                            \
        array_GD_EG[i].max_grado = 0;                            \
        array_GD_EG[i].cant_vertices = 0;                        \
        array_GD_EG[i].vertices = &verticesXbloque[sum_parcial]; \
        sum_parcial += cant_verticesXcolor[f_color - 1];         \
        assert(cant_verticesXcolor[f_color - 1] != 0);           \
    }

static void Free_All(Bloque *arrayEGDG, u32 *cant_verticesXcolor, u32 *verticesXbloque)
{
    free(arrayEGDG);
    free(cant_verticesXcolor);
    free(verticesXbloque);
}

static u32 Calcular_r(u32 *cant_verticesXcolor, u32 r, u32 n, Grafo G)
{
    assert(cant_verticesXcolor != NULL);
    for (u32 i = 0; i < n; i++)
    {
        u32 color = Color(i, G);
        cant_verticesXcolor[color - 1]++;
        if (color > r)
            r = color;
    }
    return r;
}

static void Concatenar_r_arreglos(Bloque *arrayN, u32 *Orden, u32 r, u32 n)
{
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
}

// *~~~~~~~~~~~~~~~~ Codigo auxiliar GulDukat ~~~~~~~~~~~~~~~~* //

/**
 * @brief Esta función inserta el vértice en el i-bloque de arrayGD y actualiza su informacion.
 *
 * @param arrayGD Es un puntero al array de bloques.
 * @param indice Es el índice del bloque en el que se insertará el vértice.
 * @param vertice Es el vértice que se va a insertar en el bloque.
 * @param grado Es el grado del vértice que se va a insertar.
 *
 * @note La función primero obtiene el bloque en el que se insertará el vértice utilizando el índice proporcionado.
 * @note Después, inserta el vértice en la posición actual y aumenta la cantidad de vértices en el bloque.
 * @note Finalmente, actualiza los grados mínimos y máximos del bloque si el grado del vértice insertado es menor o mayor que los actuales, respectivamente.
 */
static void putBloqueGD(Bloque *arrayGD, u32 indice, u32 vertice, u32 grado)
{
    Bloque *bloque = &arrayGD[indice];
    assert(bloque->vertices[bloque->cant_vertices] == 0);
    bloque->vertices[bloque->cant_vertices] = vertice;
    bloque->cant_vertices++;

    // Calculamos los grados max&min:
    if (bloque->max_grado < grado)
        bloque->max_grado = grado;

    if (bloque->min_grado > grado)
        bloque->min_grado = grado;
}

// Funciones auxiliares para el ordenamiento de GulDukat.
static u32 ret_M(Bloque *b)
{
    return b->max_grado;
}
static u32 ret_M_mas_m(Bloque *b)
{
    return (b->max_grado + b->min_grado);
}
static u32 ret_m(Bloque *b)
{
    return b->min_grado;
}

// NOTE: No sabemos si el grafo esta coloreado con greedy por lo que no podemos asumir
//       un coloreo de a lo sumo delta + 1 colores
char GulDukat(Grafo G, u32 *Orden)
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
    u32 r = 1; // Cantidad de colores
    u32 *cant_verticesXcolor = (u32 *)calloc(n, sizeof(u32));
    if (cant_verticesXcolor == NULL)
    {
        free(cant_verticesXcolor);
        return ERROR;
    }

    r = Calcular_r(cant_verticesXcolor, r, n, G);

    assert(2 <= r && r <= n);
    assert(r / 4 + r / 2 - r / 4 + (r + 1) / 2 == r);

    // En arrayGD se iran agregando los bloques de colores de la siguiente forma:
    //
    // Indices:  0                     r/4                             r/2            r
    // arrayGD = [ Los divisibles por 4 | Los pares no divisibles por 4 | Los impares ]
    Bloque *arrayGD = (Bloque *)calloc(r, sizeof(Bloque));

    // En verticesXbloque se iran guardando los vertices de cada bloque.
    u32 *verticesXbloque = (u32 *)calloc(n, sizeof(u32));

    if (arrayGD == NULL || verticesXbloque == NULL)
    {
        Free_All(arrayGD, cant_verticesXcolor, verticesXbloque);
        return ERROR;
    }

    // Inicializamos los bloques de colores (Bloque) de arrayGD
    u32 inicio_d4 = 0, inicio_d2_no_d4 = r / 4, inicio_impares = r / 2;
    u32 sum_parcial = 0;
    INIT_BLOCK(arrayGD, inicio_d4, inicio_d2_no_d4, (j + 1) * 4)
    INIT_BLOCK(arrayGD, inicio_d2_no_d4, inicio_impares, 2 * (j * 2 + 1))
    INIT_BLOCK(arrayGD, inicio_impares, r, (j * 2) + 1)
    assert(sum_parcial == n);

    // En verticesXbloque guardamos los vertices en su seccion correspondiente dependiendo de
    // si su color es divisible por 4, par no divisible por 4 o impar.
    // Ademas calculamos el max&min grado de cadaBloque..
    for (u32 v = 0; v < n; v++)
    {
        u32 color = Color(v, G);
        u32 grado = Grado(v, G);

        if (color % 4 == 0)
        {
            // Accediendo al bloque del color correspondiente.
            u32 indice = inicio_d4 + (color / 4) - 1;
            assert(indice < inicio_d2_no_d4);
            // Actualizamos el bloque correspondiente recalculando todo
            putBloqueGD(arrayGD, indice, v, grado);
        }
        else if (color % 2 == 0)
        {
            // Accediendo al bloque del color correspondiente.
            u32 indice = inicio_d2_no_d4 + ((color / 2) - (color / 4)) - 1;
            assert(indice < inicio_impares);
            // Actualizamos el bloque correspondiente recalculando todo
            putBloqueGD(arrayGD, indice, v, grado);
        }
        else
        {
            // Accediendo al bloque del color correspondiente.
            u32 indice = inicio_impares + (((color + 1) / 2)) - 1;
            assert(indice < r);
            // Actualizamos el bloque correspondiente recalculando todo
            putBloqueGD(arrayGD, indice, v, grado);
        }
    }

    // Funcion de ordenamiento que ordena en en el subarreglo de colores
    // divisibles por 4 en ArrayGD segun M(x) de mayor a menor. O(r)
    char res = countingSort(&arrayGD[0], r / 4, ret_M, MAYOR_A_MENOR);
    if (res == ERROR)
    {
        Free_All(arrayGD, cant_verticesXcolor, verticesXbloque);
        return ERROR;
    }

    // Funcion de ordenamiento que ordena en en el subarreglo de colores
    // pares no divisibles por 4 en ArrayGD segun M(x) + m(x) de mayor a menor. O(r)
    res = countingSort(&arrayGD[r / 4], r / 2 - r / 4, ret_M_mas_m, MAYOR_A_MENOR);
    if (res == ERROR)
    {
        Free_All(arrayGD, cant_verticesXcolor, verticesXbloque);
        return ERROR;
    }

    // Funcion de ordenamiento que ordena en en el subarreglo de colores
    // impares en ArrayGD segun m(x) de mayor a menor. O(r)
    res = countingSort(&arrayGD[r / 2], (r + 1) / 2, ret_m, MAYOR_A_MENOR);
    if (res == ERROR)
    {
        Free_All(arrayGD, cant_verticesXcolor, verticesXbloque);
        return ERROR;
    }

    // "Concatenamos" los r arreglos anidados de ArrayGD en Orden. O(n)
    Concatenar_r_arreglos(arrayGD, Orden, r, n);

    // Liberamos toda la memoria usada.
    Free_All(arrayGD, cant_verticesXcolor, verticesXbloque);

    return OK;
}

// *~~~~~~~~~~~~~~~~ Codigo auxiliar ElimGarak ~~~~~~~~~~~~~~~~* //

// Funciones auxiliares para el array de ElimGarak.
static void putBloqueEG_N(Bloque *arrayEG_N, u32 indice, u32 vertice, u32 grado)
{
    Bloque *bloque = &arrayEG_N[indice];
    assert(bloque->vertices[bloque->cant_vertices] == 0);
    bloque->vertices[bloque->cant_vertices] = vertice;
    bloque->cant_vertices++;
}

// Funciones auxiliares para el ordenamiento de ElimGarak.
static u32 ret_cant_ver(Bloque *b)
{
    return b->cant_vertices;
}

// NOTE: Se usara la misma estructura de datos que la funcion de arriba para los bloques,
//       pero no use deberian usar max_grado ni min_grado.
char ElimGarak(Grafo G, u32 *Orden)
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
    if (cant_verticesXcolor == NULL)
    {
        free(cant_verticesXcolor);
        return ERROR;
    }
    r = Calcular_r(cant_verticesXcolor, r, n, G);

    assert(r >= 2 && r <= n);

    // En arrayEG se iran agregando los colores de la siguiente forma:
    // x1 es el color que tiene la menor cantidad de vertices de ese color, excluyendo a los colores 1 y 2.
    // x2 es el color que tiene la menor cantidad de vertices de ese color, excluyendo a los colores 1,2 y x1
    // Indices:  0 -----------------------------r,------r2,----r1
    // arrayEG = [x1=r3, x2=r4, ........ , xr-2=r, xr-1=r2, xr=r1]
    Bloque *arrayEG = (Bloque *)calloc(r, sizeof(Bloque));

    // En verticesXbloque se iran guardando los vertices de cada cada color [r3,-----,r,r2,r1]
    u32 *verticesXbloque = (u32 *)calloc(n, sizeof(u32));

    // Controlamos que no haya problemas de memoria.
    if (arrayEG == NULL || verticesXbloque == NULL)
    {
        Free_All(arrayEG, cant_verticesXcolor, verticesXbloque);
        return ERROR;
    }

    // Inicializamos los dos bloques de colores [r3,r4,----,r,r2,r1]
    u32 inicio_d_r_3 = 0, inicio_r1_r2 = r - 2;
    u32 sum_parcial = 0;
    INIT_BLOCK(arrayEG, inicio_d_r_3, inicio_r1_r2, j + 3)
    INIT_BLOCK(arrayEG, inicio_r1_r2, r, 3 - (j + 1)) // ---- se almacena primero r2 y despues r1 si j=0, j+1=1 y 3-(j+1) = 2 que es r2
    assert(sum_parcial == n);

    // En verticesXbloque guardamos los vertices en su seccion correspondiente dependiendo de
    // si su color es [r3,-----,r] o corresponde a r1,r2
    // Ademas calculamos el max&min grado de cadaBloque..
    for (u32 v = 0; v < n; v++)
    {
        u32 color = Color(v, G);
        u32 grado = Grado(v, G);

        if (color >= 3)
        {
            // Accediendo al bloque del color correspondiente. [r3,-----,r]
            u32 indice = color - 3;
            assert(indice < inicio_r1_r2);
            // Actualizamos el bloque correspondiente recalculando todo
            putBloqueEG_N(arrayEG, indice, v, grado);
        }
        else
        {
            // Accediendo al bloque del color correspondiente. [r2,r1]
            u32 indice = r - color;
            assert(indice >= inicio_r1_r2);
            // Actualizamos el bloque correspondiente recalculando todo
            putBloqueEG_N(arrayEG, indice, v, grado);
        }
    }
    // Funcion de ordenamiento que ordene en el arreglo que va desde color [r3,-----,r]
    // ArrayEG segun cant_vertices de menor a mayor O(r)
    char res = countingSort(&arrayEG[0], inicio_r1_r2, ret_cant_ver, MENOR_A_MAYOR);
    if (res == ERROR)
    {
        Free_All(arrayEG, cant_verticesXcolor, verticesXbloque);
        return ERROR;
    }

    // "Concatenamos" los r arreglos anidados de ArrayEG en Orden. O(n)
    Concatenar_r_arreglos(arrayEG, Orden, r, n);

    // Liberamos toda la memoria usada.
    Free_All(arrayEG, cant_verticesXcolor, verticesXbloque);

    return OK;
}

// *~~~~~~~~~~~~~~~~ Codigo auxiliar Greedy ~~~~~~~~~~~~~~~~* //

static void DescolorearGrafo(Grafo G)
{
    assert(G != NULL);
    u32 N = NumeroDeVertices(G);
    for (u32 i = 0; i < N; i++)
    {
        AsignarColor(0, i, G);
    }
}

u32 Greedy(Grafo G, u32 *Orden)
{
    assert(Orden != NULL);

    /* Inicializamos variables */
    u32 n = NumeroDeVertices(G);
    u32 d = Delta(G);
    u32 vertice = Orden[0]; // Primer vertice
    u32 numeroCromatico = 0;
    u32 *presentes = (u32 *)calloc(d + 1, sizeof(u32));
    if (presentes == NULL)
        return MAX_u32;
    u32 *biyeccion = (u32 *)calloc(n, sizeof(u32));
    if (biyeccion == NULL)
        return MAX_u32;

    /* Codigo Greedy */

    DescolorearGrafo(G);

    // Coloreamos el primer vertice
    if (vertice >= n)
    {
        free(biyeccion);
        return MAX_u32;
    }
    AsignarColor(1, vertice, G);
    biyeccion[vertice] = 1;

    for (u32 i = 1; i < n; i++)
    {
        // Tomamos el siguiente vertice
        vertice = Orden[i];
        u32 grado = Grado(vertice, G);
        color color_vertice = 0;

        // Verificamos que Orden es biyectiva {0, 1, ..., n − 1}
        if (biyeccion[Orden[i]] != 0 || Orden[i] >= n)
        {
            free(presentes);
            free(biyeccion);
            return MAX_u32;
        }
        biyeccion[Orden[i]] = 1;

        // Recorro los grado vecinos del vertice y "tacho" con 1 sus colores en p[].
        // i.e. Si el vecino tiene color, p[color_vecino - 1] = 1.
        // Obs: Puedo "tachar" hasta grado colores.
        for (u32 j = 0; j < grado; j++)
        {
            u32 vecino = Vecino(j, vertice, G);
            color color_vecino = Color(vecino, G);
            if (color_vecino > 0) // Si el vecino tiene color
                presentes[color_vecino - 1] = 1;
        }

        // Busco el menor color ausente en p[].
        // i.e. Busco el primer 0 en p[].
        // Obs: Recorro grado + 1 posiciones donde a lo sumo pueden haber grado 1's.
        for (u32 j = 0; j <= grado && color_vertice == 0; j++)
        {
            if (presentes[j] == 0)
                color_vertice = j + 1; // Si lo encontre, color = j + 1
        }

        // Limpio p[j] para la proxima iteracion
        for (u32 j = 0; j < grado; j++)
        {
            u32 vecino = Vecino(j, vertice, G);
            color color_vecino = Color(vecino, G);
            if (color_vecino > 0) // Si el vecino tiene color
                presentes[color_vecino - 1] = 0;
        }

        assert(color_vertice > 0 && color_vertice <= grado + 1);
        AsignarColor(color_vertice, vertice, G);

        // Busco el mayor color asignado
        if (color_vertice > numeroCromatico)
            numeroCromatico = color_vertice;
    }
    assert(coloreoPropio(G));
    free(presentes);
    free(biyeccion);
    return numeroCromatico;
}

//-----------------------Funciones auxuliares que comprueban funcionamineto correcto ---------------------------//

/*
 *
 * @brief Verifica que el bloque actual pueda estar luego del anterior.
 *
 * @param arrayGD puntero a arrayGD
 * @param i indice actual
 *
 * @return u32 1 si es valido, 0 si no lo es.
 *
static u32 checkBGD(Bloque *arrayGD, u32 i)
{

    if (i == 0)
        return 1;

    Bloque b1 = arrayGD[i - 1];
    Bloque b2 = arrayGD[i];

    if (b1.color % 4 == 0 && b2.color % 4 == 0)
    {
        return b1.max_grado >= b2.max_grado;
    }
    else if (b1.color % 4 == 2 && b2.color % 4 == 2)
    {
        return (b1.max_grado + b1.min_grado) >= (b2.max_grado + b2.min_grado);
    }
    else if (b1.color % 2 == 1 && b2.color % 2 == 1)
    {
        return b1.min_grado >= b2.min_grado;
    }

    return 1;
}

static u32 checkELEC(Bloque *arrayGD, u32 i)
{
    return 1;
}

 *
 * @brief Verifica que el bloque actual pueda estar luego del anterior.
 *
 * @param arrayGD puntero a arrayGD
 * @param i indice actual
 *
 * @return u32 1 si es valido, 0 si no lo es.
 *
static u32 checkBEG(Bloque *arrayGD, u32 i)
{

    if (i == 0)
        return 1;

    Bloque b1 = arrayGD[i - 1];
    Bloque b2 = arrayGD[i];

    if (b1.color == 1)
    {
        return 0;
    }
    else if (b1.color == 2 && b2.color != 1)
    {
        return 0;
    }
    else if (b2.color != 2 && b1.color != 2)
    {
        return b1.cant_vertices <= b2.cant_vertices;
    }

    return 1;
}

 *
 * @brief Verifica que el ordenamiento se haya hecho correctamente.
 *
 * @param array puntero a array.
 * @param size tamaño del array.
 * @param valor funcion que toma un puntero a una estructura Bloque y devuelve un valor u32.
 * @param mayorAmenor MAYOR_A_MENOR para ordenar de mayor a menor, si no, de menor a mayor.
 *
 * @return u32 1 si es valido, 0 si no lo es.
 *
static u32 checkOrd(Bloque *array, u32 size, u32 (*valor)(Bloque *), u32 mayorAmenor)
{

    for (u32 i = 1; i < size; i++)
    {
        if (mayorAmenor == MAYOR_A_MENOR)
        {
            if (valor(&array[i - 1]) < valor(&array[i]))
                return 0;
        }
        else
        {
            if (valor(&array[i - 1]) > valor(&array[i]))
                return 0;
        }
    }
    return 1;
}
*/
