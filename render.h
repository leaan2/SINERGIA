//Primitivas de los dibujos//

#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "pieza.h"

void dibujarBloque(int x, int y, uint8_t color_original, int paleta_tipo);
void dibujarPieza(Pieza p, int posX, int posY, int paleta_tipo);
void dibujarTablero(int** tablero, int offsetX, int offsetY, int paleta_tipo);
void dibujarInterfaz(int** tablero, Pieza piezaActual, int fila, int columna, char nombre[], int longitud, int puntaje, int paleta_tipo, int ancho_ventana, int alto_ventana);

void dibujar_letra(char c, int x, int y, int color);
void dibujar_texto(const char *texto, int x, int y, int color);

#endif // RENDER_H_INCLUDED
