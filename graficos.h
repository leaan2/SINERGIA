//Primitivas graficas//

#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED

#include "GBT/gbt.h"

#define CANT_COLORES 16

extern tGBT_ColorRGB paletaCGA[CANT_COLORES];

void configurar_limites_dibujo(int ancho, int alto);
void Dibujar_rect(int x, int y, int w, int h, int color);
void dibujarBorde(int x, int y, int w, int h, int color);
void dibujar_matriz(int x, int y, int filas, int cols, int matriz[filas][cols], int color);
void dibujar_linea(int x, int y, int h, int color);

#endif // GRAFICOS_H_INCLUDED
