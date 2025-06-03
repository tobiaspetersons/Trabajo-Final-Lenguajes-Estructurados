#include <stdio.h>
#include <string.h>
#include "utils.h"

int guardarLinea(const char *ruta, const char *linea) {
    FILE *f = fopen(ruta, "a");
    if (f == NULL) return 0;
    fprintf(f, "%s\n", linea);
    fclose(f);
    return 1;
}

int leerLineas(const char *ruta, char lineas[][256], int maxLineas) {
    FILE *f = fopen(ruta, "r");
    if (f == NULL) return 0;
    int i = 0;
    while (fgets(lineas[i], 256, f) && i < maxLineas) {
        // Elimina el salto de línea al final
        lineas[i][strcspn(lineas[i], "\n")] = 0;
        i++;
    }
    fclose(f);
    return i; // cantidad de líneas leídas
}