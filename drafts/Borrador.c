#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


#define menuInicio 1
#define menuFin 5
/*#define lineaDeInicio 1*/
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
void imprimirInterfaz(void);
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
void gotoab(int, int);
void centrarTexto(char*, int);
void cargando(int, int);
void goy(int x, int y);
void imprimirEspaciosEnBlanco(int filas, int col);

int main(int argc, char const* argv[]) {
	int operacion;
    Matriz matriz1, matriz2;
    

/*    clearscreen();*/
    imprimirInterfaz();
    centrarTexto("CALCULADORA DE MATRICES", 3);

	do {
		gotoab(45, 9);puts("Seleccione la opcion deseada:");
		goy(39, 10);
		gotoab(45, 10);puts("1-Suma de matrices");
		gotoab(45, 11);puts("2-Multiplicacion de matriz por escalar");
		gotoab(45, 12);puts("3-Multiplicacion de dos matrices");
		gotoab(45, 13);puts("4-Obtencion de la transpuesta de una matriz");
		gotoab(45, 14);puts("0-Salir");

		/*		centrarTexto("Opcion deseada:");*/
		/*		gotoab(4,14);scanf("%d", &operacion);*/

		operacion = 1;
		gotoab(39, 10);
		putchar('>');
		while (1) {
			if (GetAsyncKeyState(VK_UP)) {
                gotoab(39, 9 + operacion); putchar(' ');
				operacion = operacion == menuInicio ? menuFin : operacion - 1;
/*                gotoab(39, 9); imprimirEspaciosEnBlanco(39, 10 + operacion);*/
				gotoab(39, 9 + operacion);
				putchar('>');
			}
			else if (GetAsyncKeyState(VK_DOWN)) {
                gotoab(39, 9 + operacion); putchar(' ');
				operacion = operacion == menuFin ? menuInicio : operacion + 1;
				// gotoab(39, 10); imprimirEspaciosEnBlanco(39, 10 + operacion);
				gotoab(39, 9 + operacion);
				putchar('>');
				
			}
			else if (GetAsyncKeyState(VK_RETURN)) {
				break;
			}
			Sleep(200);
		}

		switch (operacion) {
		case 5:
			operacion = 0;
			break;
		case 1:
			sumaMatrices(&matriz1, &matriz2);
			gotoab(3, 28);system("pause");
			system("cls");
			break;
		case 2:
			multiplicacionMatrizPorEscalar(&matriz1);
			gotoab(3, 28);system("pause");
			system("cls");
			break;
		case 3:
			multiplicacionMatrices(&matriz1, &matriz2);
			gotoab(3, 28);system("pause");
			system("cls");
			break;
		case 4:
			matrizTranspuesta(&matriz1);
			gotoab(3, 28);system("pause");
			system("cls");
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
	printf("\033[2J");
	return;
}

void imprimirInterfaz(void){
    recuadro(2, 1, 119, 30);
    recuadro(4, 2, 117, 6);

    return;
}


void menu(void){
    
}




void crearMatriz(Matriz* matriz) {
	puts("Tamanio matriz: ");
	guardarPosicionCursor();
	gotoab(21, 17);puts("_ x _");
	restaurarPosicionCursor();
	gotoab(21, 17);scanf("%d", &matriz->filas);
	moverCursorDerecha(4);
	moverCursorArriba(1);
	gotoab(25, 17);scanf("%d", &matriz->columnas);
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
	for (int i = 0, l = 46; i < filas; i++, l += 7) {
		for (int j = 0, k = 15; j < col; j++, k++) {
			gotoab(l, k);puts("   _      ");
		}
		putchar('\n');
	}
	restaurarPosicionCursor();
}
void imprimirEspaciosMatrizDos(int filas, int col) {
	guardarPosicionCursor();
	for (int i = 0, l = 80; i < filas; i++, l += 7) {
		for (int j = 0, k = 15; j < col; j++, k++) {
			gotoab(l, k);puts("   _      ");
		}
		putchar('\n');
	}
	restaurarPosicionCursor();
}

void leerMatriz(Matriz* matriz) {
	imprimirEspaciosMatriz(matriz->filas, matriz->columnas);
	for (int row = 0, k = 15; row < matriz->filas; row++, k++) {
		for (int col = 0, l = 49; col < matriz->columnas; col++, l += 7) {
			gotoab(l, k);scanf("%f", &matriz->datos[row][col]);
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
			gotoab(l, k);printf("%g\t", matriz->datos[row][col]);
		}
		putchar('\n');
	}
}

void imprimirMatrizResultado(Matriz* matriz) {
	for (int row = 0, k = 23; row < matriz->filas; row++, k++) {
		for (int col = 0, l = 68; col < matriz->columnas; col++, l += 7) {
			gotoab(l, k);printf("%g\t", matriz->datos[row][col]);
		}
		putchar('\n');
	}
}

void sumaMatrices(Matriz* matriz1, Matriz* matriz2) {
	system("cls");
	recuadro(2, 1, 119, 30);
	recuadro(4, 2, 117, 6);
	recuadro(16, 16, 33, 19);
	centrarTexto("SUMA DE MATRICES", 3);
	gotoab(16, 16);crearMatriz(matriz1);
	gotoab(49, 12);puts("Matriz 1");imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas);
	gotoab(16, 16);crearMatriz(matriz2);
	gotoab(83, 12);puts("Matriz X"); imprimirEspaciosMatrizDos(matriz2->filas, matriz2->columnas);



	if (matriz1->filas != matriz2->filas || matriz1->columnas != matriz2->columnas) {
		puts("No se pueden sumar");
		return;
	}

	gotoab(49, 12);puts("Matriz 1");
	leerMatriz(matriz1);
	gotoab(83, 12);puts("Matriz 1");imprimirMatriz(matriz1);

	gotoab(49, 12);puts("Matriz 2");
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

	gotoab(68, 21);puts("Resultado");
	imprimirMatrizResultado(&matrizResultado);

}

void multiplicacionMatrizPorEscalar(Matriz* matriz1) {
	system("cls");
	recuadro(2, 1, 119, 30);
	recuadro(4, 2, 117, 6);
	recuadro(16, 16, 33, 19);
	centrarTexto("MULTIPLICACION POR ESCALAR", 3);
	float matrizEscalar;
	gotoab(16, 16);crearMatriz(matriz1);
	gotoab(49, 12);puts("Matriz 1");imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas);gotoab(83, 12);puts("Escalar:"); gotoab(83, 16);puts("_");
	leerMatriz(matriz1);
	gotoab(83, 16);scanf("%f", &matrizEscalar);
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

	gotoab(68, 21);puts("Resultado");
	imprimirMatrizResultado(&matrizResultado);


}

void matrizTranspuesta(Matriz* matriz1) {
	system("cls");
	recuadro(2, 1, 119, 30);
	recuadro(4, 2, 117, 6);
	recuadro(16, 16, 33, 19);
	centrarTexto("MATRIZ TRANSPUESTA", 3);
	gotoab(16, 16);crearMatriz(matriz1);

	if (matriz1->filas >= 3 && matriz1->columnas >= 3) {
		Matriz matrizResultado;
		gotoab(49, 12);puts("Matriz");
		leerMatriz(matriz1);
		cargando(80, 27);
		matrizResultado.filas = matriz1->filas;
		matrizResultado.columnas = matriz1->columnas;
		reservarMemoria(&matrizResultado);



		for (int i = 0; i < matrizResultado.filas; i++) {
			for (int j = 0; j < matrizResultado.columnas; j++) {

				matrizResultado.datos[i][j] = matriz1->datos[j][i];
			}
		}
		gotoab(83, 12);puts("Matriz transpuesta");
		imprimirMatriz(&matrizResultado);
	}
	else {
		puts("Datos incorrectos");
	}
}



void multiplicacionMatrices(Matriz* matriz1, Matriz* matriz2) {
	system("cls");
	recuadro(2, 1, 119, 30);
	recuadro(4, 2, 117, 6);
	recuadro(16, 16, 33, 19);
	centrarTexto("MULTIPLICACION DE MATRICES", 3);
	gotoab(16, 16);crearMatriz(matriz1);
	gotoab(49, 12);puts("Matriz 1");imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas);
	gotoab(16, 16);crearMatriz(matriz2);
	gotoab(83, 12);puts("Matriz X");imprimirEspaciosMatrizDos(matriz2->filas, matriz2->columnas);

	if (matriz1->filas != matriz2->columnas) {
		puts("Entrada invalida");
		return;
	}

	gotoab(49, 12);puts("Matriz 1");
	leerMatriz(matriz1);
	gotoab(83, 12);puts("Matriz 1"); imprimirMatriz(matriz1);
	gotoab(49, 12);puts("Matriz 2");
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
	gotoab(68, 21);puts("Resultado");
	imprimirMatrizResultado(&matrizResultado);
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

void centrarTexto(char* texto, int y) {
	int tamanio = strlen(texto);
	gotoab(60 - (tamanio / 2), y); puts(texto);
}


void cargando(int a, int b) {
	centrarTexto("EN PROCESO ...", 23);
	for (int i = 3; i <= 116;i++) {
		gotoab(i, 26); putchar(177);
	}
	for (int i = 3; i <= 116;i++) {
		gotoab(i, 26); putchar(219);
		Sleep(5);
	}

	for (int i = 3; i <= 116;i++) {
		gotoab(i, 23); putchar(' ');
	}
	for (int i = 3; i <= 116;i++) {
		gotoab(i, 26); putchar(' ');
	}
}

void goy(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

void imprimirEspaciosEnBlanco(int filas, int col) {
	gotoab(filas, col);
	for (int i = 0; i < 3; i++) {
		putchar(' ');
	}
}

