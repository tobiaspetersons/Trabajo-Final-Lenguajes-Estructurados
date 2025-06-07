#include <stdio.h>
#include <string.h> 
#include "usuarios.h"
#include "utils.h"
#include "auth.h"

extern char usuarioActual[50];

void registrarUsuario() {
    limpiarConsola();
    char user[50], pass[50], linea[120];
    char lineas[100][BUFFER_LINEA];
    int cantidad, existe = 0, rol = 0;

    printf("Ingrese nombre de usuario: ");
    scanf("%49s", user);
    limpiarBuffer();

    cantidad = leerLineas("data/usuarios.txt", lineas, 100);
    for (int i = 0; i < cantidad; i++) {
        char u[50], p[50];
        int estado, r;
        sscanf(lineas[i], "%49[^,],%49[^,],%d,%d", u, p, &estado, &r);
        if (strcmp(u, user) == 0 && estado == 1) {
            existe = 1;
            break;
        }
    }
    if (existe) {
        printf("El usuario ya existe y está activo.\n");
        return;
    }

    do {
        printf("Ingrese contraseña (mínimo 8 caracteres, una mayúscula, una minúscula y un número): ");
        scanf("%49s", pass);
        if (!validarPassword(pass)) {
            printf("Contraseña insegura. Intente de nuevo.\n");
        }
    } while (!validarPassword(pass));

    do {
        printf("¿El usuario será administrador? (1=Sí, 0=No): ");
        if (scanf("%d", &rol) != 1) { /*aca el scanf si lee un entero correctamente devuelve 1*/
            limpiarBuffer(); 
            rol = -1;
        }
        if (rol != 0 && rol != 1) {
            printf("Opción inválida. Ingrese 1 para Sí o 0 para No.\n");
        }
    } while (rol != 0 && rol != 1);

    sprintf(linea, "%s,%s,1,%d", user, pass, rol);
    guardarLinea("data/usuarios.txt", linea);
    printf("Usuario registrado con éxito.\n");
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}

void inhabilitarUsuario() {
    limpiarConsola();
    char nombre[50];
    char lineas[100][BUFFER_LINEA];
    int cantidad, encontrado = 0;

    printf("Ingrese el nombre de usuario a inhabilitar: ");
    scanf("%49s", nombre);
    limpiarBuffer();

    if (strcmp(nombre, usuarioActual) == 0) {
    printf("No puedes inhabilitar tu propio usuario.\n");
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
    return;
}
    cantidad = leerLineas("data/usuarios.txt", lineas, 100);

    for (int i = 0; i < cantidad; i++) {
        char user[50], pass[50];
        int estado, rol;
        sscanf(lineas[i], "%49[^,],%49[^,],%d,%d", user, pass, &estado, &rol);
        if (strcmp(user, nombre) == 0 && estado == 1) {
            sprintf(lineas[i], "%s,%s,0,%d", user, pass, rol);
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        FILE *f = fopen("data/usuarios.txt", "w");
        for (int i = 0; i < cantidad; i++) {
            fprintf(f, "%s\n", lineas[i]);
        }
        fclose(f);
        printf("Usuario inhabilitado con éxito.\n");
    } else {
        printf("Usuario no encontrado o ya inhabilitado.\n");
    }
}

void listarUsuarios(int estado) {
    limpiarConsola();
    char lineas[100][BUFFER_LINEA];
    int cantidad = leerLineas("data/usuarios.txt", lineas, 100);

    if (estado == 1) {
        printf("\n--- Usuarios activos ---\n");
    } else {
        printf("\n--- Usuarios inactivos ---\n");
    }

    printf("%-15s | %-15s | %-8s\n", "Usuario", "Contraseña", "Rol");
    printf("--------------- | --------------- | --------\n");

    for (int i = 0; i < cantidad; i++) {
        char user[50], pass[50];
        int est, rol;
        sscanf(lineas[i], "%49[^,],%49[^,],%d,%d", user, pass, &est, &rol);
        if (est == estado) {
            char passOculta[50];
            int len = strlen(pass);
            for (int j = 0; j < len; j++) passOculta[j] = '*';
            passOculta[len] = '\0';
            printf("%-15s | %-15s | %-8s\n", user, passOculta, rol == 1 ? "ADMIN" : "USUARIO");
        }
    }
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}