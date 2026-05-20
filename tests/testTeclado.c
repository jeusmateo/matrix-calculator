
#include <stdio.h>
#include <conio.h>

int main() {
    int tecla;

    printf("Presiona la tecla de flecha hacia arriba.\n");

    // Espera hasta que se presione una tecla
    while (!kbhit());

    // Lee el código de la tecla presionada
    tecla = getch();

    // Verifica si la tecla de flecha hacia arriba fue presionada
    if (tecla == 72) {
        printf("La tecla de flecha hacia arriba fue presionada.\n");
    }
    else {
        printf("Otra tecla fue presionada.\n");
    }

    return 0;
}

// #include <stdio.h>
// #include <conio.h>

// int main() {
//     int tecla;

//     while (1) {


//         if (kbhit()) { // Si una tecla ha sido presionada
//             tecla = getch(); // Obtener el código ASCII de la tecla presionada
//             printf("%d\n", tecla);


//             printf(".\n");
//             if (tecla == 72) { // 72 es el código ASCII de la flecha hacia arriba
//                 printf("La tecla de flecha hacia arriba ha sido presionada.\n");
//             }
//         }
//     }

//     return 0;
// }
