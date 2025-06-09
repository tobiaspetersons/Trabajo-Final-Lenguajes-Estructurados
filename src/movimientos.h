#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H

typedef struct {
    int codigoPrenda;
    char tipo[20];
    int cantidad;
    char usuario[50];
    char fecha[20];
    char detalle[100];
} Movimiento;

typedef struct {
    int codigoPrenda;
    const char *tipo;
    int cantidad;
    const char *usuario;
    const char *detalle;
} DatosMovimiento;

void registrarMovimiento(Movimiento mov);
void agregarMovimiento(DatosMovimiento datos);
void listarMovimientos();


#endif