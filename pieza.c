#include "pieza.h"
#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"
#include <time.h>

#define ANCHO_VENTANA 128
#define ALTO_VENTANA 128
#define ESCALA_VENTANA 5

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
    9

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
    14

};



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
    int** ult = m + (filas - 1);

    for(int** i = m; i <= ult; i++)

    {
        free(*i);
    }

    free(m);
}

void inicializarMatriz(int** m, int filas, int columnas)

{

    //int valor = 1;

    for(int i = 0; i < filas; i++)

    {

        for(int j = 0; j < columnas; j++)

        {

            m[i][j] = 0;

        }

    }

}

void mostrarMatriz(int** m, int filas, int columnas)

{

    for(int i = 0; i < filas; i++)

    {

        for(int j = 0; j < columnas; j++)

        {

            printf("[%02d]", m[i][j]);

        }

        putchar('\n');

    }

}

void dibujarBloque(int x, int y, uint8_t color)
{
    for(int i = 0; i < TAM_BLOQUE; i++)
    {
        for(int j = 0; j < TAM_BLOQUE; j++)
        {
            gbt_dibujar_pixel(x + j, y + i, color);
        }
    }
}


void dibujarPieza(Pieza p, int posX, int posY)
{
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
            {
                dibujarBloque( posX + j * TAM_BLOQUE, posY + i * TAM_BLOQUE, p.color
                );
            }
        }
    }
}

void colocarPieza(int** tablero, Pieza p, int fila, int columna
)
{
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
            {
                tablero[fila + i][columna + j] = p.color;
            }
        }
    }
}

void dibujarTablero(int** tablero, int offsetX, int offsetY)
{
    for(int i = 0; i < ALTO_T; i++)
    {
        for(int j = 0; j < ANCHO_T; j++)
        {
            if(tablero[i][j] != 0)
            {
                dibujarBloque(
                    offsetX + j * TAM_BLOQUE,
                    offsetY + i * TAM_BLOQUE,
                    tablero[i][j]
                );
            }
        }
    }
}

Pieza rotarPieza (Pieza pieza)
{
    int i,j;
    //int  N = TAM;
    Pieza aux={0};
    aux.color = pieza.color;

    for(i=0;i<TAM;i++)
    {
        for(j=0;j<TAM;j++)
        {

            aux.forma[i][j] =pieza.forma [j][i];
        }
    }
    return aux;
}

int alturaPieza(Pieza p)
{
    int max = 0;

    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
            {
                max = i + 1;
            }
        }
    }

    return max;
}

int anchoPieza(Pieza p)
{
    int max = 0;

    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
            {
                if(j + 1 > max)
                {
                    max = j + 1;
                }
            }
        }
    }

    return max;
}

int puedeMoverDerecha(int** tablero, Pieza p, int fila, int columna)
{
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
            {
                int nuevaCol = columna + j + 1;

                if(nuevaCol >= ANCHO_T)
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}

int puedeMoverIzquierda(int** tablero, Pieza p, int fila, int columna)
{
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
            {
                int nuevaCol = columna + j - 1;

                if(nuevaCol < 0)
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}


void juego()
{
    tGBT_Temporizador *temporizador = gbt_temporizador_crear(1.0);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador para los dibujos: %s\n", gbt_obtener_log());
        return;
    }

    srand(time(0));

    int offsetX = (ANCHO_VENTANA - (ANCHO_T * TAM_BLOQUE)) / 2;
    int offsetY = (ALTO_VENTANA - (ALTO_T * TAM_BLOQUE)) / 2;


    uint8_t corriendo = 1;

    uint8_t fila= 0;
    uint8_t columna= 3;
    uint8_t random= rand() % 7;
    Pieza vector[7]={piezaI, piezaO ,piezaT ,piezaJ ,piezaL ,piezaS ,piezaZ};

    int** tablero = crearMatriz(ALTO_T, ANCHO_T);

    if (!tablero)
    {
        printf("Error de memoria\n");
        return;
    }




    Pieza piezaOrig = vector[random];
    inicializarMatriz(tablero, ALTO_T, ANCHO_T);

    while(corriendo)
    {
        gbt_procesar_entrada();

        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();


        if(tecla == GBTK_ESCAPE)
        {
            corriendo = 0;
        }

        if(tecla == GBTK_a && columna > 0)
        {
            if(puedeMoverIzquierda(tablero, piezaOrig, fila, columna))
            {
                columna--;
            }
        }

        if(tecla == GBTK_d && columna < ANCHO_T)
        {
            if(puedeMoverDerecha(tablero, piezaOrig, fila, columna))
            {
                columna++;
            }
        }

        if(tecla == GBTK_s)
        {
            fila++;
        }

        if(gbt_temporizador_consumir(temporizador))
        {
            fila++;
        }
        if(tecla == GBTK_w)
        {
            piezaOrig=rotarPieza(piezaOrig);
        }
        // Si toca el piso
        if(fila >= ALTO_T - alturaPieza(piezaOrig))
        {

            colocarPieza(tablero, piezaOrig, fila, columna);

            fila = 0;
            columna = 3;
            random= rand() % 7;
            piezaOrig = vector[random];

        }

        gbt_borrar_backbuffer(0);

        // Dibujar bloques ya colocados
        dibujarTablero(tablero, offsetX, offsetY);

        // Dibujar pieza cayendo
        dibujarPieza( piezaOrig, offsetX + columna * TAM_BLOQUE, offsetY + fila * TAM_BLOQUE);


        gbt_volcar_backbuffer();

        gbt_esperar(16);



    }


    destruirMatriz(tablero, ALTO_T);
    gbt_temporizador_destruir(temporizador);
}
