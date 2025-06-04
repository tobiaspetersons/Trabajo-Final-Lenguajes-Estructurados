#ifndef USUARIOS_H
#include <stdio.h>

typedef struct
{
    char user[50];
    char pass[50];
    int estado; /* 0: inactivo, 1: activo */
}Usuario;

void registrarUsuario();
#endif
