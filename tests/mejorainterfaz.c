#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>

void lineaYColumna(int lin, int col);
void recuadro(int lin1, int col1, int lin2, int col2);
int menu(int lin1, int col1, int qtd, char lista[3][40]);
void colorDeTexto(int letras, int fondo);

// Color letras
enum
{
    BLACK,        // 0
    BLUE,         // 1
    GREEN,        // 2
    CYAN,         // 3
    RED,          // 4
    MAGENTA,      // 5
    BROWN,        // 6
    LIGHTGRAY,    // 7
    DARKGRAY,     // 8
    LIGHTBLUE,    // 9
    LIGHTGREEN,   // 10
    LIGHTCYAN,    // 11
    LIGHTRED,     // 12
    LIGHTMAGENTA, // 13
    YELLOW,       // 14
    WHITE         // 15

};
// Color fondos
enum
{
    _BLACK = 0,          // 0
    _BLUE = 16,          // 1
    _GREEN = 32,         // 2
    _CYAN = 48,          // 3
    _RED = 64,           // 4
    _MAGENTA = 80,       // 5
    _BROWN = 96,         // 6
    _LIGHTGRAY = 112,    // 7
    _DARKGRAY = 128,     // 8
    _LIGHTBLUE = 144,    // 9
    _LIGHTGREEN = 160,   // 10
    _LIGHTCYAN = 176,    // 11
    _LIGHTRED = 192,     // 12
    _LIGHTMAGENTA = 208, // 13
    _YELLOW = 224,       // 14
    _WHITE = 240         // 15
};































void colorDeTexto(int letra, int fondo)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fondo);
}





















void lineaYColumna(int lin, int col)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){col - 1, lin - 1}); // coorddenada na tela

    
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}































void recuadro(int lin1, int col1, int lin2, int col2)
{
    int i, j, tamanioLinea, tamanioColumna;

   
    tamanioLinea = lin2 - lin1;
    tamanioColumna = col2 - col1;

    

    for (i = col1; i <= col2; i++)
    { 
        lineaYColumna(lin1, i);
        printf("%c", 196);
        lineaYColumna(lin2, i);
        printf("%c", 196);
    }

    for (i = lin1; i <= lin2; i++)
    {
        lineaYColumna(i, col1);
        printf("%c", 179);
        lineaYColumna(i, col2);
        printf("%c", 179);
    }
    for (i = lin1 + 1; i < lin2; i++)
    {
        for (j = col1 + 1; j < col2; j++)
        {
            lineaYColumna(i, j);
            printf(" ");
        }
    }
 

 // MARCO DE TODA LA INTERFAZ
    lineaYColumna(lin1, col1);
    printf("%c", 218);
    lineaYColumna(lin1, col2);
    printf("%c", 191);
    lineaYColumna(lin2, col1);
    printf("%c", 192);
    lineaYColumna(lin2, col2);
    printf("%c", 217);

}






















int menu(int lin1, int col1, int qtd, char lista[3][40])
{
    int opc = 1, lin2, col2, linha, i, tamMaxItem, tecla;


    tamMaxItem = strlen(lista[0]);
 
    for (i = 1; i < qtd; i++)
    {
        if (strlen(lista[i]) > tamMaxItem)
        {
            tamMaxItem = strlen(lista[i]);
        }
    }
    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxItem + 4;

  
    colorDeTexto(WHITE, _BLUE);
  
   
    while (1)
    {

        linha = lin1 + 2;
        for (i = 0; i < qtd; i++)
        {
            if (i + 1 == opc)
                colorDeTexto(WHITE, _BLACK);
            else
                colorDeTexto(WHITE, _BLUE);
            lineaYColumna(linha, col1 + 2);
            printf("%s", lista[i]);
            linha += 2;
        }

        
        lineaYColumna(1, 1);
        tecla = getch();
        lineaYColumna(22, 1);
        
       
        if (tecla == 27)
        { 
            opc = 0;
            break;
        }
        else if (tecla == 13)
        { 
            break;
        }
        
        else if (tecla == 72)
        { 
            if (opc > 1)
                opc--; 
        }
        else if (tecla == 80)
        { 
            if (opc < qtd)
                opc++; 

            
        }
    }
    return opc;
}


























int main()
{
    int opc;
    char lista[5][40] = {"Suma de matrices", "Matriz por escalar", "Multiplicacion de matrices", "matriz transpuesta", "banana"};

    setlocale(LC_ALL, "");
    colorDeTexto(WHITE, _BLACK);
    lineaYColumna(24, 1);
    printf("");

    return 0;
}
