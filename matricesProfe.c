#include <stdio.h>
#define M 3
#define N 2


void leerMatriz(float matriz[M][N]);
void imprimirMatriz(float matriz[M][N]);
void sumaMatrices(float matriz[M][N], float matriz_2[M][N]);
void matrizEscalar(float matriz[M][N]);
void multiplicacionMatrices(float matriz[M][N], float matriz_2[M][N]);
void matrizTranspuesta(float matriz[M][N]);
void imprimirMatrizTranspuesta(float matriz[N][M]);


int main(int argc, char* argv[]) {
    float matriz[M][N], matriz_2[M][N];
    int operacion;
    do {
        puts("\n1-Suma de matrices.\n2-Multiplicacion de matriz por escalar\n3-Multiplicacion de dos matrices\n4-Obtencion de la transpuesta de una matriz\n0-Salir");
        puts("Ingrese el numero de operacion segun el menu:");
        scanf("%d", &operacion);

        switch (operacion) {
        case 1:
            sumaMatrices(matriz, matriz_2);
            break;
        case 2:
            matrizEscalar(matriz);
            break;
        case 3:
            multiplicacionMatrices(matriz, matriz_2);
            break;
        case 4:
            matrizTranspuesta(matriz);
            break;
        }

    } while (operacion != 0);




    return 0;
}

void leerMatriz(float matriz[M][N]) {
    int fila, col;
    for (fila = 0; fila < M; fila++) {
        for (col = 0; col < N; col++) {
            printf("Introduzca un valor de la matriz en la Posicion [%d][%d]:", fila, col);
            scanf("%f", &matriz[fila][col]);
        }
    }
    printf("\n");

}

void imprimirMatriz(float matriz[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0;j < N; j++) {
            printf("|%.1f", matriz[i][j]);

        }

        printf("|\n");

    }
    printf("\n");
}
void imprimirMatrizTranspuesta(float matriz[N][M]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0;j < N; j++) {
            printf("|%.1f", matriz[i][j]);

        }

        printf("|\n");

    }
    printf("\n");
}

void sumaMatrices(float matriz[M][N], float matriz_2[M][N]) {
    float matriz_Resultado[M][N];
    puts("Ingrese los datos para la matriz 1:");
    leerMatriz(matriz);
    puts("Ingrese los datos para la matriz 2:");
    leerMatriz(matriz_2);
    puts("Matriz 1");
    imprimirMatriz(matriz);
    puts("Matriz 2");
    imprimirMatriz(matriz_2);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matriz_Resultado[i][j] = matriz[i][j] + matriz_2[i][j];
        }
    }
    puts("El resultado de la suma de la matriz 1 y matriz 2 es: ");
    imprimirMatriz(matriz_Resultado);
}

void matrizEscalar(float matriz[M][N]) {
    float matriz_Resultado[M][N];
    float escalar;
    puts("Ingrese los datos para la matriz:");
    leerMatriz(matriz);
    puts("Matriz");
    imprimirMatriz(matriz);

    puts("Ingrese el escalar:");
    scanf("%f", &escalar);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matriz_Resultado[i][j] = matriz[i][j] * escalar;
        }
    }
    puts("El resultado de la suma de la matriz por el escalar es: ");
    imprimirMatriz(matriz_Resultado);
}

void multiplicacionMatrices(float matriz[M][N], float matriz_2[M][N]) {
    float matriz_Resultado[M][N];
    puts("Ingrese los datos para la matriz 1:");
    leerMatriz(matriz);
    puts("Ingrese los datos para la matriz 2:");
    leerMatriz(matriz_2);
    puts("Matriz 1");
    imprimirMatriz(matriz);
    puts("Matriz 2");
    imprimirMatriz(matriz_2);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matriz_Resultado[i][j] = 0;
            for (int k = 0; k < N; k++) {
                matriz_Resultado[i][j] = (matriz_Resultado[i][j] + (matriz[i][k] * matriz_2[k][j]));
            }
        }
    }
    puts("El resultado de la multiplicacion de la matriz 1 y matriz 2 es: ");
    imprimirMatriz(matriz_Resultado);
}

void matrizTranspuesta(float matriz[M][N]) {
    float matriz_Resultado[N][M];
    puts("Ingrese los datos para la matriz:");
    leerMatriz(matriz);
    puts("Matriz");
    imprimirMatriz(matriz);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matriz_Resultado[i][j] = matriz[j][i];
        }
    }
    puts("La matriz transpuesta es: ");
    imprimirMatrizTranspuesta(matriz_Resultado);

}