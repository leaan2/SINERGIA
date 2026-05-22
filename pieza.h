#ifndef PIEZA_H_INCLUDED
#define PIEZA_H_INCLUDED

#include <stdint.h>
#include <time.h>

#define ANCHO_VENTANA 320
#define ALTO_VENTANA 200
#define ESCALA_VENTANA 4

#define ALTO_T 20
#define ANCHO_T 10
#define TAM 4
#define SIN_MEM 1
#define TAM_BLOQUE 10

typedef struct
{
    uint8_t forma[TAM][TAM];
    uint8_t color;
} Pieza;



int** crearMatriz(int filas, int columnas);
void destruirMatriz(int** m, int filas);
void inicializarMatriz(int** m, int filas, int columnas);
void mostrarMatriz(int** m, int filas, int columnas);

void dibujarBloque(int x, int y, uint8_t color_original, int paleta_tipo);
void dibujarPieza(Pieza p, int posX, int posY, int paleta_tipo);
void dibujarTablero(int** tablero, int offsetX, int offsetY, int paleta_tipo);
int colocarPieza(int** tablero, Pieza p, int fila, int columna, int cantpiezas);


Pieza rotarPieza(Pieza pieza);
int alturaPieza(Pieza p);

int puedeColocarPieza(int** tablero, Pieza p, int fila, int columna);
int moverPieza(int** tablero, Pieza p, int *fila, int *columna, int desplazamientoFilas, int desplazamientoColumnas);

int filaCompleta(int** tablero, int fila);
void eliminarFila(int** tablero, int fila);
int eliminarFilasCompletas(int** tablero);
int sistemaPuntuacion(int puntaje, int filasborradas, double tiempocaida);

void juego();

extern Pieza piezaT;
extern Pieza piezaI;
extern Pieza piezaO;
extern Pieza piezaJ;
extern Pieza piezaS;
extern Pieza piezaL;
extern Pieza piezaZ;

#endif // PIEZA_H_INCLUDED
