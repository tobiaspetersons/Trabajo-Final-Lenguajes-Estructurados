#include <stdio.h>
#include <string.h>
#include "prendas.h"
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
void listarPrendas(int estado) {
    char lineas[100][256];
    int cantidad = leerLineas("data/prendas.txt", lineas, 100);

    if (estado == 1) {
        printf("\n--- Prendas activas ---\n");
    } else {
        printf("\n--- Prendas inactivas ---\n");
    }
    printf("Codigo | Nombre | Color | Talle | Precio | Stock\n");
    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%d,%d",
               &p.codigo, p.nombre, p.color, p.talle, &p.precio, &p.stock, &p.estado);
        if (p.estado == estado) {
            printf("%d | %s | %s | %s | %.2f | %d\n", p.codigo, p.nombre, p.color, p.talle, p.precio, p.stock);
        }
    }
}
