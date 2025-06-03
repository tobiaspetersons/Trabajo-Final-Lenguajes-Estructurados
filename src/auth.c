#include <stdio.h>
#include "auth.h"
#include "utils.h"
#include "usuarios.h"


int login()
{
    char user[50], pass[50];
    char lineas[100][256]; // arreglo de 100 líneas, y cada línea puede tener hasta 255 caracteres
    int cantidad;
    int encontrado = 0;

    printf("Usuario: ");
    scanf("%49s", user);
    printf("Contraseña: ");
    scanf("%49s", pass);
    // lee todas las líneas del archivo de usuarios
    cantidad = leerLineas("data/usuarios.txt", lineas, 100);

    for (int i = 0; i < cantidad; i++) {
        Usuario u;
        // separa la línea en user, pass y estado
        sscanf(lineas[i], "%49[^,],%49[^,],%d", u.user, u.pass, &u.estado);
        if (u.estado == 1 && strcmp(u.user, user) == 0 && strcmp(u.pass, pass) == 0) {
            printf("Login exitoso.\n");
            return 1; // corta aca
        }
    }
    printf("Usuario o contraseña incorrectos.\n");
    return 0;
}