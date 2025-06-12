#include <stdio.h>
#include <string.h>
#include "prendas.h"
#include "utils.h"
#include "movimientos.h"
#include "auth.h"

extern char usuarioActual[50];

void listarPrendas(int estado) {
    limpiarConsola();
    char lineas[100][BUFFER_LINEA];
    int cantidad = leerLineas("data/prendas.txt", lineas, 100);

    if (estado == 1) {
        printf("\n--- Prendas activas ---\n");
    } else {
        printf("\n--- Prendas inactivas ---\n");
    }

    printf("%-6s | %-25s | %-15s | %-10s | %-8s | %-8s | %-5s | %-15s\n",
           "Codigo", "Nombre", "Color", "Talle", "Costo", "Precio", "Stock", "Foto");
    printf("------ | ------------------------- | --------------- | ---------- | -------- | -------- | ----- | ---------------\n");

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.estado == estado) {
            printf("%-6d | %-25s | %-15s | %-10s | %-8.2f | %-8.2f | %-5d | %-15s\n",
                   p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.foto);
        }
    }
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}

void agregarPrenda() {
    limpiarConsola();
    char opcion;
    do
    {
        Prenda p;
        char linea[300];
        char lineas[100][BUFFER_LINEA];

        int cantidad = leerLineas("data/prendas.txt", lineas, 100);

        // asignar código autoincremental (máximo código + 1)
        int maxCodigo = 0;
        for (int i = 0; i < cantidad; i++) {
            int cod;
            sscanf(lineas[i], "%d,%*[^,],%*[^,],%*[^,],%*f,%*f,%*d,%*d,%*[^,]", &cod);
            if (cod > maxCodigo) 
            {
                maxCodigo = cod;
            }
        }
        p.codigo = maxCodigo + 1;

        printf("Nombre: ");
        fgets(p.nombre, sizeof(p.nombre), stdin);
        p.nombre[strcspn(p.nombre, "\n")] = 0;

        printf("Color: ");
        fgets(p.color, sizeof(p.color), stdin);
        p.color[strcspn(p.color, "\n")] = 0;

        printf("Talle: ");
        fgets(p.talle, sizeof(p.talle), stdin);
        p.talle[strcspn(p.talle, "\n")] = 0;

        printf("Costo: $");
        scanf("%f", &p.costo);
        limpiarBuffer();
        printf("Precio: $");
        scanf("%f", &p.precio);
        limpiarBuffer();
        printf("Stock: ");
        scanf("%d", &p.stock);
        limpiarBuffer();
        printf("Nombre de la foto (ej: img_8478): ");
        scanf("%29s", p.foto);
        limpiarBuffer();

        if (p.costo < 0 || p.precio < 0 || p.stock < 0) {
            printf("Costo, precio y stock deben ser valores positivos.\n");
            return;
        }

        p.estado = 1;

        sprintf(linea, "%d,%s,%s,%s,%.2f,%.2f,%d,%d,%s", p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.estado, p.foto);
        guardarLinea("data/prendas.txt", linea);
        printf("Prenda agregada con éxito. Código asignado: %d\n", p.codigo);
        Movimiento mov = {p.codigo, "ALTA", p.stock, usuarioActual, "", "Alta de prenda"};
        registrarMovimiento(mov);

        printf("¿Desea agregar otra prenda? (s/n): ");
        scanf(" %c", &opcion); 
        limpiarBuffer();
        limpiarConsola();
    } while (opcion == 's' || opcion == 'S');
}

void bajaPrenda() {
    limpiarConsola();
    int codigo, cantidad, encontrada = 0, hayActivas = 0;
    char lineas[100][BUFFER_LINEA];
    char tipoBaja;

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    // verifica si hay prendas activas
    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.estado == 1) {
            hayActivas = 1;
            break;
        }
    }

    if (!hayActivas) {
        printf("\nNo hay prendas activas.\n");
        printf("\nPresione ENTER para continuar...");
        limpiarBuffer();
        getchar();
        limpiarConsola();
        return;
    }

    listarPrendas(1); // muestra prendas activas

    printf("Ingrese el código de la prenda a dar de baja: ");
    scanf("%d", &codigo);
    limpiarBuffer();

    printf("¿Desea inhabilitar la prenda o eliminarla definitivamente?\n");
    printf("Ingrese 'i' para inhabilitar o 'f' para eliminar: ");
    scanf(" %c", &tipoBaja);
    limpiarBuffer();

    FILE *f = fopen("data/prendas.txt", "w");
    if (!f) {
        printf("No se pudo abrir el archivo.\n");
        printf("\nPresione ENTER para continuar...");
        limpiarBuffer();
        getchar();
        limpiarConsola();
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);

        if (p.codigo == codigo && p.estado == 1) {
            encontrada = 1;
            if (tipoBaja == 'i' || tipoBaja == 'I') {
                // baja lógica: solo cambia el estado
                sprintf(lineas[i], "%d,%s,%s,%s,%.2f,%.2f,%d,0,%s", p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.foto);
                fprintf(f, "%s\n", lineas[i]);
                printf("Prenda inhabilitada (baja lógica) con éxito.\n");
                Movimiento mov = {p.codigo, "BAJA", 0, usuarioActual, "", "Baja lógica de prenda"};
                registrarMovimiento(mov);
            } else if (tipoBaja == 'f' || tipoBaja == 'F') {
                // baja física: no la escribe, la elimina
                printf("Prenda eliminada definitivamente (baja física).\n");
                Movimiento mov = {p.codigo, "ELIMINACION", 0, usuarioActual, "", "Baja física de prenda"};
                registrarMovimiento(mov);
            } else {
                // opción inválida, vuelve a escribir la línea original
                fprintf(f, "%s\n", lineas[i]);
                printf("Opción inválida. No se realizó ninguna baja.\n");
            }
        } else {
            // escribe todas las demás prendas
            fprintf(f, "%s\n", lineas[i]);
        }
    }
    fclose(f);

    if (!encontrada && hayActivas) {
        printf("Prenda no encontrada o ya inactiva.\n");
    }
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
    limpiarConsola();
}

void habilitarPrenda() {
    int codigo, cantidad, encontrado = 0, hayInhabilitadas = 0;
    char lineas[100][BUFFER_LINEA];

    limpiarConsola();
    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.estado == 0) {
            hayInhabilitadas = 1;
            break;
        }
    }

    if (!hayInhabilitadas) {
        printf("\nNo hay prendas inhabilitadas.\n");
        printf("\nPresione ENTER para continuar...");
        limpiarBuffer();
        getchar();
        limpiarConsola();
        return;
    }

    listarPrendas(0);

    printf("Ingrese el código de la prenda a habilitar: ");
    scanf("%d", &codigo);
    limpiarBuffer();

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.codigo == codigo && p.estado == 0) {
            sprintf(lineas[i], "%d,%s,%s,%s,%.2f,%.2f,%d,1,%s", p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.foto);
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
        Movimiento mov = {codigo, "HABILITACION", 0, usuarioActual, "", "Prenda habilitada"};
        registrarMovimiento(mov);
    } else {
        printf("Prenda no encontrada o ya activa.\n");
    }
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
    limpiarConsola();
}

void modificarPrenda() {
    int codigo, opcion, cantidad;
    char lineas[100][BUFFER_LINEA];
    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    listarPrendas(1);

    printf("Ingrese el código de la prenda a modificar: ");
    scanf("%d", &codigo);
    limpiarBuffer();

    int encontrada = 0;

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);

        if (p.codigo == codigo && p.estado == 1) {
            encontrada = 1;
            printf("¿Qué desea modificar?\n");
            printf("1. Nombre\n2. Color\n3. Talle\n4. Stock\n5. Costo\n6. Precio\n7. Foto\n");
            printf("Ingrese una opción: ");
            scanf("%d", &opcion);
            limpiarBuffer();

            Movimiento mov;

            switch (opcion) {
                case 1:
                    printf("Nombre actual: %s\nNuevo nombre: ", p.nombre);
                    fgets(p.nombre, sizeof(p.nombre), stdin);
                    p.nombre[strcspn(p.nombre, "\n")] = 0;
                    if (strlen(p.nombre) == 0) strcpy(p.nombre, "SinNombre");
                    mov = (Movimiento){p.codigo, "MODIFICACION", 0, usuarioActual, "", "Modificación de nombre"};
                    registrarMovimiento(mov);
                    break;
                case 2:
                    printf("Color actual: %s\nNuevo color: ", p.color);
                    fgets(p.color, sizeof(p.color), stdin);
                    p.color[strcspn(p.color, "\n")] = 0;
                    if (strlen(p.color) == 0) strcpy(p.color, "SinColor");
                    mov = (Movimiento){p.codigo, "MODIFICACION", 0, usuarioActual, "", "Modificación de color"};
                    registrarMovimiento(mov);
                    break;
                case 3:
                    printf("Talle actual: %s\nNuevo talle: ", p.talle);
                    fgets(p.talle, sizeof(p.talle), stdin);
                    p.talle[strcspn(p.talle, "\n")] = 0;
                    if (strlen(p.talle) == 0) strcpy(p.talle, "SinTalle");
                    mov = (Movimiento){p.codigo, "MODIFICACION", 0, usuarioActual, "", "Modificación de talle"};
                    registrarMovimiento(mov);
                    break;
                case 4: {
                    int nuevoStock, stockAnterior = p.stock;
                    printf("Stock actual: %d\nNuevo stock: ", p.stock);
                    scanf("%d", &nuevoStock);
                    limpiarBuffer();
                    if (nuevoStock < 0) {
                        printf("El stock debe ser un valor positivo.\n");
                        return;
                    }
                    p.stock = nuevoStock;
                    int diferencia = nuevoStock - stockAnterior;
                    mov = (Movimiento){p.codigo, "MODIFICACION", diferencia, usuarioActual, "", "Modificación de stock"};
                    registrarMovimiento(mov);
                    break;
                }
                case 5:
                    printf("Costo actual: %.2f\nNuevo costo: ", p.costo);
                    scanf("%f", &p.costo);
                    limpiarBuffer();
                    mov = (Movimiento){p.codigo, "MODIFICACION", 0, usuarioActual, "", "Modificación de costo"};
                    registrarMovimiento(mov);
                    break;
                case 6:
                    printf("Precio actual: %.2f\nNuevo precio: ", p.precio);
                    scanf("%f", &p.precio);
                    limpiarBuffer();
                    mov = (Movimiento){p.codigo, "MODIFICACION", 0, usuarioActual, "", "Modificación de precio"};
                    registrarMovimiento(mov);
                    break;
                case 7:
                    printf("Foto actual: %s\nNueva foto: ", p.foto);
                    fgets(p.foto, sizeof(p.foto), stdin);
                    p.foto[strcspn(p.foto, "\n")] = 0;
                    if (strlen(p.foto) == 0) strcpy(p.foto, "SinFoto");
                    mov = (Movimiento){p.codigo, "MODIFICACION", 0, usuarioActual, "", "Modificación de foto"};
                    registrarMovimiento(mov);
                    break;
                default:
                    printf("Opción inválida.\n");
                    return;
            }

            // Actualiza la línea modificada
            sprintf(lineas[i], "%d,%s,%s,%s,%.2f,%.2f,%d,%d,%s",
                    p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.estado, p.foto);

            // Sobrescribe el archivo con todas las líneas actualizadas
            FILE *f = fopen("data/prendas.txt", "w");
            for (int j = 0; j < cantidad; j++) {
                guardarLinea("data/prendas.txt", lineas[j]);
            }
            if (f) fclose(f);

            printf("Prenda modificada con éxito.\n");
            return;
        }
    }
    if (!encontrada) {
        printf("Prenda no encontrada o inactiva.\n");
    }
}


void buscarPrendaPorCodigo() {
    limpiarConsola();
    int codigo, cantidad, encontrada = 0;
    char lineas[100][BUFFER_LINEA];

    printf("Ingrese el código de la prenda a buscar: ");
    scanf("%d", &codigo);
    limpiarBuffer();

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.codigo == codigo) {
            printf("Código: %d\nNombre: %s\nColor: %s\nTalle: %s\nCosto: %.2f\nPrecio: %.2f\nStock: %d\nFoto: %s\nEstado: %s\n",
                   p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.foto, p.estado ? "Activo" : "Inactivo");
            encontrada = 1;
            break;
        }
    }
    if (!encontrada) {
        printf("Prenda no encontrada.\n");
    }
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}

void filtrarPrendas() {
    limpiarConsola();
    char color[30], talle[10];
    char lineas[100][BUFFER_LINEA];
    int cantidad;

    printf("Ingrese color (o '-' para ignorar): ");
    scanf("%29s", color);
    limpiarBuffer();
    printf("Ingrese talle (o '-' para ignorar): ");
    scanf("%9s", talle);
    limpiarBuffer();

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    printf("\nResultados:\n");
    printf("%-6s | %-25s | %-15s | %-10s | %-8s | %-8s | %-5s | %-15s\n",
           "Codigo", "Nombre", "Color", "Talle", "Costo", "Precio", "Stock", "Foto");
    printf("------ | ------------------------- | --------------- | ---------- | -------- | -------- | ----- | ---------------\n");

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.estado == 1 &&
            (strcmp(color, "-") == 0 || strcmp(p.color, color) == 0) &&
            (strcmp(talle, "-") == 0 || strcmp(p.talle, talle) == 0)) {
            printf("%-6d | %-25s | %-15s | %-10s | %-8.2f | %-8.2f | %-5d | %-15s\n",
                   p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.foto);
        }
    }
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}

void consultarStock() {
    limpiarConsola();
    int codigo, cantidad, encontrada = 0;
    char lineas[100][BUFFER_LINEA];

    printf("Ingrese el código de la prenda: ");
    scanf("%d", &codigo);
    limpiarBuffer();

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.codigo == codigo && p.estado == 1) {
            printf("Stock disponible de %s: %d\n", p.nombre, p.stock);
            encontrada = 1;
            break;
        }
    }
    if (!encontrada) {
        printf("Prenda no encontrada o inactiva.\n");
    }
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}

void reporteInventario() {
    limpiarConsola();
    char lineas[100][BUFFER_LINEA];
    int cantidad = leerLineas("data/prendas.txt", lineas, 100);
    int totalPrendas = 0;
    float costoTotal = 0;

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.estado == 1) {
            totalPrendas += p.stock;
            costoTotal += p.costo * p.stock;
        }
    }

    printf("\n--- Reporte de Inventario ---\n");
    printf("Total de prendas activas en stock: %d\n", totalPrendas);
    printf("Costo total de mercadería: $%.2f\n", costoTotal);
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}