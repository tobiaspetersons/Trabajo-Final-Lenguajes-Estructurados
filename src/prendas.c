#include <stdio.h>
#include <string.h>
#include "prendas.h"
#include "utils.h"

void agregarPrenda() {
    char opcion;
    do
    {
        Prenda p;
        char linea[256];

        printf("Código: ");
        scanf("%d", &p.codigo);
        printf("Nombre: ");
        scanf("%49s", p.nombre);
        printf("Color: ");
        scanf("%29s", p.color);
        printf("Talle: ");
        scanf("%9s", p.talle);
        printf("Precio: ");
        scanf("%f", &p.precio);
        printf("Stock: ");
        scanf("%d", &p.stock);
        p.estado = 1;

        sprintf(linea, "%d,%s,%s,%s,%.2f,%d,%d", p.codigo, p.nombre, p.color, p.talle, p.precio, p.stock, p.estado);
        guardarLinea("data/prendas.txt", linea);
        printf("Prenda agregada con éxito.\n");

        printf("¿Desea agregar otra prenda? (s/n): ");
        scanf(" %c", &opcion); 
    } while (opcion == 's' || opcion == "S");
}

void inhabilitarPrenda() {
    int codigo, cantidad, encontrado = 0;
    char lineas[100][256];

    listarPrendas(1); // muestra las prendas activas antes de pedir el código

    printf("Ingrese el código de la prenda a dar de baja: ");
    scanf("%d", &codigo);

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%d,%d", &p.codigo, p.nombre, p.color, p.talle, &p.precio, &p.stock, &p.estado);
        if (p.codigo == codigo && p.estado == 1) {
            sprintf(lineas[i], "%d,%s,%s,%s,%.2f,%d,0", p.codigo, p.nombre, p.color, p.talle, p.precio, p.stock); // estado a 0
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        FILE *f = fopen("data/prendas.txt", "w");
        for (int i = 0; i < cantidad; i++) {
            fprintf(f, "%s\n", lineas[i]);
        }
        fclose(f);
        printf("Prenda dada de baja con éxito.\n");
    } else {
        printf("Prenda no encontrada o ya inactiva.\n");
    }
}

void habilitarPrenda() {
    int codigo, cantidad, encontrado = 0;
    char lineas[100][256];

    listarPrendas(0); // muestra las prendas inactivas antes de pedir el código

    printf("Ingrese el código de la prenda a habilitar: ");
    scanf("%d", &codigo);

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%d,%d", &p.codigo, p.nombre, p.color, p.talle, &p.precio, &p.stock, &p.estado);
        if (p.codigo == codigo && p.estado == 0) {
            sprintf(lineas[i], "%d,%s,%s,%s,%.2f,%d,1", p.codigo, p.nombre, p.color, p.talle, p.precio, p.stock); // estado a 1
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        FILE *f = fopen("data/prendas.txt", "w");
        for (int i = 0; i < cantidad; i++) {
            fprintf(f, "%s\n", lineas[i]);
        }
        fclose(f);
        printf("Prenda habilitada con éxito.\n");
    } else {
        printf("Prenda no encontrada o ya activa.\n");
    }
}

void ModificarStockPrenda() {
    int codigo, nuevoStock, cantidad, encontrado = 0;
    char lineas[100][256];

    listarPrendasActivas(); // muestra las prendas activas antes de pedir el código

    printf("Ingrese el código de la prenda para modificar el stock: ");
    scanf("%d", &codigo);

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%d,%d", &p.codigo, p.nombre, p.color, p.talle, &p.precio, &p.stock, &p.estado);
        if (p.codigo == codigo && p.estado == 1) {
            printf("Stock actual: %d\n", p.stock);
            printf("Ingrese el nuevo stock: ");
            scanf("%d", &nuevoStock);
            p.stock = nuevoStock;
            sprintf(lineas[i], "%d,%s,%s,%s,%.2f,%d,%d", p.codigo, p.nombre, p.color, p.talle, p.precio, p.stock, p.estado);
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        FILE *f = fopen("data/prendas.txt", "w");
        for (int i = 0; i < cantidad; i++) {
            fprintf(f, "%s\n", lineas[i]);
        }
        fclose(f);
        printf("Stock de la prenda modificado con éxito.\n");
    } else {
        printf("Prenda no encontrada o ya inactiva.\n");
    }
}