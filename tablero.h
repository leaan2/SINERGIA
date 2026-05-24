//Primitivas de matriz//

#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "pieza.h"

int** crearMatriz(int filas, int columnas);
void destruirMatriz(int** m, int filas);
void inicializarMatriz(int** m, int filas, int columnas);
void mostrarMatriz(int** m, int filas, int columnas);

int colocarPieza(int** tablero, Pieza p, int fila, int columna, int cantpiezas);
int puedeColocarPieza(int** tablero, Pieza p, int fila, int columna);
int moverPieza(int** tablero, Pieza p, int *fila, int *columna, int desplazamientoFilas, int desplazamientoColumnas);

int filaCompleta(int** tablero, int fila);
void eliminarFila(int** tablero, int fila);
int eliminarFilasCompletas(int** tablero);

#endif // TABLERO_H_INCLUDED
