#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct producto {
    int codigo;
    char articulo[50];
    int existencia;
    float precio;
    struct producto* siguiente;
};

typedef struct producto Producto;
typedef struct producto* NodoProducto;

NodoProducto crearNodo(const Producto);
Producto leerProducto(void);
void insertarNodo(NodoProducto, const Producto);
void imprimirProductos(const NodoProducto);

//b
void actualizarDatosProducto(const NodoProducto, const int);

//c
void imprimirProductosSinExistencia(const NodoProducto);

//d
void eliminarProducto(NodoProducto*, char*);

int main(int argc, char const* argv[]) {
    int continuar = 1, opcion = 0, codigo = 0;
    char nombreProd[50];
    Producto datos;

    // insersion d productos a la fuerza 
    datos.codigo = 10;
    strcpy(datos.articulo, "Bandas elasticas");
    datos.existencia = 15;
    datos.precio = 350;

    NodoProducto cabecera = crearNodo(datos);

    datos.codigo = 4;
    strcpy(datos.articulo, "Guantes");
    datos.existencia = 10;
    datos.precio = 300.5;
    insertarNodo(cabecera, datos);

    datos.codigo = 7;
    strcpy(datos.articulo, "Tennis");
    datos.existencia = 5;
    datos.precio = 750;
    insertarNodo(cabecera, datos);

    datos.codigo = 1;
    strcpy(datos.articulo, "Pesas 5 kilos");
    datos.existencia = 20;
    datos.precio = 250;
    insertarNodo(cabecera, datos);

    datos.codigo = 8;
    strcpy(datos.articulo, "Ligas");
    datos.existencia = 14;
    datos.precio = 375;
    insertarNodo(cabecera, datos);


    imprimirProductosSinExistencia(cabecera);
    eliminarProducto(&cabecera, "Tennis");



    do {
        printf("Leer otro articulo?\n0. No\n1. Si\n> ");
        scanf("%d", &continuar);

        if (continuar == 0) break;

        datos = leerProducto();
        insertarNodo(cabecera, datos);

    } while (1);


    do {

        printf("Menu\n1. Actualizar la cantidad y el precio del artículo\n2. Imprimir los datos de los artículos sin existencia\n3. Eliminar el artículo cuyo nombre ha sido proporcionado\n4. Imprimir lista\n0. Salir\n> ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 0:
            printf("\nSaliendo\n");
            break;
        case 1:
            printf("Codigo del producto: ");
            scanf("%d", &codigo);
            actualizarDatosProducto(cabecera, codigo);
            break;

        case 2:
            imprimirProductosSinExistencia(cabecera);
            break;

        case 3:
            printf("Nombre del producto: ");
            fflush(stdin);
            getchar();
            gets(nombreProd);
            eliminarProducto(&cabecera, nombreProd);
            break;

        case 4:
            imprimirProductos(cabecera);
            break;

        default:
            printf("\nOpcion invalida\n");
            continue;
        }
    } while (1);

    return 0;
}

NodoProducto crearNodo(const Producto datos) {
    NodoProducto nuevo = (NodoProducto)malloc(sizeof(Producto));
    nuevo->codigo = datos.codigo;
    strcpy(nuevo->articulo, datos.articulo);
    nuevo->existencia = datos.existencia;
    nuevo->precio = datos.precio;
    nuevo->siguiente = NULL;
    return nuevo;
}

Producto leerProducto(void) {
    Producto nuevo;
    printf("Codigo: ");
    scanf("%d", &nuevo.codigo);

    printf("Nombre: ");
    fflush(stdin);
    getchar();
    gets(nuevo.articulo);

    printf("Existencia: ");
    scanf("%d", &nuevo.existencia);

    printf("Precio: ");
    scanf("%f", &nuevo.precio);
    return nuevo;
}

void insertarNodo(NodoProducto cabecera, const Producto datos) {
    NodoProducto anterior, actual, nuevo;

    anterior = NULL;
    actual = cabecera;

    nuevo = crearNodo(datos);

    while (actual != NULL) {
        anterior = actual;
        actual = actual->siguiente;
    }

    anterior->siguiente = nuevo;
    nuevo->siguiente = NULL;

}


void imprimirProductos(const NodoProducto cabecera) {
    NodoProducto actual = cabecera;

    printf("\n%8s\t%20s\t%8s\t%8s\n", "Codigo", "Articulo", "Exist.", "Precio");
    while (actual != NULL) {
        printf("%8d\t%20s\t%8d\t%8.2f\n", actual->codigo, actual->articulo, actual->existencia, actual->precio);
        actual = actual->siguiente;
    }

}

//b
void actualizarDatosProducto(const NodoProducto cabecera, const int codigo) {
    int opcion = 0;
    NodoProducto actual;

    actual = cabecera;

    while (actual != NULL && actual->codigo != codigo) {
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("%d no fue encontrado", codigo);
        return;
    }

    printf("\nQue desea actualizar\n1. Existencia\n2. Precio\n> ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
        printf("Nueva existencia: ");
        scanf("%d", &actual->existencia);
        break;

    case 2:
        printf("Nuevo precio: ");
        scanf("%f", &actual->precio);
        break;

    default:
        printf("\nLa opcion no existe\n");
        // aplica recursion ???????????????'
        actualizarDatosProducto(cabecera, codigo);
        break;
    }

}

//c
void imprimirProductosSinExistencia(const NodoProducto cabecera) {
    NodoProducto actual = cabecera;

    puts("\nProductos sin existencia:");
    printf("%8s\t%20s\t%8s\t%8s\n", "Codigo", "Articulo", "Exist.", "Precio");
    while (actual != NULL) {

        if (actual->existencia == 0)
            printf("%8d\t%20s\t%8d\t%8.2f\n", actual->codigo, actual->articulo, actual->existencia, actual->precio);

        actual = actual->siguiente;
    }

}

//d
void eliminarProducto(NodoProducto* cabecera, char* nombreProducto) {
    printf("\nEliminando nodo %s\n", nombreProducto);
    NodoProducto anterior, actual;

    anterior = NULL;
    actual = *cabecera;

    while (actual != NULL && strcmp(actual->articulo, nombreProducto)) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("\n%s no encontrado\n", nombreProducto);
        return;
    }

    //si es la cabecera dezolasalo
    if (actual == *cabecera) {
        *cabecera = actual->siguiente;
    }
    else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    printf("\nEliminado con exito :D\n");
}