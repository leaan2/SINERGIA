#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED
#include "GBT/gbt.h"
#define CANT_COLORES 16
#include "pieza.h"
#include "presentacion.h"

extern tGBT_ColorRGB paletaCGA[CANT_COLORES];
typedef enum
{
    estado_menu,
    estado_juego,
    estado_pausa,
    estado_gameover
}EstadoJuego;
typedef struct {
    int paleta_tipo;       // 0: Cl�sica, 1: GameBoy, 2: Ne�n
    int resolucion_tipo;   // 0: 128x128, 1: 256x256
    int escala_ventana;
    double velocidad_init; // 1.0 (F�cil), 0.5 (Normal), 0.2 (Dif�cil)
} Configuracion;

void Dibujar_rect(int x, int y, int w, int h, int color);
void dibujarBorde(int x, int y, int w, int h, int color);
void dibujarFondo();
void dibujar_matriz(int x, int y, int filas, int cols, int matriz[filas][cols], int color);
void dibujar_linea(int x, int y, int h ,int color);
void dibujarInterfaz(int** tablero, Pieza pieza, int fila, int columna, char Nombre[], int longitud, int puntaje, int paleta_tipo, int ancho_ventana, int alto_ventana);
void guardar_configuracion(Configuracion *config);
void cargar_configuracion(Configuracion *config);
#endif // GRAFICOS_H_INCLUDED
