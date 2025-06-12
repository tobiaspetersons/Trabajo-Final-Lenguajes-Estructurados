#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H

typedef struct {
    int codigoPrenda;
    const char *tipo;
    int cantidad;
    const char *usuario;
    char fecha[20];
    const char *detalle;
} Movimiento;

void registrarMovimiento(Movimiento mov);
void listarMovimientos();


#endif