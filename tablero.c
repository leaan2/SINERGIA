//Matriz//
// creacion, destruccion, inicializacion,etc//

#include "tablero.h"
#include <stdlib.h>

int** crearMatriz(int filas, int columnas)
{
    int** m = malloc(filas * sizeof(int*));
    if(!m)
        return NULL;

    for(int i = 0; i < filas; i++)
    {
        m[i] = malloc(columnas * sizeof(int));
        if(!m[i])
        {
            destruirMatriz(m, i);
            return NULL;
        }
    }

    return m;
}

void destruirMatriz(int** m, int filas)
{
    if(!m)
        return;

    for(int i = 0; i < filas; i++)
        free(m[i]);

    free(m);
}

void inicializarMatriz(int** m, int filas, int columnas)
{
    for(int i = 0; i < filas; i++)
        for(int j = 0; j < columnas; j++)
            m[i][j] = 0;
}

void colocarPieza(int** tablero, Pieza p, int fila, int columna)
{
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
                tablero[fila + i][columna + j] = p.color;
        }
    }
}

int puedeColocarPieza(int** tablero, Pieza p, int fila, int columna)
{
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 0)
                continue;

            int y = fila + i;
            int x = columna + j;

            if(y < 0 || y >= ALTO_MATRIZ_T)
                return 0;

            if(x < 0 || x >= ANCHO_T)
                return 0;

            if(tablero[y][x] != 0)
                return 0;
        }
    }

    return 1;
}

int moverPieza(int** tablero, Pieza p, int *fila, int *columna, int df, int dc)
{
    int nf = *fila + df;
    int nc = *columna + dc;

    if(puedeColocarPieza(tablero, p, nf, nc))
    {
        *fila = nf;
        *columna = nc;
        return 1;
    }

    return 0;
}

int hayBloquesEnFilasOcultas(int** tablero)
{
    for(int i = 0; i < FILAS_OCULTAS_T; i++)
        for(int j = 0; j < ANCHO_T; j++)
            if(tablero[i][j] != 0)
                return 1;

    return 0;
}

int filaCompleta(int** tablero, int fila)
{
    for(int j = 0; j < ANCHO_T; j++)
        if(tablero[fila][j] == 0)
            return 0;

    return 1;
}

void eliminarFila(int** tablero, int fila)
{
    for(int i = fila; i > 0; i--)
        for(int j = 0; j < ANCHO_T; j++)
            tablero[i][j] = tablero[i - 1][j];

    for(int j = 0; j < ANCHO_T; j++)
        tablero[0][j] = 0;
}

int eliminarFilasCompletas(int** tablero)
{
    int eliminadas = 0;

    for(int i = ALTO_MATRIZ_T - 1; i >= FILAS_OCULTAS_T; i--)
    {
        if(filaCompleta(tablero, i))
        {
            eliminarFila(tablero, i);
            eliminadas++;
            i++;
        }
    }

    return eliminadas;
}
