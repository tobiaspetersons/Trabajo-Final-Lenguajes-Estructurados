#include <stdio.h>
#include <menu.h>

int main()
{
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