#ifndef PRENDAS_H
#include <stdio.h>

typedef struct
{
    int id; /*codigo imagen*/
    char nombre[100];
    char color[100];
    int talle;
    char categoria[50];
    float precio;
    int stock;
    int estado; /* 0: inactivo, 1:activo */
}Prenda;


#endif