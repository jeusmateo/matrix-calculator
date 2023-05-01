#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
void cambiarColorFondo(int r, int g, int b);

void leerMatriz(Matriz*);
void crearMatriz(Matriz*);
void reservarMemoria(Matriz*);
void imprimirMatriz(Matriz*);
void imprimirEspaciosMatriz(int, int);
void sumaMatrices(Matriz*, Matriz*);
void multiplicacionMatrizPorEscalar(Matriz* matriz1);
void matrizTranspuesta(Matriz* matriz1);
void multiplicacionMatrices(Matriz* matriz1, Matriz* matriz2);
void recuadro(int, int, int, int);
void gotoab(int, int);

int main(int argc, char const* argv[]) {
	// system("mode con: cols=120 lines=30");
	// cambiarColorFondo(230, 115, 115);
	printf("\033[44m\033[2J");
	recuadro(2, 1, 119, 30);
	recuadro(4, 2, 117, 6);
	gotoab(49, 3); puts("CALCULADORA DE MATRICES");
	Matriz matriz1, matriz2;
	int operacion;

	do {

		gotoab(4, 7);puts("1-Suma de matrices");
		gotoab(4, 8);puts("2-Multiplicacion de matriz por escalar");
		gotoab(4, 9);puts("3-Multiplicacion de dos matrices");
		gotoab(4, 10);puts("4-Obtencion de la transpuesta de una matriz");
		gotoab(4, 11);puts("0-Salir");
		gotoab(4, 6);puts("Ingrese el numero de operacion segun el menu:");
		gotoab(4, 13);puts("Opcion deseada:");
		gotoab(4, 14);scanf("%d", &operacion);

		switch (operacion) {
		case 1:
			sumaMatrices(&matriz1, &matriz2);
			break;
		case 2:
			multiplicacionMatrizPorEscalar(&matriz1);
			break;
		case 3:
			multiplicacionMatrices(&matriz1, &matriz2);
			break;
		case 4:
			matrizTranspuesta(&matriz1);
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

void cambiarColorFondo(int r, int g, int b) {
	printf("\033[48;2;%d;%d;%dm", r, g, b);
	clearscreen();
}


void crearMatriz(Matriz* matriz) {
	puts("Tamanio matriz: ");
	guardarPosicionCursor();
	gotoab(21,17);puts("_ x _");
	restaurarPosicionCursor();
	gotoab(21,17);scanf("%d", &matriz->filas);
	moverCursorDerecha(4);
	moverCursorArriba(1);
	gotoab(25,17);scanf("%d", &matriz->columnas);
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
			moverCursorArriba(1);
			moverCursorDerecha((col + 1) * 8);
		}
		putchar('\n');
	}
	return;
}

void imprimirMatriz(Matriz* matriz) {
	for (int row = 0; row < matriz->filas; row++) {
		for (int col = 0; col < matriz->columnas; col++) {
			printf("%g\t", matriz->datos[row][col]);
		}
		putchar('\n');
	}
}

void sumaMatrices(Matriz* matriz1, Matriz* matriz2) {
	gotoab(16,16);crearMatriz(matriz1);
	gotoab(16,16);crearMatriz(matriz2);

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

void multiplicacionMatrizPorEscalar(Matriz* matriz1) {
	float matrizEscalar;
	crearMatriz(matriz1);


	puts("Digite los datos de la matriz 1:");
	leerMatriz(matriz1);

	puts("Digite el dato de la matriz escalar:");
	scanf("%f", &matrizEscalar);


	Matriz matrizResultado;
	matrizResultado.filas = matriz1->filas;
	matrizResultado.columnas = matriz1->columnas;
	reservarMemoria(&matrizResultado);



	for (int i = 0; i < matrizResultado.filas; i++) {
		for (int j = 0; j < matrizResultado.columnas; j++) {
			matrizResultado.datos[i][j] = matriz1->datos[i][j] * matrizEscalar;
		}
		puts("\n");
	}

	puts("El resultado de la multiplicacion de la matriz 1 y la escalar es: ");
	imprimirMatriz(&matrizResultado);


}

void matrizTranspuesta(Matriz* matriz1) {
	clearscreen();
	crearMatriz(matriz1);

	if (matriz1->filas >= 3 && matriz1->columnas >= 3) {
		Matriz matrizResultado;
		puts("Digite los datos de la matriz 1:");
		leerMatriz(matriz1);
		matrizResultado.filas = matriz1->filas;
		matrizResultado.columnas = matriz1->columnas;
		reservarMemoria(&matrizResultado);



		for (int i = 0; i < matrizResultado.filas; i++) {
			for (int j = 0; j < matrizResultado.columnas; j++) {

				matrizResultado.datos[i][j] = matriz1->datos[j][i];
			}
		}
		puts("La matriz transpuesta es: ");
		imprimirMatriz(&matrizResultado);
	}
	else {
		puts("Datos incorrectos");
	}
}



void multiplicacionMatrices(Matriz* matriz1, Matriz* matriz2) {
	clearscreen();
	crearMatriz(matriz1);
	crearMatriz(matriz2);

	if (matriz1->filas != matriz2->columnas) {
		puts("No se pueden multiplicar, el numero de columnas de la primera matriz debe coincidir con el número de filas de la segunda matriz");
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
			matrizResultado.datos[i][j] = 0;
			for (int k = 0; k < matrizResultado.columnas; k++) {
				matrizResultado.datos[i][j] = matrizResultado.datos[i][j] + (matriz1->datos[i][k] * matriz2->datos[k][j]);
			}
		}
	}
	puts("El resultado de la multiplicacion de la matriz 1 y matriz 2 es: ");
	imprimirMatriz(&matrizResultado);
}


void recuadro(int xs, int ys, int xi, int yi) {
	int i;

	for (i = ys; i <= yi; i++) {
		gotoxy(xs, i); putchar(179);
		gotoxy(xi, i); putchar(179);
	}

	for (i = xs; i <= xi; i++) {
		gotoxy(i, ys); putchar(196);
		gotoxy(i, yi); putchar(196);
	}



	gotoxy(xs, ys); putchar(218);
	gotoxy(xi, yi); putchar(217);
	gotoxy(xi, ys); putchar(191);
	gotoxy(xs, yi); putchar(192);

}


void gotoab(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
