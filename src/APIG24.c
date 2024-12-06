#include "APIG24.h"
#include "EstructuraGrafo24.h"
#include <assert.h>

#define TAMANO_DEL_STDIN 200
#define ERROR 1
#define OK 0

// ----------------- FUNCIONES AUXILIARES -----------------

typedef struct Lado
{
    u32 v1;
    u32 v2;
} Lado;

static Grafo IniciarGrafo()
{
    Grafo G = (Grafo)malloc(sizeof(GrafoSt));
    if (G == NULL)
        return NULL;
    G->cant_vertices = 0;
    G->cant_lados = 0;
    G->delta = 0;
    G->vertices = NULL;
    G->almacen = NULL;
    return G;
}

static u32 IniciarElementosDelGrafo(Grafo G)
{
    assert(G != NULL);
    u32 cant_vertices = G->cant_vertices;

    G->vertices = (Vertice *)malloc(cant_vertices * sizeof(Vertice));
    if (G->vertices == NULL)
        return ERROR;

    G->almacen = (u32 *)malloc(G->cant_lados * 2 * sizeof(u32));
    if (G->almacen == NULL)
        return ERROR;

    for (u32 i = 0; i < cant_vertices; i++)
    {
        G->vertices[i].id = UINT32_MAX;
        G->vertices[i].grado = 0;
        G->vertices[i].color = 0;
        G->vertices[i].vecinos = NULL;
    }
    return OK;
}

static void AlmacenarVecinoDelVertice(Vertice *V, u32 id_vecino)
{
    assert(V != NULL);
    u32 grado = V->grado;
    V->vecinos[grado] = id_vecino;
    V->grado++;
}

static u32 BuscarYGuardar_p(Grafo G)
{
    assert(G != NULL);
    char buf[TAMANO_DEL_STDIN];

    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        switch (buf[0])
        {
        case 'c':
            break;
        case 'p':
            if (sscanf(buf, "p edge %u %u ", &G->cant_vertices, &G->cant_lados) != 2)
                return ERROR;
            return OK;
        default:
            return ERROR;
        }
    }
    return ERROR;
}

static u32 TraerLados_e_YCalcularGrados(Grafo G, Lado **memdir_lados, u32 **memdir_grado_vertices)
{
    assert(G != NULL && memdir_lados != NULL && memdir_grado_vertices != NULL);
    char c;

    // Creamos array para el grado de cada vertice
    *memdir_grado_vertices = calloc(G->cant_vertices, sizeof(u32));
    u32 *grado_vertices = *memdir_grado_vertices;
    if (grado_vertices == NULL)
        return ERROR;

    // Creamos array para guardar v1 y v2 en cada linea "e v1 v2" del stdin
    *memdir_lados = malloc(G->cant_lados * sizeof(struct Lado));
    Lado *lados = *memdir_lados;
    if (lados == NULL)
    {
        free(grado_vertices);
        return ERROR;
    }

    // Cargamos la informacion del stdin en el array lados y
    // Calculamos el grado de cada vertice en el array grado_vertices.
    for (u32 i = 0; i < G->cant_lados; i++)
    {
        // Cargamos v1 y v2 de la i-linea "e v1 v2" en el array lados
        if (getchar() != 'e')
        {
            free(grado_vertices);
            free(lados);
            return ERROR;
        }
        if (scanf("%u %u", &lados[i].v1, &lados[i].v2) != 2)
        {
            free(grado_vertices);
            free(lados);
            return ERROR;
        }
        while ((c = getchar()) != '\n' && c != EOF)
            continue;


        if (lados[i].v1 >= G->cant_vertices || lados[i].v2 >= G->cant_vertices)
        {
            free(grado_vertices);
            free(lados);
            return ERROR;
        }

        // Aumentamos el grado de los vertices v1 y v2 en el array grado_vertices
        grado_vertices[lados[i].v1]++;
        grado_vertices[lados[i].v2]++;
    }

    return OK;
}

static u32 StdinToGraph(Grafo G)
{
    assert(G != NULL);

    // Obtenemos la cantidad de vertices y lados
    if (BuscarYGuardar_p(G) == ERROR)
        return ERROR;
    u32 cant_vertices = G->cant_vertices;
    u32 cant_lados = G->cant_lados;

    // Inicializamos los elementos del Grafo
    if (IniciarElementosDelGrafo(G) == ERROR)
        return ERROR;

    //
    u32 *grado_vertices = NULL;
    Lado *lados = NULL;
    if (TraerLados_e_YCalcularGrados(G, &lados, &grado_vertices) == ERROR)
        return ERROR;
    assert(grado_vertices != NULL && lados != NULL);

    // Acomodamos el espacio para los vecinos de cada vertice en el almacen
    u32 acumuladorDeGrado = 0;
    u32 delta = 0; // Se calcula el DELTA aprovechando el bucle.
    for (u32 i = 0; i < cant_vertices; i++)
    {
        G->vertices[i].vecinos = &(G->almacen[acumuladorDeGrado]);
        acumuladorDeGrado += grado_vertices[i];

        delta = delta > grado_vertices[i] ? delta : grado_vertices[i]; // Se calcula el DELTA aprovechando el bucle.
    }
    assert(acumuladorDeGrado == cant_lados * 2);
    G->delta = delta;

    // Almacenamos los vecinos de cada vertice
    for (u32 i = 0; i < cant_lados; i++)
    {
        u32 v1 = lados[i].v1;
        u32 v2 = lados[i].v2;
        AlmacenarVecinoDelVertice(&G->vertices[v1], v2); // Agrega vertice2 a los vecinos de vertice1.
        AlmacenarVecinoDelVertice(&G->vertices[v2], v1); // Agrega vertice1 a los vecinos de vertice2.
    }

    free(grado_vertices);
    free(lados);
    return OK;
}

// ---------- FUNCIONES DE CREACIÓN Y DESTRUCCIÓN ----------

Grafo ConstruirGrafo()
{
    Grafo G = IniciarGrafo();
    if (G == NULL)
        return NULL;
    if (StdinToGraph(G) == ERROR)
    {
        DestruirGrafo(G);
        return NULL;
    }

    return G;
}

void DestruirGrafo(Grafo G)
{
    if (G->almacen != NULL)
        free(G->almacen); // Liberar memoria de los vecinos de cada vértice.
    if (G->vertices != NULL)
        free(G->vertices); // Liberar memoria del arreglo de vértices.
    if (G != NULL)
        free(G); // Liberar memoria del grafo.
    G = NULL;
}

// ---------- FUNCIONES DE INFO SOBRE TODO EL GRAFO ----------

u32 NumeroDeVertices(Grafo G)
{
    assert(G != NULL);
    return G->cant_vertices;
}

u32 NumeroDeLados(Grafo G)
{
    assert(G != NULL);
    return G->cant_lados;
}

u32 Delta(Grafo G)
{
    assert(G != NULL);
    return G->delta;
}

// ------------ FUNCIONES DE INFO SOBRE UN VÉRTICE ------------

u32 Grado(u32 i, Grafo G)
{
    assert(G != NULL);
    return i >= G->cant_vertices ? 0 : G->vertices[i].grado;
}

color Color(u32 i, Grafo G)
{
    assert(G != NULL);
    color max_color = MAX_u32;
    return i >= G->cant_vertices ? max_color : G->vertices[i].color;
}

u32 Vecino(u32 j, u32 i, Grafo G)
{
    assert(G != NULL);

    Vertice v = G->vertices[i];

    if (i >= G->cant_vertices || (j >= v.grado))
    {
        const u32 max = MAX_u32;
        return max;
    }
    else
    {
        return v.vecinos[j];
    }
}

// ------------------- FUNCIONES DE COLORES -------------------

void AsignarColor(color x, u32 i, Grafo G)
{
    assert(G != NULL);
    if (i < G->cant_vertices)
    {
        G->vertices[i].color = x;
    }
}

void ExtraerColores(Grafo G, color *Color)
{
    assert(G != NULL);
    assert(Color != NULL);
    for (u32 i = 0; i < G->cant_vertices; i++)
    {
        Color[i] = G->vertices[i].color;
    }
}

void ImportarColores(color *Color, Grafo G)
{
    assert(G != NULL);
    assert(Color != NULL);
    for (u32 i = 0; i < G->cant_vertices; i++)
    {
        G->vertices[i].color = Color[i];
    }
}