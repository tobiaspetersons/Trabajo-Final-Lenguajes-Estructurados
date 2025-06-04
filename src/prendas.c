#include <stdio.h>
#include <string.h>
#include "prendas.h"
#include "utils.h"

void listarPrendas(int estado) {
    char lineas[100][300];
    int cantidad = leerLineas("data/prendas.txt", lineas, 100);

    if (estado == 1) {
        printf("\n--- Prendas activas ---\n");
    } else {
        printf("\n--- Prendas inactivas ---\n");
    }
    printf("Codigo | Nombre | Color | Talle | Costo | Precio | Stock | Foto\n");
    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.estado == estado) {
            printf("%d | %s | %s | %s | %.2f | %.2f | %d | %s\n", p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.foto);
        }
    }
}

void agregarPrenda() {
    char opcion;
    do
    {
        Prenda p;
        char linea[300];
        char lineas[100][300];

        int cantidad = leerLineas("data/prendas.txt", lineas, 100);

        // Asignar código autoincremental (máximo código + 1)
        int maxCodigo = 0;
        for (int i = 0; i < cantidad; i++) {
            int cod;
            sscanf(lineas[i], "%d,%*[^,],%*[^,],%*[^,],%*f,%*f,%*d,%*d,%*[^,]", &cod);
            if (cod > maxCodigo) maxCodigo = cod;
        }
        p.codigo = maxCodigo + 1;

        printf("Nombre: ");
        scanf("%49s", p.nombre);
        limpiarBuffer();
        printf("Color: ");
        scanf("%29s", p.color);
        limpiarBuffer();
        printf("Talle: ");
        scanf("%9s", p.talle);
        limpiarBuffer();
        printf("Costo: ");
        scanf("%f", &p.costo);
        limpiarBuffer();
        printf("Precio: ");
        scanf("%f", &p.precio);
        limpiarBuffer();
        printf("Stock: ");
        scanf("%d", &p.stock);
        limpiarBuffer();
        printf("Nombre de la foto (ej: img_8478): ");
        limpiarBuffer();
        scanf("%29s", p.foto);

        if (p.costo < 0 || p.precio < 0 || p.stock < 0) {
            printf("Costo, precio y stock deben ser valores positivos.\n");
            return;
        }

        p.estado = 1;

        sprintf(linea, "%d,%s,%s,%s,%.2f,%.2f,%d,%d,%s", p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.estado, p.foto);
        guardarLinea("data/prendas.txt", linea);
        printf("Prenda agregada con éxito. Código asignado: %d\n", p.codigo);

        printf("¿Desea agregar otra prenda? (s/n): ");
        scanf(" %c", &opcion); 
    } while (opcion == 's' || opcion == 'S');
}

void bajaPrenda() {
    int codigo, cantidad, encontrada = 0;
    char lineas[100][300];
    char tipoBaja;

    listarPrendas(1); // Muestra prendas activas

    printf("Ingrese el código de la prenda a dar de baja: ");
    scanf("%d", &codigo);

    printf("¿Desea inhabilitar la prenda (baja lógica) o eliminarla definitivamente (baja física)?\n");
    printf("Ingrese 'i' para inhabilitar o 'f' para eliminar: ");
    scanf(" %c", &tipoBaja);

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    FILE *f = fopen("data/prendas.txt", "w");
    if (!f) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);

        if (p.codigo == codigo && p.estado == 1) {
            encontrada = 1;
            if (tipoBaja == 'i' || tipoBaja == 'I') {
                // Baja lógica: solo cambia el estado
                sprintf(lineas[i], "%d,%s,%s,%s,%.2f,%.2f,%d,0,%s", p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.foto);
                fprintf(f, "%s\n", lineas[i]);
                printf("Prenda inhabilitada (baja lógica) con éxito.\n");
            } else if (tipoBaja == 'f' || tipoBaja == 'F') {
                // Baja física: no la escribe, la elimina
                printf("Prenda eliminada definitivamente (baja física).\n");
            } else {
                // Opción inválida, vuelve a escribir la línea original
                fprintf(f, "%s\n", lineas[i]);
                printf("Opción inválida. No se realizó ninguna baja.\n");
            }
        } else {
            // Escribe todas las demás prendas
            fprintf(f, "%s\n", lineas[i]);
        }
    }
    fclose(f);

    if (!encontrada) {
        printf("Prenda no encontrada o ya inactiva.\n");
    }
}

void habilitarPrenda() {
    int codigo, cantidad, encontrado = 0;
    char lineas[100][300];

    listarPrendas(0);

    printf("Ingrese el código de la prenda a habilitar: ");
    scanf("%d", &codigo);

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

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
    } else {
        printf("Prenda no encontrada o ya activa.\n");
    }
}

void modificarPrenda() {
    int codigo, cantidad, encontrado = 0;
    char lineas[100][300];
    int opcion;

    listarPrendas(1);

    printf("Ingrese el código de la prenda a modificar: ");
    scanf("%d", &codigo);

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.codigo == codigo && p.estado == 1) {
            printf("¿Qué desea modificar?\n");
            printf("1. Stock\n");
            printf("2. Costo\n");
            printf("3. Precio\n");
            printf("4. Foto\n");
            printf("Ingrese opción: ");
            scanf("%d", &opcion);

            if (opcion == 1) {
                int nuevoStock;
                printf("Stock actual: %d\n", p.stock);
                printf("Ingrese el nuevo stock: ");
                scanf("%d", &nuevoStock);
                if (nuevoStock < 0) {
                    printf("El stock debe ser un valor positivo.\n");
                    return;
                }
                p.stock = nuevoStock;
            } else if (opcion == 2) {
                float nuevoCosto;
                printf("Costo actual: %.2f\n", p.costo);
                printf("Ingrese el nuevo costo: ");
                scanf("%f", &nuevoCosto);
                if (nuevoCosto < 0) {
                    printf("El costo debe ser un valor positivo.\n");
                    return;
                }
                p.costo = nuevoCosto;
            } else if (opcion == 3) {
                float nuevoPrecio;
                printf("Precio actual: %.2f\n", p.precio);
                printf("Ingrese el nuevo precio: ");
                scanf("%f", &nuevoPrecio);
                if (nuevoPrecio < 0) {
                    printf("El precio debe ser un valor positivo.\n");
                    return;
                }
                p.precio = nuevoPrecio;
            } else if (opcion == 4) {
                printf("Foto actual: %s\n", p.foto);
                printf("Ingrese el nuevo nombre de la foto: ");
                scanf("%29s", p.foto);
            } else {
                printf("Opción inválida.\n");
                return;
            }

            sprintf(lineas[i], "%d,%s,%s,%s,%.2f,%.2f,%d,%d,%s", p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.estado, p.foto);
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
        printf("Prenda modificada con éxito.\n");
    } else {
        printf("Prenda no encontrada o ya inactiva.\n");
    }
}

void buscarPrendaPorCodigo() {
    int codigo, cantidad, encontrada = 0;
    char lineas[100][300];

    printf("Ingrese el código de la prenda a buscar: ");
    scanf("%d", &codigo);

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
}

void filtrarPrendas() {
    char color[30], talle[10];
    char lineas[100][300];
    int cantidad;

    printf("Ingrese color (o '-' para ignorar): ");
    scanf("%29s", color);
    printf("Ingrese talle (o '-' para ignorar): ");
    scanf("%9s", talle);

    cantidad = leerLineas("data/prendas.txt", lineas, 100);

    printf("Resultados:\n");
    printf("Codigo | Nombre | Color | Talle | Costo | Precio | Stock | Foto\n");
    for (int i = 0; i < cantidad; i++) {
        Prenda p;
        sscanf(lineas[i], "%d,%49[^,],%29[^,],%9[^,],%f,%f,%d,%d,%29s",
               &p.codigo, p.nombre, p.color, p.talle, &p.costo, &p.precio, &p.stock, &p.estado, p.foto);
        if (p.estado == 1 &&
            (strcmp(color, "-") == 0 || strcmp(p.color, color) == 0) &&
            (strcmp(talle, "-") == 0 || strcmp(p.talle, talle) == 0)) {
            printf("%d | %s | %s | %s | %.2f | %.2f | %d | %s\n", p.codigo, p.nombre, p.color, p.talle, p.costo, p.precio, p.stock, p.foto);
        }
    }
}

void consultarStock() {
    int codigo, cantidad, encontrada = 0;
    char lineas[100][300];

    printf("Ingrese el código de la prenda: ");
    scanf("%d", &codigo);

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
}

void reporteInventario() {
    char lineas[100][300];
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
}