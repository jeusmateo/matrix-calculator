#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// #define parpadeoCursor(void) printf("\033[5m");
// #define resetearModo(void) printf("\033[0m");

typedef struct matriz {
    float** datos;
    int filas;
    int columnas;

} Matriz;


void gotoxy(int, int);
void clearscreen(void);
void guardarPosicionCursor(void);
void moverCursorDerecha(int columnas);
void moverCursorArriba(int filas);
void restaurarPosicionCursor(void);
void colorearFondo(int, int, int);
void resetearModos(void);

void leerMatriz(Matriz*);
void crearMatriz(Matriz*);
void reservarMemoria(Matriz*);
void imprimirMatriz(Matriz*);
void imprimirEspaciosMatriz(int, int);
void sumaMatrices(Matriz*, Matriz*);

int main(int argc, char const* argv[]) {
    Matriz matriz1, matriz2;
    int operacion;
    clearscreen();
    gotoxy(5, 5);
    do {
        puts("1-Suma de matrices.\n2-Multiplicacion de matriz por escalar\n3-Multiplicacion de dos matrices\n4-Obtencion de la transpuesta de una matriz\n0-Salir");
        puts("Ingrese el numero de operacion segun el menu:");
        scanf("%d", &operacion);

        switch (operacion) {
        case 1:
            sumaMatrices(&matriz1, &matriz2);
            break;
        case 2:
            // matrizEscalar(matriz);
            break;
        case 3:
            // multiplicacionMatrices(matriz, matriz_2);
            break;
        case 4:
            // matrizTranspuesta(matriz);
            break;
        }

    } while (operacion != 0);


    return 0;
}


void guardarPosicionCursor(void) {
    printf("\0337");
}

void restaurarPosicionCursor(void) {
    printf("\0338");
}

void moverCursorDerecha(int columnas) {
    moverCursorArriba(1);
    printf("\033[%dC", columnas);
}

void moverCursorArriba(int filas) {
    printf("\033[%dA", filas);
}

void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    return;
}

void clearscreen(void) {
    puts("\033[H\033[2J");
    return;
}

void colorearFondo(int r, int g, int b) {
    printf("\033[48;2;%d;%d;%dm", r, g, b);
}

void resetearModos(void) {
    printf("\033[0m");
}

void crearMatriz(Matriz* matriz) {
    puts("Tamanio matriz: ");
    guardarPosicionCursor();
    puts("_ x _");
    restaurarPosicionCursor();
    scanf("%d", &matriz->filas);
    moverCursorDerecha(4);
    scanf("%d", &matriz->columnas);
    reservarMemoria(matriz);
}

void reservarMemoria(Matriz* matriz) {
    matriz->datos = malloc(matriz->filas * sizeof(float*));
    if (matriz->datos == NULL) {
        puts("Error creando la matriz");
        return;
    }

    for (int i = 0; i < matriz->filas; i++) {
        matriz->datos[i] = malloc(matriz->columnas * sizeof(float));
        if (matriz->datos[i] == NULL) {
            puts("Error creando la matriz");
            return;
        }

    }
}

void imprimirEspaciosMatriz(int filas, int col) {
    guardarPosicionCursor();
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < col; j++) {
            putchar('_');
            putchar('\t');
        }
        putchar('\n');
    }
    restaurarPosicionCursor();
}

void leerMatriz(Matriz* matriz) {
    imprimirEspaciosMatriz(matriz->filas, matriz->columnas);
    for (int row = 0; row < matriz->filas; row++) {
        for (int col = 0; col < matriz->columnas; col++) {
            scanf("%f", &matriz->datos[row][col]);
            moverCursorDerecha((col + 1) * 8);
        }
        putchar('\n');
    }
    return;
}

void imprimirMatriz(Matriz* matriz) {
    for (int row = 0; row < matriz->filas; row++) {
        for (int col = 0; col < matriz->columnas; col++) {
            // colorearFondo(255, 255, 0);
            printf("\033[7;4m");
            printf("%3g", matriz->datos[row][col]);
            Sleep(512);
            resetearModos();
            
        }
        putchar('\n');
            // printf("\033[0m");
    }

}

void sumaMatrices(Matriz* matriz1, Matriz* matriz2) {
    clearscreen();
    crearMatriz(matriz1);
    crearMatriz(matriz2);

    if (matriz1->filas != matriz2->filas || matriz1->columnas != matriz2->columnas) {
        puts("No se pueden sumar");
        return;
    }

    puts("Digite los datos de la matriz 1:");
    leerMatriz(matriz1);

    puts("Digite los datos de la matriz 2:");
    leerMatriz(matriz2);

    Matriz matrizResultado;
    matrizResultado.filas = matriz1->filas;
    matrizResultado.columnas = matriz1->columnas;
    reservarMemoria(&matrizResultado);

    for (int i = 0; i < matrizResultado.filas; i++) {
        for (int j = 0; j < matrizResultado.columnas; j++) {
            matrizResultado.datos[i][j] = matriz1->datos[i][j] + matriz2->datos[i][j];
        }
    }

    puts("El resultado de la suma de la matriz 1 y matriz 2 es: ");
    imprimirMatriz(&matrizResultado);

}
