#include <stdio.h>
#include "menu.h"
#include "usuarios.h"
#include "prendas.h"


void menuPrincipal() {
    int opcion;
    do {
        printf("\n--- Menú Principal ---\n");
        printf("1. Gestión de usuarios\n");
        printf("2. Gestión de prendas\n");
        printf("3. Consultar stock\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                menuUsuarios();
                break;
            case 2:
                menuPrendas();
                break;
            case 3:
                consultarStock();
                break;
            case 4:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 4);
}

void menuUsuarios() {
    int opcion;
    do {
        printf("\n--- Gestión de Usuarios ---\n");
        printf("1. Registrar nuevo usuario\n");
        printf("2. Inhabilitar usuario.");
        printf("3. Volver\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                registrarUsuario();
                break;
            }
            case 2:
                printf("Funcion en desarrollo...\n");
                break;
            case 3:
                printf("Volviendo al menú principal...\n");
                break;

            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 3);
}

void menuPrendas()
{
    int opcion;
    do {
        printf("\n--- Gestión de Prendas ---\n");
        printf("1. Agregar prenda\n");
        printf("2. Dar de baja prenda\n");
        printf("3. Habilitar prenda\n");
        printf("4. Modificar stock de prenda\n");
        printf("5. Listar prendas activas\n");
        printf("6. Listar prendas inactivas\n");
        printf("7. Volver\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarPrenda();
                break;
            case 2:
                inhabilitarPrenda();
                break;
            case 3:
                habilitarPrenda();
                break;
            case 4:
                ModificarStockPrenda();
                break;
            case 5:
                listarPrendas(1); // 1 = activas
                break;
            case 6:
                listarPrendas(0); // 0 = inactivas
                break;
            case 7:
                printf("Volviendo al menú principal...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 7);
}