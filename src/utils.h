#ifndef UTILS_H
#define UTILS_H

int guardarLinea(const char *ruta, const char *linea);
int leerLineas(const char *ruta, char lineas[][256], int maxLineas);
void inicializarArchivos();
void limpiarBuffer();


#endif