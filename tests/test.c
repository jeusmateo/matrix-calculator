#include <stdio.h>
#include <stdlib.h>

int main() {
    int** matriz;

    // Asignar memoria dinámicamente para la matriz
    matriz = (int**)malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matriz[i] = (int*)malloc(3 * sizeof(int));
    }

    // Leer los elementos de la matriz
    printf("Introduce los elementos de la matriz:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    // Mostrar los elementos de la matriz
    printf("La matriz es:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Liberar memoria asignada dinámicamente
    for (int i = 0; i < 3; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
