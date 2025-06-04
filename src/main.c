#include <stdio.h>
#include "menu.h"   
#include "utils.h"
#include "auth.h"

int main()
{

    inicializarArchivos();

    if (login())
    {
        menuPrincipal();
    }
    else
    {
        printf("Error de autenticación.");
    }

    return 0;
}