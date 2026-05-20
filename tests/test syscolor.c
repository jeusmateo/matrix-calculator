#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(int argc, char const *argv[])
{

    system("color 08");
    printf("\033[2J\033[H");
    
    return 0;
}
