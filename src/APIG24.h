#ifndef APIG24_H
#define APIG24_H

#include <stdio.h>
#include <stdlib.h>

// el .h de abajo debe tener definida GrafoSt, u32 y color.
#include "EstructuraGrafo24.h"

// Grafo es un puntero a una estructura GrafoSt,
// la cual debe estar definida en el .h de arriba

typedef GrafoSt *Grafo;

// ---------- FUNCIONES DE CREACIÓN Y DESTRUCCIÓN ----------

// debe leer desde stdin
Grafo ConstruirGrafo();

/**
 * @brief   Destruye un grafo liberando la memoria asignada.
 *
 * @param G El grafo a destruir/liberar.
 * @note    Si G es NULL, no se realiza ninguna acción.
 */
void DestruirGrafo(Grafo G);

// ---------- FUNCIONES DE INFO SOBRE TODO EL GRAFO ----------

/**
 * @brief   Obtiene el número de vértices en el grafo.
 *
 * @param G El grafo del cual se desea obtener el número de vértices.
 * @return  El número de vértices en el grafo.
 */
u32 NumeroDeVertices(Grafo G);

/**
 * @brief   Esta función devuelve la cantidad de lados que tiene el grafo especificado.
 *
 * @param G El grafo del cual se desea obtener el número de lados.
 * @return  El número de lados del grafo.
 */
u32 NumeroDeLados(Grafo G);

/**
 * @brief   Retorna el valor de la propiedad delta del grafo dado.
 *
 * @param G El objeto grafo.
 * @return  El valor de la propiedad delta del grafo.
 */
u32 Delta(Grafo G);

// ------------ FUNCIONES DE INFO SOBRE UN VÉRTICE ------------

/**
 * @brief   Calcula el grado del vértice con índice i en el grafo G.
 *
 * @param i El índice del vértice.
 * @param G El grafo.
 * @return  El grado del vértice con índice i.
 * @note    Si el índice `i` es mayor o igual a la cantidad de vértices en el grafo, se devuelve 0.
 */
u32 Grado(u32 i, Grafo G);

/**
 * @brief   Devuelve el color del vértice con el índice dado en el grafo.
 *
 * @param i El índice del vértice.
 * @param G El grafo.
 * @return  El color del vértice con el índice dado.
 * @note    Si el índice `i` es mayor o igual a la cantidad de vértices en el grafo, devuelve MAX_u32 (2^32 - 1).
 */
color Color(u32 i, Grafo G);

/**
 * @brief   Devuelve el vecino en la posición j del vértice i en el grafo G.
 *
 * @param j La posición del vecino.
 * @param i El índice del vértice.
 * @param G El grafo.
 * @return  El vecino en la posición j del vértice i.
 * @note    Si el índice `i` es mayor o igual a la cantidad de vértices en G, o si `j` es mayor o igual al grado del vértice `i`, se devuelve MAX_u32 (2^32 - 1).
 */
u32 Vecino(u32 j, u32 i, Grafo G);

// ------------------- FUNCIONES DE COLORES -------------------

/**
 * @brief   Asigna un color a un vértice en un grafo.
 *
 * @param x El color a asignar al vértice.
 * @param i El índice del vértice en el grafo.
 * @param G El grafo en el que se encuentra el vértice.
 * @note    Si el valor de `i` es mayor o igual que el número de vértices en el grafo, no se realizará ninguna asignación de color.
 */
void AsignarColor(color x, u32 i, Grafo G);

/**
 * @brief Extrae el color de cada vértice en un arreglo.
 *
 * @param G El grafo.
 * @param Color Arreglo con G->cant_vertices espacios donde se guardaran los colores.
 */
void ExtraerColores(Grafo G, color *Color);

/**
 * @brief Importa los colores del array en un grafo.
 *
 * @param Color puntero a un arreglo de G->cant_vertices colores
 * @param G El grafo.
 */
void ImportarColores(color *Color, Grafo G);

#endif
