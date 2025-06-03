#include <stdio.h>
#include "usuarios.h"
#include "utils.h"

void registrarUsuario(const char* user, const char* pass) {
    char linea[120];
    sprintf(linea, "%s,%s,1", user, pass); // 1 = activo
    guardarLinea("data/usuarios.txt", linea);
}