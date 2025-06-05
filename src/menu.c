#include <stdio.h>
#include "menu.h"
#include "usuarios.h"
#include "prendas.h"
#include "auth.h"
#include "utils.h"

void menuPrincipal() {
    int opcion;
    do {
        limpiarConsola();
        printf("\n--- Menú Principal ---\n");
        if (usuarioActualRol == 1) {
            printf("1. Gestión de usuarios\n");
            printf("2. Gestión de prendas\n");
            printf("3. Consultas y Reportes\n");
            printf("4. Salir\n");
        } else {
            printf("1. Gestión de prendas\n");
            printf("2. Consultas y Reportes\n");
            printf("3. Salir\n");
        }
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        if (usuarioActualRol == 1) {
            switch (opcion) {
                case 1: menuUsuarios(); break;
                case 2: menuPrendas(); break;
                case 3: menuConsultas(); break;
                case 4: printf("Saliendo...\n"); break;
                default: printf("Opción inválida.\n");
            }
        } else {
            switch (opcion) {
                case 1: menuPrendas(); break;
                case 2: menuConsultas(); break;
                case 3: printf("Saliendo...\n"); break;
                default: printf("Opción inválida.\n");
            }
        }
    } while ((usuarioActualRol == 1 && opcion != 4) || (usuarioActualRol == 0 && opcion != 3));
}

void menuUsuarios() {
    int opcion;
    do {
        limpiarConsola();
        printf("\n--- Gestión de Usuarios ---\n");
        printf("1. Registrar nuevo usuario\n");
        printf("2. Inhabilitar usuario\n");
        printf("3. Listar usuarios activos\n");
        printf("4. Listar usuarios inactivos\n");
        printf("5. Volver\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1: registrarUsuario(); break;
            case 2: inhabilitarUsuario(); break;
            case 3: listarUsuarios(1); break; // 1 = activos
            case 4: listarUsuarios(0); break; // 0 = inactivos
            case 5: printf("Volviendo al menú principal...\n"); break;
            default: printf("Opción inválida.\n");
        }
    } while (opcion != 5);
}

void menuPrendas()
{
    int opcion;
    do {
        limpiarConsola();
        printf("\n--- Gestión de Prendas ---\n");
        printf("1. Agregar prenda\n");
        printf("2. Dar de baja o eliminar prenda\n");
        printf("3. Habilitar prenda\n");
        printf("4. Modificar prenda\n");
        printf("5. Volver\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1: agregarPrenda(); break;
            case 2: bajaPrenda(); break;
            case 3: habilitarPrenda(); break;
            case 4: modificarPrenda(); break;
            case 5: printf("Volviendo al menú principal...\n"); break;
            default: printf("Opción inválida.\n");
        }
    } while (opcion != 5);
}

void menuConsultas() {
    int opcion;
    do {
        limpiarConsola();
        printf("\n--- Consultas y Reportes ---\n");
        printf("1. Listar prendas activas\n");
        printf("2. Listar prendas inactivas\n");
        printf("3. Consultar stock\n");
        printf("4. Buscar prenda por código\n");
        printf("5. Filtrar prendas\n");
        printf("6. Consultar total de prendas y costos\n");
        printf("7. Volver\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1: listarPrendas(1); break; // 1 = activas
            case 2: listarPrendas(0); break; // 0 = inactivas
            case 3: consultarStock(); break;
            case 4: buscarPrendaPorCodigo(); break;
            case 5: filtrarPrendas(); break;
            case 6: reporteInventario(); break;
            case 7: printf("Volviendo...\n"); break;
            default: printf("Opción inválida.\n");
        }
    } while (opcion != 7);
}
