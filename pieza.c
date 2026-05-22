#include "pieza.h"
#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"
#include <time.h>
#include "graficos.h"

#define ANCHO_VENTANA 128
#define ALTO_VENTANA 128
#define ESCALA_VENTANA 5

// --- Definición de Piezas ---

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
    8
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

// --- Gestión de Memoria del Tablero ---

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
        free(*i);

    free(m);
}

void inicializarMatriz(int** m, int filas, int columnas)
{
    (void)columnas;
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
}

// --- Lógica Gráfica y de Piezas ---

void dibujarBloque(int x, int y, uint8_t color)
{
    for(int i = 0; i < TAM_BLOQUE; i++)
        for(int j = 0; j < TAM_BLOQUE; j++)
            gbt_dibujar_pixel(x + j, y + i, color);
}

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

int colocarPieza(int** tablero, Pieza p, int fila, int columna, int cantpiezas)
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
    cantpiezas++;
    return cantpiezas;
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
                    (uint8_t)tablero[i][j]
                );
            }
        }
    }
}

Pieza rotarPieza(Pieza pieza)
{
    Pieza aux = (Pieza){0};
    aux.color = pieza.color;

    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            // Rotación correcta de 90 grados para Tetris
            aux.forma[i][j] = pieza.forma[TAM - 1 - j][i];
        }
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

            // Control de límites del tablero
            if(y < 0 || y >= ALTO_T)  return 0;
            if(x < 0 || x >= ANCHO_T) return 0;

            // Control de colisión con bloques existentes
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

// --- Mecánicas de Filas y Puntuación ---

int filaCompleta(int** tablero, int fila)
{
    for(int j = 0; j < ANCHO_T; j++)
    {
        if(tablero[fila][j] == 0)
            return 0;
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
            i++; // Se vuelve a revisar la misma fila porque bajó contenido nuevo
        }
    }
    return eliminadas;
}

int sistemaPuntuacion(int puntaje, int filasborradas, double tiempocaida)
{
    double punt = 100.0;
    punt = (punt / tiempocaida) * 1.2; // A menor tiempo de caída, mayor recompensa

    if(filasborradas == 1)      puntaje += 1 * punt;
    else if(filasborradas == 2) puntaje += 3 * punt;
    else if(filasborradas == 3) puntaje += 5 * punt;
    else if(filasborradas == 4) puntaje += 8 * punt;

    return puntaje;
}

// --- Bucle Principal del Juego ---

void juego()
{
    char nombre[MAX_NOMBRE] = "";
    int filasborradas = 0;
    int puntaje = 0;
    int cantpiezas = 0;
    double tiempocaida = 1.0;
    int longitud = Presentacion(nombre);
    uint8_t tocandoPiso = 0;

    tGBT_Temporizador *temporizador = gbt_temporizador_crear(tiempocaida);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
        return;
    }

    tGBT_Temporizador *temporizadorLock = gbt_temporizador_crear(0.2);
    if (!temporizadorLock) {
        fprintf(stderr, "Error al crear el temporizador lock: %s\n", gbt_obtener_log());
        gbt_temporizador_destruir(temporizador);
        return;
    }

    srand((unsigned)time(0));

    uint8_t corriendo = 1;
    int fila = 0;
    int columna = 3;

    int random = rand() % 7;
    Pieza vector[7] = {piezaI, piezaO, piezaT, piezaJ, piezaL, piezaS, piezaZ};

    int** tablero = crearMatriz(ALTO_T, ANCHO_T);
    if (!tablero) {
        printf("Error de memoria en el tablero\n");
        gbt_temporizador_destruir(temporizador);
        gbt_temporizador_destruir(temporizadorLock);
        return;
    }

    Pieza piezaOrig = vector[random];
    inicializarMatriz(tablero, ALTO_T, ANCHO_T);

    if(!puedeColocarPieza(tablero, piezaOrig, fila, columna))
    {
        printf("Game Over (no entra al iniciar)\n");
        corriendo = 0;
    }

    while(corriendo)
    {
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        if(tecla == GBTK_ESCAPE)
            corriendo = 0;

        // Entradas del usuario
        if(tecla == GBTK_a || tecla == GBTK_IZQUIERDA)
            moverPieza(tablero, piezaOrig, &fila, &columna, 0, -1);

        if(tecla == GBTK_d || tecla == GBTK_DERECHA)
            moverPieza(tablero, piezaOrig, &fila, &columna, 0, 1);

        if(tecla == GBTK_s || tecla == GBTK_ABAJO){
            if(moverPieza(tablero, piezaOrig, &fila, &columna, 1, 0)) {
                puntaje++;
            }
        }

        if(tecla == GBTK_w || tecla == GBTK_ARRIBA)
        {
            Pieza rotada = rotarPieza(piezaOrig);
            if(puedeColocarPieza(tablero, rotada, fila, columna))
                piezaOrig = rotada;
        }

        // Caída automática por gravedad
        if(gbt_temporizador_consumir(temporizador))
            moverPieza(tablero, piezaOrig, &fila, &columna, 1, 0);

        // Lógica de colisión con el suelo o piezas inferiores
        if(!puedeColocarPieza(tablero, piezaOrig, fila + 1, columna))
        {
            if(!tocandoPiso)
            {
                tocandoPiso = 1;
                gbt_temporizador_destruir(temporizadorLock);
                temporizadorLock = gbt_temporizador_crear(0.2); // Margen para deslizar la pieza
            }

            if(gbt_temporizador_consumir(temporizadorLock))
            {
                cantpiezas = colocarPieza(tablero, piezaOrig, fila, columna, cantpiezas);
                filasborradas = eliminarFilasCompletas(tablero);

                // Procesar sistema de puntos e incremento de velocidad
                puntaje = sistemaPuntuacion(puntaje, filasborradas, tiempocaida);

                if (cantpiezas % 10 == 0)
                {
                    tiempocaida *= 0.97; // Aumenta la velocidad un 3%
                    gbt_temporizador_destruir(temporizador);
                    temporizador = gbt_temporizador_crear(tiempocaida);
                    if (!temporizador) {
                        fprintf(stderr, "Error al actualizar el temporizador: %s\n", gbt_obtener_log());
                        corriendo = 0;
                    }
                }

                // Siguiente pieza
                fila = 0;
                columna = 3;
                random = rand() % 7;
                piezaOrig = vector[random];
                tocandoPiso = 0;

                if(!puedeColocarPieza(tablero, piezaOrig, fila, columna))
                {
                    printf("Game Over\n");
                    corriendo = 0;
                }
            }
        }
        else
        {
            tocandoPiso = 0;
        }

        // Renderizado en pantalla usando dibujarInterfaz de graficos.h
        gbt_borrar_backbuffer(0);
        dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje);
        gbt_volcar_backbuffer();
        gbt_esperar(20);
    }

    // Liberación de recursos al salir
    destruirMatriz(tablero, ALTO_T);
    gbt_temporizador_destruir(temporizador);
    gbt_temporizador_destruir(temporizadorLock);
}
