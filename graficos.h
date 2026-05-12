#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED
#include "GBT/gbt.h"
#define CANT_COLORES 16
<<<<<<< HEAD
#include "pieza.h"
#include "presentacion.h"
=======
#define MAX_NOMBRE 7
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54

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
void dibujar_linea(int x, int y, int h ,int color);
void dibujarInterfaz(int** tablero, Pieza pieza, int fila, int columna, char Nombre[], int longitud, int puntaje);
#endif // GRAFICOS_H_INCLUDED
