/*
Integrantes:
Garcia Rios Jimena Guadalupe
MagaÃ±a Flores Raul Alejandro
Ortiz Chay Jesus Mateo
Torres Tec Josue David
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#define MENU_INICIO 1
#define MENU_FIN 7

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
void leerMatriz(Matriz*, int l, int k);
void crearMatriz(Matriz*);
void reservarMemoria(Matriz*);
void imprimirMatriz(Matriz* matriz, int x, int y);
void imprimirMatrizResultado(Matriz* matriz);
void imprimirEspaciosMatriz(int, int,int x, int y);
void imprimirEspaciosBorrarMatriz(int filas, int col);
void imprimirEspaciosBorrarMatrizDos(int filas, int col);
void imprimirEspaciosMatrizDos(int filas, int col);
void sumaMatrices(Matriz*, Matriz*);
void multiplicacionMatrizPorEscalar(Matriz* matriz1);
void matrizTranspuesta(Matriz* matriz1);
void multiplicacionMatrices(Matriz* matriz1, Matriz* matriz2);
void recuadro(int, int, int, int);
void centrarTexto(char*, int);
void cargando(void);
void funcionDeterminante(Matriz* matriz1);
float calcularDeterminante(Matriz* matriz1);
void inversaMatrizGaussJordan(Matriz* matriz1);
void calcularMatrizIdentidad(Matriz* matriz);
void liberarMemoria(Matriz* matriz);

int main(void) {
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
	while ((ch = getchar()) != '\n' && ch != EOF)
		;
}
void menu(void) {
	system("mode con: cols=120 lines=30");
	int operacion;
	Matriz matriz1, matriz2;
	system("mode con: cols=120 lines=30");
	system("COLOR 17"); // cambio de color a azul bios
	system("mode con: cols=120 lines=30");
	imprimirInterfaz("CALCULADORA DE MATRICES");
	centrarTexto("UNIVERSIDAD AUTONOMA DE YUCATAN", 8);
	centrarTexto("PROGRAMACION ESTRUCTURADA", 10);
	centrarTexto("MIT. EDWIN LEON BOJORQUEZ", 12);
	centrarTexto("INTEGRANTES:", 15);
	centrarTexto("GARCIA RIOS JIMENA GUADALUPE", 17);
	centrarTexto("MAGANIA FLORES RAUL ALEJANDRO", 19);
	centrarTexto("ORTIZ CHAY JESUS MATEO", 21);
	centrarTexto("TORRES TEC JOUSE DAVID", 23);
	gotoxy(3, 28);
	system("pause");

	do {
		system("mode con: cols=120 lines=30");
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
		puts("5-Inversa de una matriz por Gauss Jordan");
		gotoxy(45, 15);
		puts("6-Calculo del determinante de una matriz");
		gotoxy(45, 16);
		puts("0-Salir");
		centrarTexto("FLECHA 'ARRIBA' Y 'ABAJO' O 'W' Y 'S'PARA DESPLAZARSE ENTRE OPCIONES Y 'ENTER' PARA SELECCIONAR LA OPCION", 23);
		centrarTexto("NOTA: TAMANIO MATRICES DE MINIMO 1x1 MAXIMO 4x4", 24);
		centrarTexto("Y LAS MATRICES SIGUEN EL FORMATO FILAS COLUMNAS RESPECTIVAMENTE", 25);
		operacion = 1;
		gotoxy(39, 10);
		putchar('>');

		// Si hay un return en el buffer lo elimina
		GetAsyncKeyState(VK_RETURN);

		do {
			Sleep(200);
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
			inversaMatrizGaussJordan(&matriz1);
			break;
		case 6:
			funcionDeterminante(&matriz1);
			break;
		case 7:
			operacion = 0;
			limpiarPantalla();
			return;
		}
		gotoxy(3, 28);
		system("pause");
		limpiarBuffer();
		limpiarPantalla();
	} while (operacion != 0);

	liberarMemoria(&matriz1);
	liberarMemoria(&matriz2);
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
		gotoxy(18, 17);
		puts("_    x    _   ");
		// restaurarPosicionCursor();
		gotoxy(18, 17);
		scanf("%d", &matriz->filas);
		moverCursorDerecha(4);
		moverCursorArriba(1);
		gotoxy(28, 17);
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


void liberarMemoria(Matriz* matriz) {
	// Liberar memoria para cada elemento del doble apuntador
	for (int i = 0; i < matriz->filas; i++) {
		free(matriz->datos[i]);
	}

	// Liberar memoria para el doble apuntador en sí mismo
	free(matriz->datos);
}


void imprimirEspaciosMatriz(int filas, int col, int x, int y) {
	guardarPosicionCursor();
	for (int i = 0, k = y; i < filas; i++, k++) {
		for (int j = 0, l = x; j < col; j++, l += 7) {
			gotoxy(l, k);
			puts("_      "); // ta raro
		}
		putchar('\n');
	}

	restaurarPosicionCursor();
}
void imprimirEspaciosBorrarMatriz(int filas, int col) {
	guardarPosicionCursor();
	for (int i = 0, k = 15; i < filas; i++, k++) {
		for (int j = 0, l = 46; j < col; j++, l += 7) {
			gotoxy(l, k);
			puts("        "); // ta raro
		}
		putchar('\n');
	}
	restaurarPosicionCursor();
}
void imprimirEspaciosBorrarMatrizDos(int filas, int col) {
	guardarPosicionCursor();
	for (int i = 0, k = 15; i < filas; i++, k++) {
		for (int j = 0, l = 49; j < col; j++, l += 7) {
			gotoxy(l, k);
			puts("        "); // ta raro
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
void leerMatriz(Matriz* matriz, int x, int y) {

	imprimirEspaciosMatriz(matriz->filas, matriz->columnas,x,y);
	for (int row = 0, k = y; row < matriz->filas; row++, k++) {
		for (int col = 0, l = x; col < matriz->columnas; col++, l += 7) {
			gotoxy(l, k);
			scanf("%f", &matriz->datos[row][col]);
			//moverCursorArriba(1);
			//moverCursorDerecha((col + 1) * 8);
		}
		putchar('\n');
	}
	return;
}
void imprimirMatriz(Matriz* matriz, int x, int y) {
	for (int row = 0, k = x; row < matriz->filas; row++, k++) {
		for (int col = 0, l = y; col < matriz->columnas; col++, l += 7) {
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
		centrarTexto("NOTA: LAS MATRICES DEBEN SER DEL MISMO TAMANIO", 6);
		gotoxy(16, 16);
		crearMatriz(matriz1);
		// Limpiar linea
		for (int i = 16; i <= 31; i++) {
			gotoxy(i, 23);
			putchar(' ');
		}
		gotoxy(49, 12);
		puts("Matriz 1");
		imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas,49,15);
		gotoxy(16, 16);
		crearMatriz(matriz2);
		// Limpiar linea
		for (int i = 16; i <= 31; i++) {
			gotoxy(i, 23);
			putchar(' ');
		}
	
		imprimirEspaciosMatriz(matriz2->filas, matriz2->columnas,80,15);

		if (matriz1->filas != matriz2->filas || matriz1->columnas != matriz2->columnas) {
			gotoxy(16, 23);
			puts("No se pueden sumar");
			gotoxy(3, 28);
			system("pause");
		}
	} while (matriz1->filas != matriz2->filas || matriz1->columnas != matriz2->columnas);
	gotoxy(70, 12);
	puts("+");
	gotoxy(49, 12);
	puts("Matriz 1");
	leerMatriz(matriz1, 49, 15);
	gotoxy(83, 12);
	puts("Matriz 2");
	imprimirMatriz(matriz1,49,15);
	gotoxy(49, 12);
	puts("Matriz 1");
	leerMatriz(matriz2, 80, 15);
	imprimirMatriz(matriz2,80,15);
	cargando();
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

	imprimirInterfaz("MULTIPLICACION POR ESCALAR");
	float matrizEscalar;
	gotoxy(16, 16);
	crearMatriz(matriz1);
	// limpiar linea
	for (int i = 16; i <= 31; i++) {
		gotoxy(i, 23);
		putchar(' ');
	}
	gotoxy(49, 12);
	puts("Matriz 1");
	imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas,49,15);
	gotoxy(70, 12);
	puts("X");
	gotoxy(83, 12);
	puts("Escalar:");
	gotoxy(83, 16);
	puts("_");
	leerMatriz(matriz1, 49, 15);
	gotoxy(83, 16);
	scanf("%f", &matrizEscalar);
	cargando();

	Matriz matrizResultado;
	matrizResultado.filas = matriz1->filas;
	matrizResultado.columnas = matriz1->columnas;
	reservarMemoria(&matrizResultado);

	for (int i = 0; i < matrizResultado.filas; i++) {
		for (int j = 0; j < matrizResultado.columnas; j++) {
			matrizResultado.datos[i][j] = matriz1->datos[i][j] * matrizEscalar;
		}
	}

	gotoxy(68, 21);
	puts("Resultado");
	imprimirMatrizResultado(&matrizResultado);
}
void multiplicacionMatrices(Matriz* matriz1, Matriz* matriz2) {
	do {
		imprimirInterfaz("MULTIPLICACION DE MATRICES");
		centrarTexto("NOTA: LAS MATRICES DEBEN COMPARTIR EL MISMO TAMANIO DE COLUMNA EN LA MATRIZ 1 CON TAMANIO DE FILA EN LA MATRIZ 2", 6);
		gotoxy(16, 16);
		crearMatriz(matriz1);
		// Limpiar linea
		for (int i = 16; i <= 31; i++) {
			gotoxy(i, 23);
			putchar(' ');
		}
		gotoxy(49, 12);
		puts("Matriz 1");
		imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas,49,15);
		gotoxy(16, 16);
		crearMatriz(matriz2);
		// Limpiar linea
		for (int i = 16; i <= 31; i++) {
			gotoxy(i, 23);
			putchar(' ');
		}
		gotoxy(83, 12);
		puts("Matriz 2");
		imprimirEspaciosMatriz(matriz2->filas, matriz2->columnas,80,15);
		if (matriz1->columnas != matriz2->filas) {
			gotoxy(16, 23);
			puts("Entrada invalida");
			gotoxy(3, 28);
			system("pause");
		}
	} while (matriz1->columnas != matriz2->filas);

	gotoxy(70, 12);
	puts("X");
	
	leerMatriz(matriz1, 49, 15);

	imprimirMatriz(matriz1,49,15);


	//imprimirEspaciosBorrarMatrizDos(matriz2->filas, matriz2->columnas);
	// imprimirMatriz(matriz1);
	//imprimirEspaciosBorrarMatriz(matriz1->filas, matriz1->columnas);
	leerMatriz(matriz2, 80, 15);

	cargando();
	Matriz matrizResultado;
	matrizResultado.filas = matriz1->filas;
	matrizResultado.columnas = matriz2->columnas;
	reservarMemoria(&matrizResultado);

	for (int i = 0; i < matrizResultado.filas; i++) {
		for (int j = 0; j < matrizResultado.columnas; j++) {
			matrizResultado.datos[i][j] = 0;
			for (int k = 0; k < matriz1->columnas; k++) {
				matrizResultado.datos[i][j] = matrizResultado.datos[i][j] + (matriz1->datos[i][k] * matriz2->datos[k][j]);
			}
		}
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
	leerMatriz(matriz1, 49, 15);
	cargando();
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
	gotoxy(70, 12);
	puts("=");
	imprimirMatriz(&matrizResultado, 80,15);
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
void cargando(void) {
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

void inversaMatrizGaussJordan(Matriz* matriz1) {
	Matriz identidad;

	int invalido = 0;
	float pivote = 0, auxiliar = 0;

	do {
		imprimirInterfaz("INVERSA DE UNA MATRIZ POR GAUSS JORDAN");
		centrarTexto("NOTA: LA MATRIZ DEBE COMPARTIR EL MISMO TAMANIO EN FILAS Y COLUMNAS", 6);
		gotoxy(16, 16);
		crearMatriz(matriz1);
		identidad.filas = matriz1->filas;
		identidad.columnas = matriz1->columnas;
		reservarMemoria(&identidad);
		gotoxy(49, 12);
		puts("Matriz 1");
		imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas,49,15);
		gotoxy(16, 16);

		if (matriz1->columnas != matriz1->filas) {
			liberarMemoria(matriz1);
			gotoxy(16, 23);
			puts("Entrada invalida");
			gotoxy(3, 28);
			system("pause");
			continue;
		}

		leerMatriz(matriz1, 49, 15);

		if (calcularDeterminante(matriz1) == 0) {
			liberarMemoria(matriz1);
			gotoxy(16, 23);
			puts("No se puede hacer el calculo con una matriz con determinante 0");
			gotoxy(3, 28);
			system("pause");
			continue;
		}
		break;
	} while (1);

	cargando();

	// MATRIZ IDENTIDAD
	calcularMatrizIdentidad(&identidad);

	imprimirMatriz(&identidad,80,15);

	// REDUCCION DE LOS RENGLONES
	for (int i = 0; i < matriz1->filas; i++) {
		pivote = matriz1->datos[i][i];
		for (int k = 0; k < matriz1->filas; k++) {
			// PIVOTE A 1 Y OPERACION SOBRE LA FILA
			matriz1->datos[i][k] = matriz1->datos[i][k] / pivote;
			identidad.datos[i][k] = identidad.datos[i][k] / pivote;
		}

		for (int j = 0; j < matriz1->filas; j++) {
			if (i != j) {
				auxiliar = matriz1->datos[j][i];
				for (int k = 0; k < matriz1->filas; k++) {
					matriz1->datos[j][k] = matriz1->datos[j][k] - auxiliar * matriz1->datos[i][k];
					identidad.datos[j][k] = identidad.datos[j][k] - auxiliar * identidad.datos[i][k];
				}
			}
		}
	}

	gotoxy(83, 12);
	puts("Matriz inversa");
	gotoxy(70, 12);
	puts("=");
	imprimirMatriz(&identidad,80,15);

}



void funcionDeterminante(Matriz* matriz1) {
	float determinante = 0;
	do {
		imprimirInterfaz("DETERMINANTE DE UNA MATRIZ");
		centrarTexto("NOTA: LA MATRIZ DEBE COMPARTIR EL MISMO TAMANIO EN FILAS Y COLUMNAS", 6);
		gotoxy(16, 16);
		crearMatriz(matriz1);
		gotoxy(49, 12);
		puts("Matriz 1");
		imprimirEspaciosMatriz(matriz1->filas, matriz1->columnas,49,15);
		gotoxy(16, 16);
		if (matriz1->columnas != matriz1->filas) {
			gotoxy(16, 23);
			puts("Entrada invalida");
			gotoxy(3, 28);
			system("pause");
		}
	} while (matriz1->columnas != matriz1->filas);
	leerMatriz(matriz1, 49, 15);
	cargando();
	gotoxy(83, 12);
	puts("Determinante");
	determinante = calcularDeterminante(matriz1);
	gotoxy(83, 16);
	printf("%g", determinante);
}

float calcularDeterminante(Matriz* matriz1) {
	float determinante = 0;
	float matriz2[3][3];
	if (matriz1->columnas == 1) {
		determinante = matriz1->datos[0][0] * 1;
	}
	else if (matriz1->columnas == 2) {
		determinante = (matriz1->datos[0][0] * matriz1->datos[1][1]) - (matriz1->datos[1][0] * matriz1->datos[0][1]) * 1;
	}
	else if (matriz1->columnas == 3) {
		determinante = matriz1->datos[0][0] * matriz1->datos[1][1] * matriz1->datos[2][2] + matriz1->datos[0][1] * matriz1->datos[1][2] * matriz1->datos[2][0] + matriz1->datos[0][2] * matriz1->datos[1][0] * matriz1->datos[2][1] - matriz1->datos[0][2] * matriz1->datos[1][1] * matriz1->datos[2][0] - matriz1->datos[0][1] * matriz1->datos[1][0] * matriz1->datos[2][2] - matriz1->datos[0][0] * matriz1->datos[1][2] * matriz1->datos[2][1];
	}
	else if (matriz1->columnas == 4) {
		float productos[4];
		// determinante=matriz1->datos[0][0] * matriz1->datos[1][1] * matriz1->datos[2][2] + matriz1->datos[0][1] * matriz1->datos[1][2] * matriz1->datos[2][0] + matriz1->datos[0][2] * matriz1->datos[1][0] * matriz1->datos[2][1] - matriz1->datos[0][2] * matriz1->datos[1][1] * matriz1->datos[2][0] - matriz1->datos[0][1] * matriz1->datos[1][0] * matriz1->datos[2][2] - matriz1->datos[0][0] * matriz1->datos[1][2] * matriz1->datos[2][1];

		for (int contador = 0; contador < 4; contador++) {
			for (int i = 0; i < 4; i++) {
				if (i == contador) {
					i++;
				}
				if (i == 4) {
					break;
				}
				for (int j = 0; j < 3; j++) {
					matriz2[i - 1][j] = matriz1->datos[i][j];
				}
			}
			contador = contador + 1;
			productos[contador - 1] = (pow(-1, contador + 4) * matriz1->datos[contador - 1][3]) * (matriz2[0][0] * matriz2[1][1] * matriz2[2][2] + matriz2[0][1] * matriz2[1][2] * matriz2[2][0] + matriz2[0][2] * matriz2[1][0] * matriz2[2][1] - matriz2[0][2] * matriz2[1][1] * matriz2[2][0] - matriz2[0][1] * matriz2[1][0] * matriz2[2][2] - matriz2[0][0] * matriz2[1][2] * matriz2[2][1]);
			contador = contador - 1;
			determinante = determinante + productos[contador];
		}
	}
	return determinante;
}

void calcularMatrizIdentidad(Matriz* matriz) {
	for (int i = 0; i < matriz->filas; i++) {
		for (int j = 0; j < matriz->filas; j++) {
			matriz->datos[i][j] = i == j ? 1 : 0;
			// matriz->datos[i][j] = 0;
			// if (i == j) {
			// 	matriz->datos[i][j] = 1;
			// }
		}
	}
}
