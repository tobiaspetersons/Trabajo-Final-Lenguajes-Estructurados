#ifndef PRENDAS_H
#include <stdio.h>

typedef struct
{
    int codigo;
    char nombre[50];
    char color[30];
    char talle[10];
    float precio;
    int stock;
    int estado; // 1: activo, 0: inactivo
} Prenda;

void agregarPrenda();
void inhabilitarPrenda();
void habilitarPrenda();
void modificarStockPrenda();


#endif