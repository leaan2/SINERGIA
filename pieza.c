#include "pieza.h"

#include <stdlib.h>

Pieza piezaT = {
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    12
};

Pieza piezaI = {
    {
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    3
};

Pieza piezaO = {
    {
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    14
};

Pieza piezaJ = {
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    5
};

Pieza piezaL = {
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    7
};

Pieza piezaS = {
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    3
};

Pieza piezaZ = {
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    13
};

void mezclarBolsa(BolsaPiezas *bolsa)
{
    Pieza piezasBase[CANT_TETROMINOS] = {piezaI, piezaO, piezaT, piezaJ, piezaL, piezaS, piezaZ};

    for(int i = 0; i < CANT_TETROMINOS; i++)
        bolsa->piezas[i] = piezasBase[i];

    for(int i = CANT_TETROMINOS - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Pieza aux = bolsa->piezas[i];
        bolsa->piezas[i] = bolsa->piezas[j];
        bolsa->piezas[j] = aux;
    }

    bolsa->posicion = 0;
}

Pieza obtenerPiezaBolsa(BolsaPiezas *bolsa)
{
    if(bolsa->posicion >= CANT_TETROMINOS)
        mezclarBolsa(bolsa);

    return bolsa->piezas[bolsa->posicion++];
}

Pieza rotarPieza(Pieza pieza)
{
    Pieza aux = (Pieza){0};
    aux.color = pieza.color;

    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
            aux.forma[i][j] = pieza.forma[TAM - 1 - j][i];
    }

    return aux;
}

int alturaPieza(Pieza p)
{
    int max = 0;

    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++)
            if(p.forma[i][j] == 1)
                max = i + 1;

    return max;
}
