#include <stdio.h>
#include <windows.h>

void moverWindows(int x, int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
    
    
}
    
void moverControl(int x, int y){
    printf("\033[%d;%df",y,x);
}

int main(int argc, char *argv[]) {
	
    moverWindows(1,2);
    puts("windows (1,2)");
    
    system("pause");
    
    moverControl(1,2);
    puts("control (1,2)");
    
	return 0;
}

