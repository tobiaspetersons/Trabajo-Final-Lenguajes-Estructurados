#include <stdio.h>
#include "usuarios.h"
#include "utils.h"

void registrarUsuario()
{
    char user[50], pass[50], linea[120];
    printf("Ingrese nombre de usuario: ");
    scanf("%49s", user);
    printf("Ingrese contraseña: ");
    scanf("%49s", pass);
    sprintf(linea, "%s,%s,1", user, pass); // 1 = activo
    guardarLinea("data/usuarios.txt", linea);
    printf("Usuario registrado con éxito.\n");
}