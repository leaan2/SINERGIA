#include "pieza.h"
#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"
#include <time.h>
<<<<<<< HEAD
#include "graficos.h"
=======

#define ANCHO_VENTANA 128
#define ALTO_VENTANA 128
#define ESCALA_VENTANA 5

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
Pieza piezaT = {
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    12
<<<<<<< HEAD
=======

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
};

Pieza piezaI = {
    {
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
<<<<<<< HEAD
    8
=======
    9

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
};

Pieza piezaO = {
    {
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    14
<<<<<<< HEAD
=======

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
};

Pieza piezaJ = {
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    5
<<<<<<< HEAD
=======

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
};

Pieza piezaL = {
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    7
<<<<<<< HEAD
=======

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
};

Pieza piezaS = {
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    3
<<<<<<< HEAD
=======

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
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
<<<<<<< HEAD
=======

};



int** crearMatriz(int filas, int columnas)
{
    int** m = malloc(filas * sizeof(int*));

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
    if(!m)
        return NULL;

    for(int i = 0; i < filas; i++)
    {
        m[i] = malloc(columnas * sizeof(int));
<<<<<<< HEAD
=======

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
        if(!m[i])
        {
            destruirMatriz(m, i);
            return NULL;
        }
    }

    return m;
}

void destruirMatriz(int** m, int filas)
<<<<<<< HEAD
=======

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
{
    int** ult = m + (filas - 1);

    for(int** i = m; i <= ult; i++)
        free(*i);

<<<<<<< HEAD
=======
    {
        free(*i);
    }

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
    free(m);
}

void inicializarMatriz(int** m, int filas, int columnas)
{
    (void)columnas; // no se usa en el loop, pero lo dejamos por firma original

    for(int i = 0; i < filas; i++)
        for(int j = 0; j < ANCHO_T; j++)
            m[i][j] = 0;
}

void mostrarMatriz(int** m, int filas, int columnas)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
            printf("[%02d]", m[i][j]);

        putchar('\n');
    }
<<<<<<< HEAD
=======

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

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
}

void dibujarBloque(int x, int y, uint8_t color)
{
    for(int i = 0; i < TAM_BLOQUE; i++)
        for(int j = 0; j < TAM_BLOQUE; j++)
            gbt_dibujar_pixel(x + j, y + i, color);
}

<<<<<<< HEAD
=======
    {
        for(int j = 0; j < TAM_BLOQUE; j++)
        {
            gbt_dibujar_pixel(x + j, y + i, color);
        }
    }
}


>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
void dibujarPieza(Pieza p, int posX, int posY)
{
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
                dibujarBloque(posX + j * TAM_BLOQUE, posY + i * TAM_BLOQUE, p.color);
        }
    }
}

<<<<<<< HEAD
int colocarPieza(int** tablero, Pieza p, int fila, int columna, int cantpiezas)
=======
void colocarPieza(int** tablero, Pieza p, int fila, int columna)
            {
                dibujarBloque( posX + j * TAM_BLOQUE, posY + i * TAM_BLOQUE, p.color
                );
            }
        }
    }
}

void colocarPieza(int** tablero, Pieza p, int fila, int columna
)
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
{
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
<<<<<<< HEAD
=======
                tablero[fila + i][columna + j] = p.color;
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
            {
                tablero[fila + i][columna + j] = p.color;
            }
        }
    }
<<<<<<< HEAD
    cantpiezas++;
    return cantpiezas;
}



=======
}

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
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
                    (uint8_t)tablero[i][j]
                );
            }
        }
    }
}

<<<<<<< HEAD


=======
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
Pieza rotarPieza(Pieza pieza)
{
    Pieza aux = (Pieza){0};
    aux.color = pieza.color;

    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            aux.forma[i][j] = pieza.forma[TAM - 1 - j][i];
        }
    }

<<<<<<< HEAD
=======
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
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
    return aux;
}

int alturaPieza(Pieza p)
{
    int max = 0;

    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++)
            if(p.forma[i][j] == 1)
                max = i + 1;
<<<<<<< HEAD
=======
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
            {
                max = i + 1;
            }
        }
    }
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54

    return max;
}


int puedeColocarPieza(int** tablero, Pieza p, int fila, int columna)
{
<<<<<<< HEAD
=======
int anchoPieza(Pieza p)
{
    int max = 0;

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 0)
                continue;

            int y = fila + i;
            int x = columna + j;

            // Nos fijamos si la pieza se sale del tablero
            if(y < 0 || y >= ALTO_T)  return 0;
            if(x < 0 || x >= ANCHO_T) return 0;

            // Nos fijamos si la pieza colisiona con otra pieza
            if(tablero[y][x] != 0) return 0;
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

int filaCompleta(int** tablero, int fila)
{
    for(int j = 0; j < ANCHO_T; j++)
    {
        if(tablero[fila][j] == 0)
            return 0;  // si no esta completa
    }
    return 1;
}

void eliminarFila(int** tablero, int fila)
{
    for(int i = fila; i > 0; i--)
    {
        for(int j = 0; j < ANCHO_T; j++)
        {
            tablero[i][j] = tablero[i - 1][j];
        }
    }

    for(int j = 0; j < ANCHO_T; j++)
    {
        tablero[0][j] = 0;
    }
}

int eliminarFilasCompletas(int** tablero)
{
    int eliminadas = 0;

    for(int i = ALTO_T - 1; i >= 0; i--)
    {
        if(filaCompleta(tablero, i))
        {
            eliminarFila(tablero, i);
            eliminadas++;
<<<<<<< HEAD
            i++;
=======
            i++; /* volver a revisar la misma fila (porque baj� contenido nuevo) */
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
        }
    }

    return eliminadas;
}

<<<<<<< HEAD
int sistemaPuntuacion(int puntaje, int filasborradas, double tiempocaida)
{

    double punt=100.0;

    punt=(punt / tiempocaida) * 1.2; // Menos tiempo de caida, mayor puntaje obtenido.
    if(filasborradas == 1 )
    {
        puntaje+=1*punt;
    }
    if(filasborradas == 2)
    {
        puntaje+=3*punt;
    }
    if(filasborradas == 3)
    {
        puntaje +=5*punt;
    }
    if (filasborradas == 4)
    {
        puntaje+=8*punt;
    }
    return puntaje;
}

void juego()
{
    char nombre[MAX_NOMBRE] = "";
    int filasborradas =0;
    int puntaje=0;
    int cantpiezas=0;
    double tiempocaida = 1.0;
    int longitud = Presentacion(nombre);
    uint8_t tocandoPiso=0 ;
    
    tGBT_Temporizador *temporizador = gbt_temporizador_crear(tiempocaida);
        if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
        return;
        }
      
    tGBT_Temporizador *temporizadorLock = gbt_temporizador_crear(0.2);   //Temporiza or para controlar el tiempo antes de que toque el piso// 
        if (!temporizadorLock) {
                fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
                return;
                }

    srand((unsigned)time(0));

=======
void juego()
{

     tGBT_Temporizador *temporizador = gbt_temporizador_crear(1.0);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
        return;
    }

    srand((unsigned)time(0));
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
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54

    uint8_t corriendo = 1;

    int fila = 0;
    int columna = 3;

    int random = rand() % 7;
    Pieza vector[7] = {piezaI, piezaO, piezaT, piezaJ, piezaL, piezaS, piezaZ};

    int** tablero = crearMatriz(ALTO_T, ANCHO_T);
    if (!tablero) {
<<<<<<< HEAD
=======

    uint8_t corriendo = 1;

    uint8_t fila= 0;
    uint8_t columna= 3;
    uint8_t random= rand() % 7;
    Pieza vector[7]={piezaI, piezaO ,piezaT ,piezaJ ,piezaL ,piezaS ,piezaZ};

    int** tablero = crearMatriz(ALTO_T, ANCHO_T);

    if (!tablero)
    {
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
        printf("Error de memoria\n");
        return;
    }

    Pieza piezaOrig = vector[random];
    inicializarMatriz(tablero, ALTO_T, ANCHO_T);

    /* Si por alguna raz�n no entra al inicio -> game over simple */
    if(!puedeColocarPieza(tablero, piezaOrig, fila, columna))
    {
        printf("Game Over (no entra al iniciar)\n");
        corriendo = 0;
    }

    while(corriendo)
    {
<<<<<<< HEAD


=======
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        if(tecla == GBTK_ESCAPE)
            corriendo = 0;

        /* Movimiento con colisi�n real */
        if(tecla == GBTK_a || tecla == GBTK_IZQUIERDA)
<<<<<<< HEAD
          moverPieza(tablero, piezaOrig, &fila, &columna, 0, -1);
=======
            moverPieza(tablero, piezaOrig, &fila, &columna, 0, -1);
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54

        if(tecla == GBTK_d || tecla == GBTK_DERECHA)
            moverPieza(tablero, piezaOrig, &fila, &columna, 0, 1);

<<<<<<< HEAD
        if(tecla == GBTK_s || tecla == GBTK_ABAJO){
            moverPieza(tablero, piezaOrig, &fila, &columna, 1, 0);
            puntaje++;
        }
=======
        if(tecla == GBTK_s || tecla == GBTK_ABAJO)
            moverPieza(tablero, piezaOrig, &fila, &columna, 1, 0);

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
        if(gbt_temporizador_consumir(temporizador))
            moverPieza(tablero, piezaOrig, &fila, &columna, 1, 0);

        if(tecla == GBTK_w || tecla == GBTK_ARRIBA)
        {
            Pieza rotada = rotarPieza(piezaOrig);
            if(puedeColocarPieza(tablero, rotada, fila, columna))
                piezaOrig = rotada;
        }

        /* Si NO puede bajar una fila, se fija la pieza y aparece otra */
        if(!puedeColocarPieza(tablero, piezaOrig, fila + 1, columna))
        {
<<<<<<< HEAD
             if(!tocandoPiso)
            {
                tocandoPiso = 1;
                gbt_temporizador_destruir(temporizadorLock);
                temporizadorLock = gbt_temporizador_crear(0.2);
            }


            if(gbt_temporizador_consumir(temporizadorLock))
            {
            
            cantpiezas = colocarPieza(tablero, piezaOrig, fila, columna, cantpiezas);

            filasborradas=eliminarFilasCompletas(tablero);
=======
            colocarPieza(tablero, piezaOrig, fila, columna);

            eliminarFilasCompletas(tablero);
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54

            fila = 0;
            columna = 3;
            random = rand() % 7;
            piezaOrig = vector[random];

<<<<<<< HEAD
            if (cantpiezas % 10== 0)
            {
                tiempocaida *= 0.97; //caida de 3%
                gbt_temporizador_destruir(temporizador);
                temporizador = gbt_temporizador_crear(tiempocaida);
                if (!temporizador) {
                fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
                return;
                }
            }
            puntaje=sistemaPuntuacion(puntaje,filasborradas,tiempocaida);
=======
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
            if(!puedeColocarPieza(tablero, piezaOrig, fila, columna))
            {
                printf("Game Over\n");
                corriendo = 0;
            }
        }
<<<<<<< HEAD
      }
        else 
         {
            tocandoPiso= 0;
         } 

        


              /* Render */
            gbt_borrar_backbuffer(0);
            dibujarInterfaz(tablero,piezaOrig,fila,columna,nombre,longitud, puntaje);
            gbt_volcar_backbuffer();
            gbt_esperar(20);
    }

    destruirMatriz(tablero, ALTO_T);
    gbt_temporizador_destruir(temporizador);
    gbt_temporizador_destruir(temporizadorLock);
}


=======

        /* Render */
        gbt_borrar_backbuffer(0);

        dibujarTablero(tablero, offsetX, offsetY);
        dibujarPieza(piezaOrig,
                     offsetX + columna * TAM_BLOQUE,
                     offsetY + fila * TAM_BLOQUE);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
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
>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
