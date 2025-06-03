#include <stdio.h>
#include "menu.h"

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