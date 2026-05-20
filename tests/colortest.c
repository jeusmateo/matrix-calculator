#include <stdio.h>
#include <windows.h>

int main(int argc, char const* argv[]) {



    // for (int i = 0; i < 256;i++) {
    //     for (int j = 0; j < 16;j++) {
    //         for (int k = 0; k < 16;k++) {
    //             printf("\033[48;2;%d;%d;%dm", i, j, k);
    //             putchar(' ');
    //         }
    //     }
    // }

    for (int i = 0; i < 256; i++) {
        printf("\033[48;5;%dm% 0d", i,i);
        putchar(' ');
        // printf("\033[H\033[2J");
    }

    printf("\033[0m");
    putchar(' ');


    return 0;
}
