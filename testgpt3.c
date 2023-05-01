#include <stdio.h>

int main() {
    // puts("\033[1;1H\033[1J");
    int matrix[2][3] = { {1, 2, 4}, {0, 0, 0} }; // matriz de ejemplo
    int x = 0, y = 0; // posición inicial del cursor

    // imprimir matriz inicial
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    // actualizar matriz y mover cursor
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == 0) { // si el elemento es cero, actualizar y mover cursor
                matrix[i][j] = x * 3 + y + 1;
                printf("\033[%d;%dH%d", i + 1, y * 5 + 1, matrix[i][j]);
                y++;
                if (y == 3) { // si alcanzamos el final de la fila, pasar a la siguiente fila
                    y = 0;
                    x++;
                }
            }
        }
    }

    return 0;
}
