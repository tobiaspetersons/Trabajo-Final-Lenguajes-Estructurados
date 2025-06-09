#include <stdio.h>
#include <time.h>
#include <string.h>
#include "movimientos.h"
#include "utils.h"

void registrarMovimiento(Movimiento mov) {
    FILE *f = fopen("data/movimientos.txt", "a");
    if (!f) return;

    if (strlen(mov.fecha) == 0) {
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        strftime(mov.fecha, sizeof(mov.fecha), "%Y-%m-%d %H:%M", tm_info);
    }

    fprintf(f, "%d,%s,%d,%s,%s,%s\n", mov.codigoPrenda, mov.tipo, mov.cantidad, mov.usuario, mov.fecha, mov.detalle);
    fclose(f);
}

void agregarMovimiento(DatosMovimiento datos) {
    Movimiento mov;
    mov.codigoPrenda = datos.codigoPrenda;
    strncpy(mov.tipo, datos.tipo, sizeof(mov.tipo));
    mov.tipo[sizeof(mov.tipo)-1] = '\0';
    mov.cantidad = datos.cantidad;
    strncpy(mov.usuario, datos.usuario, sizeof(mov.usuario));
    mov.usuario[sizeof(mov.usuario)-1] = '\0';
    mov.fecha[0] = 0;
    strncpy(mov.detalle, datos.detalle, sizeof(mov.detalle));
    mov.detalle[sizeof(mov.detalle)-1] = '\0';
    registrarMovimiento(mov);
}

void listarMovimientos() {
    limpiarConsola();
    FILE *f = fopen("data/movimientos.txt", "r");
    if (!f) {
        printf("No hay movimientos registrados.\n");
        printf("\nPresione ENTER para continuar...");
        limpiarBuffer();
        getchar();
        return;
    }

    printf("\n--- Historial de Movimientos ---\n");
    printf("%-10s | %-12s | %-8s | %-15s | %-16s | %-30s\n", "Prenda", "Tipo", "Cantidad", "Usuario", "Fecha", "Detalle");
    printf("---------- | ------------ | -------- | --------------- | ---------------- | ------------------------------\n");

    char linea[256];
    while (fgets(linea, sizeof(linea), f)) {
        int codigo, cantidad;
        char tipo[20], usuario[50], fecha[20], detalle[100];
        sscanf(linea, "%d,%19[^,],%d,%49[^,],%19[^,],%99[^\n]", &codigo, tipo, &cantidad, usuario, fecha, detalle);
        printf("%-10d | %-12s | %-8d | %-15s | %-16s | %-30s\n", codigo, tipo, cantidad, usuario, fecha, detalle);
    }
    fclose(f);
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}