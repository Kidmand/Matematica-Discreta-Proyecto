#include <stdio.h>

int main()
{
    int n;
    printf("Ingrese el número de vértices: ");
    scanf("%d", &n);

    FILE *archivo;
    archivo = fopen("grafo_completo.txt", "w");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.");
        return 1;
    }

    fprintf(archivo, "p edge %d %d\n", n, n * (n - 1) / 2);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            fprintf(archivo, "e %d %d\n", i, j);
        }
    }

    fclose(archivo);
    printf("Se ha generado el grafo completo en el archivo 'grafo_completo.txt'.\n");

    return 0;
}
