#ifndef PRESENTACION_H_INCLUDED
#define PRESENTACION_H_INCLUDED
#include "graficos.h"
#include "letras.h"
#include "GBT/gbt.h"
#define MAX_NOMBRE 7
// Estructura para transportar las opciones elegidas
typedef struct {
    int paleta;           // 0: Clasica, 1: Neon, 2: GameBoy, etc.
    int resolucion;       // 0: 320x240, 1: 640x480, etc. (O los bloques del tablero si es resolucion logica del Tetris)
    int velocidad_inicial;// 1: Facil, 2: Normal, 3: Dificil (afecta el delay de caida)
} ConfigurarJuego;
void dibujar_letra(char c, int x, int y, int color);
void dibujarPantalla (int ancho_p, int alto_p);
int Presentacion(char nombre[], int ancho_pantalla, int alto_pantalla);



#endif // PRESENTACION_H_INCLUDED
