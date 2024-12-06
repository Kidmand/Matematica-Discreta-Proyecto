#ifndef ESTRUCTURAGRAFO24_H
#define ESTRUCTURAGRAFO24_H

#include <stdint.h>

#define MAX_u32 UINT32_MAX;

typedef uint32_t u32;

typedef u32 color;

typedef u32 Almacen;
typedef struct Vertice
{
    u32 id;
    u32 grado;
    color color;
    Almacen *vecinos; 
} Vertice;

typedef struct GrafoSt
{
    u32 cant_vertices;
    u32 cant_lados;
    u32 delta;
    Vertice *vertices;
    Almacen *almacen;
} GrafoSt;

#endif
