#include "pieza.h"
#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"
#include <time.h>
#include "graficos.h"


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

// --- Lógica Gráfica con Soporte de Paletas ---

void dibujarBloque(int x, int y, uint8_t color_original, int paleta_tipo)
{
    uint8_t color_base = color_original;
    uint8_t brillo = 15;
    uint8_t sombra = 8;
    uint8_t centro = color_original;

    // =========================
    // PALETAS
    // =========================

    if (color_original != 0)
    {
        switch (paleta_tipo)
        {
            case 1: // GAMEBOY
                color_base = 2;
                brillo = 10;
                sombra = 0;
                centro = 2;
                break;

            case 2: // NEON
                color_base = color_original;

                brillo = 15;
                sombra = 8;

                break;

            case 0:
            default:
                color_base = color_original;
                brillo = 15;
                sombra = 8;
                break;
        }
    }

    // =========================
    // CUERPO PRINCIPAL
    // =========================

    Dibujar_rect(
        x,
        y,
        TAM_BLOQUE,
        TAM_BLOQUE,
        color_base
    );

    // =========================
    // BORDE SUPERIOR (BRILLO)
    // =========================

    Dibujar_rect(
        x,
        y,
        TAM_BLOQUE,
        2,
        brillo
    );

    // =========================
    // BORDE IZQUIERDO (BRILLO)
    // =========================

    Dibujar_rect(
        x,
        y,
        2,
        TAM_BLOQUE,
        brillo
    );

    // =========================
    // BORDE INFERIOR (SOMBRA)
    // =========================

    Dibujar_rect(
        x,
        y + TAM_BLOQUE - 2,
        TAM_BLOQUE,
        2,
        sombra
    );

    // =========================
    // BORDE DERECHO (SOMBRA)
    // =========================

    Dibujar_rect(
        x + TAM_BLOQUE - 2,
        y,
        2,
        TAM_BLOQUE,
        sombra
    );

    // =========================
    // CENTRO INTERNO
    // =========================

    Dibujar_rect(
        x + 3,
        y + 3,
        TAM_BLOQUE - 6,
        TAM_BLOQUE - 6,
        centro
    );

    // =========================
    // PIXEL BRILLO ESQUINA
    // =========================

    Dibujar_rect(
        x + 2,
        y + 2,
        2,
        2,
        15
    );
}


/*
    if (color_original != 0) { // Si no es un bloque vacío (fondo)
        switch (paleta_tipo)
        {
            case 1:
                // === PALETA 1: MODO GAMEBOY MONOCROMÁTICO ===
                // Forzamos a que todas las piezas usen tonos verdes retro de la CGA (color 2 o 10)
                color_final = 2;
                break;

            case 2:
                // === PALETA 2: MODO NEÓN APOCALÍPTICO / FLÚOR ===
                // Mapeamos los colores originales a sus versiones intensas/brillantes de la CGA
                if (color_original == 1)  color_final = 9;  // Azul claro brillante
                if (color_original == 4)  color_final = 12; // Rojo claro brillante
                if (color_original == 5)  color_final = 13; // Magenta brillante
                if (color_original == 3)  color_final = 11; // Cyan brillante
                if (color_original == 14) color_final = 14; // Amarillo (ya es brillante)
                if (color_original == 7)  color_final = 15; // Blanco puro
                if (color_original == 12) color_final = 10; // Verde brillante
                break;

            case 0:
            default:
                // === PALETA 0: CLÁSICA ===
                // Mantiene los colores originales tal cual están definidos en tus structs
                color_final = color_original;
                break;
        }
    }

    // Dibujamos el bloque con el color adaptado
    for(int i = 0; i < TAM_BLOQUE; i++)
        for(int j = 0; j < TAM_BLOQUE; j++)
            gbt_dibujar_pixel(x + j, y + i, color_final);
       
            }
            */


// Actualizamos dibujarPieza para que reciba la paleta y se la pase a dibujarBloque
void dibujarPieza(Pieza p, int posX, int posY, int paleta_tipo)
{
    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(p.forma[i][j] == 1)
                dibujarBloque(posX + j * TAM_BLOQUE, posY + i * TAM_BLOQUE, p.color, paleta_tipo);
        }
    }
}

// Actualizamos dibujarTablero para que reciba la paleta y se la pase a dibujarBloque
void dibujarTablero(int** tablero, int offsetX, int offsetY, int paleta_tipo)
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
                    (uint8_t)tablero[i][j],
                    paleta_tipo
                );
            }
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
    int longitud = Presentacion(nombre);

    // --- CARGAR CONFIGURACIÓN DESDE ARCHIVO ---
    Configuracion config;
    cargar_configuracion(&config);

    EstadoJuego estadoActual = estado_menu;
    int opcion_seleccionada = 0;

    // Variables de control de la partida
    int filasborradas = 0;
    int puntaje = 0;
    int cantpiezas = 0;
    double tiempocaida = config.velocidad_init;
    uint8_t tocandoPiso = 0;

    tGBT_Temporizador *temporizador = NULL;
    tGBT_Temporizador *temporizadorLock = NULL;

    srand((unsigned)time(0));

    uint8_t corriendo = 1;
    int fila = 0;
    int columna = 3;

    int random = rand() % 7;
    Pieza vector[7] = {piezaI, piezaO, piezaT, piezaJ, piezaL, piezaS, piezaZ};

    // El tablero se crea ANTES del bucle para que persista si pausamos y volvemos
    int** tablero = crearMatriz(ALTO_T, ANCHO_T);
    inicializarMatriz(tablero, ALTO_T, ANCHO_T);
    Pieza piezaOrig = vector[random];

    while(corriendo)
    {
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        gbt_borrar_backbuffer(0);

        switch(estadoActual)
        {
            case estado_menu:
                // --- LÓGICA DEL MENÚ GRÁFICO INTERACTIVO ---
                if(tecla == GBTK_s || tecla == GBTK_ABAJO) opcion_seleccionada = (opcion_seleccionada + 1) % 4;
                if(tecla == GBTK_w || tecla == GBTK_ARRIBA) opcion_seleccionada = (opcion_seleccionada - 1 + 4) % 4;

                // Modificar valores con Izquierda/Derecha
                if(tecla == GBTK_d || tecla == GBTK_DERECHA || tecla == GBTK_a || tecla == GBTK_IZQUIERDA) {
                    int dir = (tecla == GBTK_d || tecla == GBTK_DERECHA) ? 1 : -1;

                    if(opcion_seleccionada == 0) { // Cambiar Paleta
                        config.paleta_tipo = (config.paleta_tipo + dir + 3) % 3;
                    }
                    else if(opcion_seleccionada == 1) { // Cambiar Resolución en el Menú
                        // Alterna limpiamente entre 0 (CGA) y 1 (VGA)
                        config.resolucion_tipo = (config.resolucion_tipo + dir + 2) % 2;

                        // Mensaje de control en consola (opcional para depurar)
                        printf("Resolucion logica seteada en: %s\n",
                                (config.resolucion_tipo == 1) ? "VGA (640x480)" : "CGA (320x200)");
                    }
                                        else if(opcion_seleccionada == 2) { // Cambiar Velocidad Inicial
                                            config.velocidad_init -= dir * 0.1;
                                            if(config.velocidad_init < 0.1) config.velocidad_init = 0.1;
                                            if(config.velocidad_init > 1.5) config.velocidad_init = 1.5;

                                            // SOLUCIÓN CONTENIDO BASURA: Usamos %f con precisión de 2 decimales (.2)
                                            printf("Velocidad seleccionada: %.2f segundos\n", config.velocidad_init);
                                        }
                                    }

                // Si tocás ESCAPE en el menú principal, ahí sí cierra el juego por completo
                if(tecla == GBTK_ESCAPE) {
                    corriendo = 0;
                }

                // --- RENDERIZADO GRÁFICO DEL MENÚ (Valores dinámicos) ---
                dibujar_matriz(30, 10, 8, 8, letra_M, 4);
                dibujar_matriz(38, 10, 8, 8, letra_E, 4);
                dibujar_matriz(46, 10, 8, 8, letra_N, 4);
                dibujar_matriz(54, 10, 8, 8, letra_U, 4);

                // Fila 0: PALETA
                if(opcion_seleccionada == 0) Dibujar_rect(10, 42, 4, 4, 14); // Puntero amarillo
                dibujar_matriz(20, 40, 8, 8, letra_P, 4);

                // Fila 1: RESOLUCIÓN
               // Fila 1: RESOLUCIÓN
                    if(opcion_seleccionada == 1) Dibujar_rect(10, 62, 4, 4, 14);
                    dibujar_matriz(20, 60, 8, 8, letra_R, 4); // Dibuja la 'R' de resolución

                    // Dibujamos al lado "CGA" o "VGA" dinámicamente según la estructura config
                    if(config.resolucion_tipo == 0) {
                        dibujar_matriz(35, 60, 8, 8, letra_C, 14);
                        dibujar_matriz(43, 60, 8, 8, letra_G, 14);
                        dibujar_matriz(51, 60, 8, 8, letra_A, 14);
                    } else {
                        dibujar_matriz(35, 60, 8, 8, letra_V, 14);
                        dibujar_matriz(43, 60, 8, 8, letra_G, 14);
                        dibujar_matriz(51, 60, 8, 8, letra_A, 14);
                    }

                // Fila 2: VELOCIDAD
                if(opcion_seleccionada == 2) Dibujar_rect(10, 82, 4, 4, 14);
                dibujar_matriz(20, 80, 8, 8, letra_V, 4);

                // Fila 3: JUGAR / CONTINUAR
                if(opcion_seleccionada == 3) Dibujar_rect(10, 112, 4, 4, 10); // Puntero verde
                dibujar_matriz(20, 110, 8, 8, letra_J, 2);
                dibujar_matriz(28, 110, 8, 8, letra_U, 2);
                dibujar_matriz(36, 110, 8, 8, letra_G, 2);
                dibujar_matriz(44, 110, 8, 8, letra_A, 2);
                dibujar_matriz(52, 110, 8, 8, letra_R, 2);

                // Acción al presionar ENTER o ESPACIO en JUGAR
                if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_seleccionada == 3) {

                    // Guardamos los cambios para que sean perdurables
                    guardar_configuracion(&config);

                    // SOLUCIÓN CAMBIO DE VELOCIDAD EN EN PARTIDA INICIADA:
                    // Si el juego ya había empezado (el temporizador ya existe), lo destruimos para aplicar el nuevo tiempo
                    if (temporizador) {
                        gbt_temporizador_destruir(temporizador);
                        temporizador = NULL;
                    }
                    if (temporizadorLock) {
                        gbt_temporizador_destruir(temporizadorLock);
                        temporizadorLock = NULL;
                    }

                    // Creamos el temporizador con la velocidad modificada (sea nueva partida o reanudada)
                    tiempocaida = config.velocidad_init;
                    temporizador = gbt_temporizador_crear(tiempocaida);
                    temporizadorLock = gbt_temporizador_crear(0.2);

                    printf("Juego iniciado/reanudado. Gravedad: %.2f segundos por bloque.\n", tiempocaida);
                    estadoActual = estado_juego; // Vamos a jugar
                }
                break;

            case estado_juego:
                // --- CAMBIO CLAVE: ESCAPE VA AL MENÚ, NO CIERRA ---
                if(tecla == GBTK_ESCAPE) {
                    estadoActual = estado_menu;
                    break;
                }

                // Botón de Pausa clásica alternativo (Tecla P)
                if(tecla == GBTK_p) {
                    estadoActual = estado_pausa;
                    break;
                }

                // Controles estándar del Tetris
                if(tecla == GBTK_a || tecla == GBTK_IZQUIERDA) moverPieza(tablero, piezaOrig, &fila, &columna, 0, -1);
                if(tecla == GBTK_d || tecla == GBTK_DERECHA)   moverPieza(tablero, piezaOrig, &fila, &columna, 0, 1);
                if(tecla == GBTK_s || tecla == GBTK_ABAJO)     { if(moverPieza(tablero, piezaOrig, &fila, &columna, 1, 0)) puntaje++; }
                if(tecla == GBTK_w || tecla == GBTK_ARRIBA) {
                    Pieza rotada = rotarPieza(piezaOrig);
                    if(puedeColocarPieza(tablero, rotada, fila, columna)) piezaOrig = rotada;
                }

                // Gravedad del juego
                if(gbt_temporizador_consumir(temporizador))
                    moverPieza(tablero, piezaOrig, &fila, &columna, 1, 0);

                if(!puedeColocarPieza(tablero, piezaOrig, fila + 1, columna)) {
                    if(!tocandoPiso) {
                        tocandoPiso = 1;
                        gbt_temporizador_destruir(temporizadorLock);
                        temporizadorLock = gbt_temporizador_crear(0.2);
                    }

                    if(gbt_temporizador_consumir(temporizadorLock)) {
                        cantpiezas = colocarPieza(tablero, piezaOrig, fila, columna, cantpiezas);
                        filasborradas = eliminarFilasCompletas(tablero);
                        puntaje = sistemaPuntuacion(puntaje, filasborradas, tiempocaida);

                        fila = 0; columna = 3;
                        random = rand() % 7;
                        piezaOrig = vector[random];
                        tocandoPiso = 0;

                        if(!puedeColocarPieza(tablero, piezaOrig, fila, columna)) {
                            estadoActual = estado_gameover;
                        }
                    }
                } else {
                    tocandoPiso = 0;
                }

                // Render
                dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje, config.paleta_tipo);
                break;

            case estado_pausa:
                dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje, config.paleta_tipo);

                // Letrero "PAUSA"
                dibujar_matriz(40, 80, 8, 8, letra_P, 12);
                dibujar_matriz(48, 80, 8, 8, letra_A, 12);
                dibujar_matriz(56, 80, 8, 8, letra_U, 12);
                dibujar_matriz(64, 80, 8, 8, letra_S, 12);
                dibujar_matriz(72, 80, 8, 8, letra_A, 12);

                if(tecla == GBTK_p || tecla == GBTK_ESCAPE) {
                    estadoActual = estado_juego;
                }
                break;

            case estado_gameover:
                dibujar_matriz(30, 60, 8, 8, letra_G, 4);
                dibujar_matriz(38, 60, 8, 8, letra_A, 4);
                dibujar_matriz(46, 60, 8, 8, letra_M, 4);
                dibujar_matriz(54, 60, 8, 8, letra_E, 4);

                if(tecla == GBTK_ESPACIO || tecla == GBTK_ENTER) {
                    // Reiniciar el tablero a vacío para una nueva partida completa
                    inicializarMatriz(tablero, ALTO_T, ANCHO_T);
                    puntaje = 0;
                    cantpiezas = 0;
                    fila = 0; columna = 3;
                    random = rand() % 7;
                    piezaOrig = vector[random];

                    if(temporizador) gbt_temporizador_destruir(temporizador);
                    if(temporizadorLock) gbt_temporizador_destruir(temporizadorLock);
                    temporizador = NULL;
                    temporizadorLock = NULL;

                    estadoActual = estado_menu;
                }
                break;
        }

        gbt_volcar_backbuffer();
        gbt_esperar(20);
    }

    // Al cerrar la aplicación definitivamente limpiamos todo de la memoria RAM
    if(tablero) destruirMatriz(tablero, ALTO_T);
    if(temporizador) gbt_temporizador_destruir(temporizador);
    if(temporizadorLock) gbt_temporizador_destruir(temporizadorLock);
}
