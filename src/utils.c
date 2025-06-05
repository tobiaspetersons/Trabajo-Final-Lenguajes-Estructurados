#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int guardarLinea(const char *ruta, const char *linea) {
    FILE *f = fopen(ruta, "a");
    if (f == NULL) return 0;
    fprintf(f, "%s\n", linea);
    fclose(f);
    return 1;
}

int leerLineas(const char *ruta, char lineas[][BUFFER_LINEA], int maxLineas) {
    FILE *f = fopen(ruta, "r");
    if (f == NULL) return 0;
    int i = 0;
    while (fgets(lineas[i], BUFFER_LINEA, f) && i < maxLineas) {
        // Elimina el salto de línea al final
        lineas[i][strcspn(lineas[i], "\n")] = 0;
        i++;
    }
    fclose(f);
    return i; // cantidad de líneas leídas
}

void inicializarArchivos() {
    FILE *f;
    int crearAdmin = 0;

    // verifica y crea data/usuarios.txt si no existe
    f = fopen("data/usuarios.txt", "r");
    if (f == NULL) {
        f = fopen("data/usuarios.txt", "w");
        if (f != NULL) {
            fprintf(f, "admin,admin,1,1\n");
            fclose(f);
            crearAdmin = 1;
        }
    } else {
        fclose(f);
    }

    // verifica y crea data/prendas.txt si no existe
    f = fopen("data/prendas.txt", "r");
    if (f == NULL) {
        f = fopen("data/prendas.txt", "w");
        if (f != NULL) fclose(f);
    } else {
        fclose(f);
    }

    if (crearAdmin) {
        printf("\n------------------------------------------\n");
        printf("Primera ejecución: usuario admin creado.\n");
        printf("Usuario: admin\nContraseña: admin\n");
        printf("------------------------------------------\n\n");
    }
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpiarConsola() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}