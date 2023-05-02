/*
Integrantes:
Garcia Rios Jimena Guadalupe
Magaña Flores Raul Alejandro
Ortiz Chay Jesus Mateo
Torres Tec Josue David
*/

/*
TODO:
las matrices deven de ser tamaño igual nose dionbde

cambair la interfaz para que quede como bios
notas y simbologia

INTENTAR: hora y fecha a lo bios JAKSJ y formato windos
Poner creditos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MENU_INICIO 1
#define MENU_FIN 5

/*#define lineaDeInicio 1*/
typedef struct matriz {
	float** datos;
	int filas;
	int columnas;

} Matriz;

void gotoxy(int, int);
void limpiarPantalla(void);
void guardarPosicionCursor(void);
void moverCursorDerecha(int columnas);
void moverCursorArriba(int filas);
void restaurarPosicionCursor(void);

void limpiarBuffer(void);

void imprimirInterfaz(char* tituloRecuadro);

void menu(void);

void leerMatriz(Matriz*);
void crearMatriz(Matriz*);
void reservarMemoria(Matriz*);
void imprimirMatriz(Matriz*);
void imprimirMatrizResultado(Matriz* matriz);
void imprimirEspaciosMatriz(int, int);
void imprimirEspaciosMatrizDos(int filas, int col);
void sumaMatrices(Matriz*, Matriz*);
void multiplicacionMatrizPorEscalar(Matriz* matriz1);
void matrizTranspuesta(Matriz* matriz1);
void multiplicacionMatrices(Matriz* matriz1, Matriz* matriz2);
void recuadro(int, int, int, int);

void centrarTexto(char*, int);
void cargando(int, int);

int main(int argc, char const* argv[]) {
	menu();
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
	printf("\033[%d;%df", y + 1, x + 1);
	return;
}

void limpiarPantalla(void) {
	puts("\033[H\033[2J");
	return;
}

void limpiarBuffer(void) {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

void menu(void) {
	int operacion;
	Matriz matriz1, matriz2;

	printf("\033[44m"); // cambio de color a azul bios




	do {
		imprimirInterfaz("CALCULADORA DE MATRICES");
		gotoxy(45, 9);
		puts("Seleccione la opcion deseada:");
		gotoxy(45, 10);
		puts("1-Suma de matrices");
		gotoxy(45, 11);
		puts("2-Multiplicacion de matriz por escalar");
		gotoxy(45, 12);
		puts("3-Multiplicacion de dos matrices");
		gotoxy(45, 13);
		puts("4-Obtencion de la transpuesta de una matriz");
		gotoxy(45, 14);
		puts("0-Salir");

		operacion = 1;
		gotoxy(39, 10);
		putchar('>');

		// Si hay un return en el buffer lo elimina
		int aux = GetAsyncKeyState(VK_RETURN);

		do {
			Sleep(100);
			if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) {
				gotoxy(39, 9 + operacion);
				putchar(' ');
				operacion = operacion == MENU_INICIO ? MENU_FIN : operacion - 1;
				gotoxy(39, 9 + operacion);
				putchar('>');
			}
			else if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) {
				gotoxy(39, 9 + operacion);
				putchar(' ');
				operacion = operacion == MENU_FIN ? MENU_INICIO : operacion + 1;
				gotoxy(39, 9 + operacion);
				putchar('>');
			}
			else if (GetAsyncKeyState(VK_RETURN)) {
				break;
			}

		} while (1);

		limpiarBuffer();

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
		case 5:
			operacion = 0;
			break;
		}
		gotoxy(3, 28);
		system("pause");
		limpiarBuffer();
		limpiarPantalla();
	} while (operacion != 0);

	free(matriz1.datos);
	free(matriz2.datos);
}


void imprimirInterfaz(char* tituloRecuadro) {
	limpiarPantalla();
	recuadro(2, 1, 119, 30);
	recuadro(4, 2, 117, 6);
	centrarTexto(tituloRecuadro, 3);
}

void crearMatriz(Matriz* matriz) {
	recuadro(16, 16, 33, 19);
	puts("Tamanio matriz: ");
	do {

		guardarPosicionCursor();
		gotoxy(21, 17);
		puts("_ x _");
		// restaurarPosicionCursor();
		gotoxy(21, 17);
		scanf("%d", &matriz->filas);
		moverCursorDerecha(4);
		moverCursorArriba(1);
		gotoxy(25, 17);
		scanf("%d", &matriz->columnas);
		if (matriz->filas < 1 || matriz->columnas < 1 || matriz->columnas > 4 || matriz->filas > 4) {
			gotoxy(16, 23);
			puts("Entrada invalida");
		}
	} while (matriz->filas < 1 || matriz->columnas < 1 || matriz->columnas > 4 || matriz->filas > 4);
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
	for (int i = 0, k = 15; i < filas; i++, k++) {
		for (int j = 0, l = 46; j < col; j++, l += 7) {
			gotoxy(l, k);
			puts("   _      "); // ta raro
		}
		putchar('\n');
	}

	restaurarPosicionCursor();
}

void imprimirEspaciosMatrizDos(int filas, int col) {
	guardarPosicionCursor();
	for (int i = 0, k = 15; i < filas; i++, k++) {
		for (int j = 0, l = 80; j < col; j++, l += 7) {
			gotoxy(l, k);
			puts("   _      "); // ta raro
		}
		putchar('\n');
	}

	restaurarPosicionCursor();
}

void leerMatriz(Matriz* matriz) {
	imprimirEspaciosMatriz(matriz->filas, matriz->columnas);
	for (int row = 0, k = 15; row < matriz->filas; row++, k++) {
		for (int col = 0, l = 49; col < matriz->columnas; col++, l += 7) {
			gotoxy(l, k);
			scanf("%f", &matriz->datos[row][col]);
			moverCursorArriba(1);
			moverCursorDerecha((col + 1) * 8);
		}
		putchar('\n');
	}
	return;
}

void imprimirMatriz(Matriz* matriz) {
	for (int row = 0, k = 15; row < matriz->filas; row++, k++) {
		for (int col = 0, l = 83; col < matriz->columnas; col++, l += 7) {
			gotoxy(l, k);
			printf("%g\t", matriz->datos[row][col]);
		}
		putchar('\n');
	}
}
void imprimirMatrizResultado(Matriz* matriz) {
	for (int row = 0, k = 23; row < matriz->filas; row++, k++) {
		for (int col = 0, l = 68; col < matriz->columnas; col++, l += 7) {
			gotoxy(l, k);
			printf("%g\t", matriz->datos[row][col]);
		}
		putchar('\n');
	}
}

void sumaMatrices(Matriz* matriz1, Matriz* matriz2) {
	do {
		imprimirInterfaz("SUMA DE MATRICES");
		gotoxy(16, 16);
		crearMatriz(matriz1);
		// Limpiar linea
		for (int i = 16; i <= 31; i++) {
			gotoxy(i, 23);
			putchar(' ');
		}
		gotoxy(49, 12);
		puts("Matriz 1");
		imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas);
		gotoxy(16, 16);
		crearMatriz(matriz2);
		// Limpiar linea
		for (int i = 16; i <= 31; i++) {
			gotoxy(i, 23);
			putchar(' ');
		}
		gotoxy(83, 12);
		puts("Matriz X");
		imprimirEspaciosMatrizDos(matriz2->filas, matriz2->columnas);

		if (matriz1->filas != matriz2->filas || matriz1->columnas != matriz2->columnas) {
			gotoxy(16, 23);
			puts("No se pueden sumar");
			gotoxy(3, 28);
			system("pause");
		}
	} while (matriz1->filas != matriz2->filas || matriz1->columnas != matriz2->columnas);

	gotoxy(49, 12);
	puts("Matriz 1");
	leerMatriz(matriz1);
	gotoxy(83, 12);
	puts("Matriz 1");
	imprimirMatriz(matriz1);

	gotoxy(49, 12);
	puts("Matriz 2");
	leerMatriz(matriz2);
	cargando(80, 27);
	Matriz matrizResultado;
	matrizResultado.filas = matriz1->filas;
	matrizResultado.columnas = matriz1->columnas;
	reservarMemoria(&matrizResultado);
	for (int i = 0; i < matrizResultado.filas; i++) {
		for (int j = 0; j < matrizResultado.columnas; j++) {
			matrizResultado.datos[i][j] = matriz1->datos[i][j] + matriz2->datos[i][j];
		}
	}
	gotoxy(68, 21);
	puts("Resultado");
	imprimirMatrizResultado(&matrizResultado);
}

void multiplicacionMatrizPorEscalar(Matriz* matriz1) {
	// limpiarPantalla();
	// imprimirInterfaz();
	imprimirInterfaz("MULTIPLICACION POR ESCALAR");
	float matrizEscalar;
	gotoxy(16, 16);
	crearMatriz(matriz1);
	// Limpiar linea
	for (int i = 16; i <= 31; i++) {
		gotoxy(i, 23);
		putchar(' ');
	}
	gotoxy(49, 12);
	puts("Matriz 1");
	imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas);
	gotoxy(83, 12);
	puts("Escalar:");
	gotoxy(83, 16);
	puts("_");
	leerMatriz(matriz1);
	gotoxy(83, 16);
	scanf("%f", &matrizEscalar);
	cargando(80, 27);

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

	gotoxy(68, 21);
	puts("Resultado");
	imprimirMatrizResultado(&matrizResultado);
}

void matrizTranspuesta(Matriz* matriz1) {
	Matriz matrizResultado;

	imprimirInterfaz("MATRIZ TRANSPUESTA");
	gotoxy(16, 16);
	crearMatriz(matriz1);

	// Limpiar linea
	for (int i = 16; i <= 31; i++) {
		gotoxy(i, 23);
		putchar(' ');
	}

	gotoxy(49, 12);
	puts("Matriz");
	leerMatriz(matriz1);
	cargando(80, 27);
	matrizResultado.filas = matriz1->columnas;
	matrizResultado.columnas = matriz1->filas;
	reservarMemoria(&matrizResultado);

	for (int i = 0; i < matrizResultado.filas; i++) {
		for (int j = 0; j < matrizResultado.columnas; j++) {

			matrizResultado.datos[i][j] = matriz1->datos[j][i];
		}
	}
	gotoxy(83, 12);
	puts("Matriz transpuesta");
	imprimirMatriz(&matrizResultado);
}

void multiplicacionMatrices(Matriz* matriz1, Matriz* matriz2) {
	imprimirInterfaz("MULTIPLICACION DE MATRICES");

	gotoxy(16, 16);
	crearMatriz(matriz1);
	gotoxy(49, 12);
	puts("Matriz 1");
	imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas);
	gotoxy(16, 16);
	crearMatriz(matriz2);
	gotoxy(83, 12);
	puts("Matriz X");
	imprimirEspaciosMatrizDos(matriz2->filas, matriz2->columnas);

	if (matriz1->filas != matriz2->columnas) {
		gotoxy(16, 23);
		puts("Entrada invalida");
		return;
	}

	gotoxy(49, 12);
	puts("Matriz 1");
	leerMatriz(matriz1);

	imprimirInterfaz("MULTIPLICACION DE MATRICES");

	gotoxy(83, 12);
	puts("Matriz 1");
	imprimirMatriz(matriz1);
	gotoxy(49, 12);
	puts("Matriz 2");
	leerMatriz(matriz2);
	cargando(80, 27);
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
	gotoxy(68, 21);
	puts("Resultado");
	imprimirMatrizResultado(&matrizResultado);
}

void recuadro(int xs, int ys, int xi, int yi) {
	guardarPosicionCursor();
	int i;

	for (i = ys; i <= yi; i++) {
		gotoxy(xs - 1, i - 1);
		putchar(179);
		gotoxy(xi - 1, i - 1);
		putchar(179);
	}

	for (i = xs; i <= xi; i++) {
		gotoxy(i - 1, ys - 1);
		putchar(196);
		gotoxy(i - 1, yi - 1);
		putchar(196);
	}

	gotoxy(xs - 1, ys - 1);
	putchar(218);
	gotoxy(xi - 1, yi - 1);
	putchar(217);
	gotoxy(xi - 1, ys - 1);
	putchar(191);
	gotoxy(xs - 1, yi - 1);
	putchar(192);
	restaurarPosicionCursor();
}

void centrarTexto(char* texto, int y) {
	int tamanio = strlen(texto);
	gotoxy(60 - (tamanio / 2), y);
	puts(texto);
}

void cargando(int x, int y) {
	centrarTexto("EN PROCESO ...", 23);
	for (int i = 3; i <= 116; i++) {
		gotoxy(i, 26);
		putchar(177);
	}
	for (int i = 3; i <= 116; i++) {
		gotoxy(i, 26);
		putchar(219);
		Sleep(1);
	}

	for (int i = 3; i <= 116; i++) {
		gotoxy(i, 23);
		putchar(' ');
	}
	for (int i = 3; i <= 116; i++) {
		gotoxy(i, 26);
		putchar(' ');
	}
}
