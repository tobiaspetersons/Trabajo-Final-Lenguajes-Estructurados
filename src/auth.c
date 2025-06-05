#include <stdio.h>
#include <string.h> 
#include "auth.h"
#include "utils.h"
#include "usuarios.h"

int usuarioActualRol = 0;
char usuarioActual[50] = "";

int login() {
    limpiarConsola();
    char user[50], pass[50];
    char lineas[100][BUFFER_LINEA];
    int cantidad;
    int intentos = 0;

    while (intentos < 3) {
        printf("Usuario: ");
        scanf("%49s", user);
        limpiarBuffer();
        printf("Contraseña: ");
        scanf("%49s", pass);
        limpiarBuffer();

        cantidad = leerLineas("data/usuarios.txt", lineas, 100);

        for (int i = 0; i < cantidad; i++) {
            Usuario u;
            sscanf(lineas[i], "%49[^,],%49[^,],%d,%d", u.user, u.pass, &u.estado, &u.rol);
            if (u.estado == 1 && strcmp(u.user, user) == 0 && strcmp(u.pass, pass) == 0) {
                usuarioActualRol = u.rol;
                strcpy(usuarioActual, user);
                printf("Login exitoso.\n");
                printf("\nPresione ENTER para continuar...");
                getchar();
                return 1;
            }
        }
        printf("Usuario o contraseña incorrectos.\n");
        intentos++;
    }
    printf("Demasiados intentos fallidos. Saliendo...\n");
    return 0;
}

// valida que la contraseña tenga al menos 8 caracteres, una mayúscula, una minúscula y un número
int validarPassword(const char *pass) {
    int tieneMayus = 0, tieneMinus = 0, tieneNum = 0, len = strlen(pass);
    if (len < 8) return 0;
    for (int i = 0; i < len; i++) {
        if (pass[i] >= 'A' && pass[i] <= 'Z') tieneMayus = 1;
        else if (pass[i] >= 'a' && pass[i] <= 'z') tieneMinus = 1;
        else if (pass[i] >= '0' && pass[i] <= '9') tieneNum = 1;
    }
    return tieneMayus && tieneMinus && tieneNum;
}