#ifndef APIG24Parte2_H
#define APIG24Parte2_H

// Importación de las librerías necesarias:
#include "APIG24.h"
#include "EstructuraGrafo24.h"

// ------------------------------------- Greedy ---------------------------------------

/**
 * @brief Función que colorea los vértices de G con el arlgoritmo de Greedy.
 *
 * @param G: Grafo a colorear.
 * @param Orden: Orden en el que se recorrerán los vértices para el coloreo.
 *
 * @return Si todo anduvo bien devuelve el u32 numero de colores que usa el coloreo, si no 
 *         el MAX_u32 (2^32 - 1).
 * 
 * @note - `PRE`: Orden apunta a un sector de memoria con n lugares.
 *
 * @note - `¿Cómo funciona?`
 * @note   En este caso consiste en recorrer los vértices en un orden determinado y asignar
 *         a cada vértice el menor color posible que no esté siendo usado por sus vecinos.
 *
 * @note - `Complejidad`: Tiempo: O(m) Espacio: O(n)
 * 
 * @note - `Primer color`: 1.
 */
u32 Greedy(Grafo G, u32 *Orden);

// -------------------------------------------------------------------------------------

// ------------------------ Funciones para crear ordenes -------------------------------

/**
 * @brief Ordena los vertices por bloque de colores como en el VIT, llenando el array Orden 
 *        de la siguiente forma:
 * @brief 1. Vertices v tal que C(v) es divisible por 4, ordenados por bloque de color x de 
 *        acuerdo con M (x) (de mayor a menor).
 * @brief 2. Vertices v tal que C(v) es par y no divisible por 4, ordenados por bloque de 
 *        color x de acuerdo con M (x) + m(x) (de mayor a menor).
 * @brief 3. Vertices v tal que C(v) es impar y no divisible por 4, ordenados por bloque de 
 *        color x de acuerdo con m(x) (de mayor a menor).
 * 
 * @param G: Grafo con el que trabajar.
 * @param Orden: Areglo Orden a llenar.
 *
 * @return Si todo anduvo bien devuelve el char 0, si no el char 1.
 *
 * @note - `PRE`: G tiene un coloreo propio con colores {1, 2, .., r} para alg ́un r.
 * @note - `PRE`: Orden apunta a una region de memoria con n lugares.
 * @note - `Complejidad`: Tiempo: O(n) Espacio: O(?)
 * 
 * @note - `¿Cómo funciona?`
 * @note   Vertices con alto grado en general tienen mayores problemas para ser coloreados. 
 * @note   Asi que poner primero los vertices de mayor grado deberia dar un buen coloreo....
 *         pero eso no necesariamente sera un ordenamiento por bloque de colores.
 * @note   Por lo tanto, debemos ordenar los colores, de acuerdo con los grados de los 
 *         vertices de ese color. 
 * @note   Podriamos tomar el promedio de los grados, o el mayor grado, o el menor grado....
 *         aca hicimos una mezcla entre el mayor y el menor grado, con un test de 
 *         divisibilidad para que sea facil chequear la funcion en el caso de un grafo 
 *         regular por ejemplo y ademas para mezclar los colores.
 */
char GulDukat(Grafo G, u32 *Orden);

/**
 * @brief Ordena los vertices por bloque de colores como en el VIT, llenando el array Orden 
 *        con los vertices en el siguiente orden:
 * @brief 1. Vertices v tal que C(v) = X1 es el color menos usado sin contar a 1 y 2.
 * @brief 2. Vertices v tal que C(v) = X2 es el color menos usado sin contar a 1, 2 y X1.
 * @brief 3. Vertices v tal que C(v) = X3 es el color menos usado sin contar a 1, 2, X1 y X2.
 * @brief 4. ...
 * @brief 5. Vertices v tal que C(v) = Xr-2 es el color menos usado sin contar a 1, 2, X1, X2, ..., Xr-3.
 * @brief 6. Vertices v tal que C(v) = 2
 * @brief 7. Vertices v tal que C(v) = 1
 * 
 * @param G: Grafo con el que trabajar.
 * @param Orden: Areglo Orden a llenar.
 *
 * @return Si todo anduvo bien devuelve el char 0, si no el char 1.
 *
 * @note - `PRE`: G tiene un coloreo propio con colores {1, 2, .., r} para alg ́un r.
 * @note - `PRE`: Orden apunta a una region de memoria con n lugares.
 * @note - `Complejidad`: Tiempo: O(n) Espacio: O(?)
 * 
 * @note - `¿Cómo funciona?`
 * @note   Poniendo los colores 1 y 2 al ultimo, nos aseguramos que los vertices que menos 
 *         problemas tuvieron para ser coloreados sean coloreados al final. 
 * @note   Y los demas colores los ordenamos por cardinalidad, asumiendo que los colores que
 *         menos vertices tienen son los mas problematicos, y poniendolos al principio quizas
 *         podamos bajar la cantidad de colores.
 */
char ElimGarak(Grafo G, u32 *Orden);
char Orden_Eleccion(Grafo G, u32 *Orden);

// -------------------------------------------------------------------------------------

#endif
