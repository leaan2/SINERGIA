#ifndef PIEZA_H
#define PIEZA_H

#include <stdint.h>
#define ALTO_T 20
#define ANCHO_T 10
#define TAM 4
#define SIN_MEM 1
#define TAM_BLOQUE 6


typedef struct {

    uint8_t forma[TAM][TAM];
    uint8_t color;

} Pieza;


int** crearMatriz(int filas, int columnas);
void destruirMatriz(int** m, int filas);
void inicializarMatriz(int** m, int filas, int columnas);
void mostrarMatriz(int** m, int filas, int columnas);
void dibujarBloque(int x, int y, uint8_t color);
void dibujarPieza(Pieza p, int posX, int posY);

void colocarPieza( int** tablero, Pieza p, int fila, int columna);
void dibujarTablero(int** tablero, int offsetX, int offsetY);
Pieza rotarPieza (Pieza pieza);
int alturaPieza(Pieza p);
int anchoPieza(Pieza p);

int puedeMoverDerecha(int** tablero, Pieza p, int fila, int columna);
int puedeMoverIzquierda(int** tablero, Pieza p, int fila, int columna);

void juego();


extern Pieza piezaT;
extern Pieza piezaI;
extern Pieza piezaO;
extern Pieza piezaJ;
extern Pieza piezaS;
extern Pieza piezaL;
extern Pieza piezaZ;

#endif
