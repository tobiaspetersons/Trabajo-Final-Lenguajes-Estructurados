#include <stdio.h>
#include "menu.h"   
#include "utils.h"
#include "auth.h"

int main()
{

    inicializarArchivos();

    if (login())
    {
        limpiarConsola();
        menuPrincipal();
    }
    else
    {
        printf("Error de autenticación.");
    }

    return 0;
}