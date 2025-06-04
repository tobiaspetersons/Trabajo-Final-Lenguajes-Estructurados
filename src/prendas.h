#ifndef PRENDAS_H
#define PRENDAS_H
#include <stdio.h>

typedef struct
{
    int codigo;              
    char nombre[50];
    char color[30];
    char talle[10];
    float costo;
    float precio;
    int stock;
    int estado;              // 1: activo, 0: inactivo
    char foto[30];           // campo para el nombre de la foto (ej: img_8478)
} Prenda;

void agregarPrenda();
void bajaPrenda();
void habilitarPrenda();
void modificarPrenda();
void listarPrendas(int estado);
void buscarPrendaPorCodigo();
void filtrarPrendas();
void consultarStock();
void reporteInventario();

#endif