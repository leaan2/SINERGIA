// Definiciones y funciones de los tetrominos://
// estructuras, rotaciones y sistema de bolsa.//

#ifndef PIEZA_H_INCLUDED
#define PIEZA_H_INCLUDED

#include <stdint.h>

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480
#define ESCALA_VENTANA 3

#define ALTO_T 20
#define FILAS_OCULTAS_T 4
#define ALTO_MATRIZ_T (ALTO_T + FILAS_OCULTAS_T)
#define ANCHO_T 10
#define TAM 4
#define TAM_BLOQUE 10
#define CANT_TETROMINOS 7

typedef struct
{
    uint8_t forma[TAM][TAM];
    uint8_t color;
} Pieza;

typedef struct
{
    Pieza piezas[CANT_TETROMINOS];
    int posicion;
} BolsaPiezas;

extern Pieza piezaT;
extern Pieza piezaI;
extern Pieza piezaO;
extern Pieza piezaJ;
extern Pieza piezaS;
extern Pieza piezaL;
extern Pieza piezaZ;

//Funciones de las piezas

void mezclarBolsa(BolsaPiezas *bolsa);
Pieza obtenerPiezaBolsa(BolsaPiezas *bolsa);
Pieza rotarPiezaIzquierda(Pieza pieza);
Pieza rotarPiezaDerecha(Pieza pieza);

#endif // PIEZA_H_INCLUDED
