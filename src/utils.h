#ifndef UTILS_H
#define UTILS_H

#define BUFFER_LINEA 256

int guardarLinea(const char *ruta, const char *linea);
int leerLineas(const char *ruta, char lineas[][BUFFER_LINEA], int maxLineas);
void inicializarArchivos();
void limpiarBuffer();
void limpiarConsola();


#endif