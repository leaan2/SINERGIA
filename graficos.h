#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED
#include "GBT/gbt.h"
#define CANT_COLORES 16
#define MAX_NOMBRE 7

extern tGBT_ColorRGB paletaCGA[CANT_COLORES];
typedef enum
{
    estado_menu,
    estado_juego
}EstadoJuego;


void Dibujar_rect(int x, int y, int w, int h, int color);
void dibujarBorde(int x, int y, int w, int h, int color);
void dibujarFondo();
void dibujar_matriz(int x, int y, int filas, int cols, int matriz[filas][cols], int color);
#endif // GRAFICOS_H_INCLUDED
