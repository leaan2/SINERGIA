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
    // Si el bloque es vacío (0), no dibujamos nada para respetar el fondo
    if (color_original == 0) return; 

    uint8_t color_base = color_original;
    uint8_t brillo = 15; // Blanco para resaltar bordes
    uint8_t sombra = 0;  // Negro para la base del relieve
    uint8_t centro = color_original;

    // --- ANTICOLISIÓN DE COLOR CON EL FONDO ---
    // Si elegiste el color '1' de fondo y la pieza justo usa el color '1':
    if (color_base == 1) { 
        color_base = 9;   // Lo cambiamos dinámicamente a un azul más claro / celeste
        centro = 9;
    }
    // Si elegiste el color '8' de fondo y la pieza justo usa el color '8':
    else if (color_base == 8) {
        color_base = 7;   // Lo cambiamos a un gris claro o plateado
        centro = 7;
    }

    // =========================================
    // PALETAS (Mantenemos tu lógica previa)
    // =========================================
    if (paleta_tipo == 1) { // GAMEBOY
        color_base = 2;
        brillo = 10;
        sombra = 0;
        centro = 2;
    } else if (paleta_tipo == 2) { // NEON
        brillo = 15;
        sombra = 8;
    }

    // =========================================
    // RENDERIZADO DEL BLOQUE CON RELIEVE
    // =========================================
    // Cuerpo Base
    Dibujar_rect(x, y, TAM_BLOQUE, TAM_BLOQUE, color_base);

    // Borde Superior Izquierdo (Brillo que la separa del fondo)
    Dibujar_rect(x, y, TAM_BLOQUE, 2, brillo);
    Dibujar_rect(x, y, 2, TAM_BLOQUE, brillo);

    // Borde Inferior Derecho (Sombra de contraste)
    Dibujar_rect(x, y + TAM_BLOQUE - 2, TAM_BLOQUE, 2, sombra);
    Dibujar_rect(x + TAM_BLOQUE - 2, y, 2, TAM_BLOQUE, sombra);

    // Centro Interno
    Dibujar_rect(x + 3, y + 3, TAM_BLOQUE - 6, TAM_BLOQUE - 6, centro);
    
    // Pixel de Brillo Extremo
    Dibujar_rect(x + 2, y + 2, 2, 2, 15);
}

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

        gbt_borrar_backbuffer(9);

        // --- ADAPTACIÓN DINÁMICA DE RESOLUCIÓN ---
        int ancho_pantalla = ANCHO_VENTANA;
        int alto_pantalla = ALTO_VENTANA;

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
                        config.resolucion_tipo = (config.resolucion_tipo + dir + 2) % 2;

                        printf("Resolucion logica seteada en: %s\n",
                                (config.resolucion_tipo == 1) ? "VGA (640x480)" : "CGA (320x200)");
                    }
                    else if(opcion_seleccionada == 2) { // Cambiar Velocidad Inicial
                        config.velocidad_init -= dir * 0.1;
                        if(config.velocidad_init < 0.1) config.velocidad_init = 0.1;
                        if(config.velocidad_init > 1.5) config.velocidad_init = 1.5;

                        printf("Velocidad seleccionada: %.2f segundos\n", config.velocidad_init);
                    }
                }

                if(tecla == GBTK_ESCAPE) {
                    corriendo = 0;
                }

                // --- RENDEREADO ADAPTATIVO DEL MENÚ EN PANTALLA ---
                // Centramos un bloque virtual del menú en la mitad de la pantalla
                int menu_centro_x = ancho_pantalla / 2;
                int menu_base_y = alto_pantalla / 4;
                int espaciado_y = (alto_pantalla * 10) / 100; // Espaciado vertical porcentual

                // Letrero de "MENU" centrado
                dibujar_matriz(menu_centro_x - 16, menu_base_y - 20, 8, 8, letra_M, 4);
                dibujar_matriz(menu_centro_x - 8,  menu_base_y - 20, 8, 8, letra_E, 4);
                dibujar_matriz(menu_centro_x + 0,  menu_base_y - 20, 8, 8, letra_N, 4);
                dibujar_matriz(menu_centro_x + 8,  menu_base_y - 20, 8, 8, letra_U, 4);

                // Fila 0: PALETA
                int fila0_y = menu_base_y + espaciado_y * 0;
                if(opcion_seleccionada == 0) Dibujar_rect(menu_centro_x - 45, fila0_y + 2, 4, 4, 14);
                dibujar_matriz(menu_centro_x - 30, fila0_y, 8, 8, letra_P, 4);
                // Mostrar número de paleta al lado
                if(config.paleta_tipo == 0) dibujar_matriz(menu_centro_x + 20, fila0_y, 8, 8, letra_C, 14); // Clásica
                if(config.paleta_tipo == 1) dibujar_matriz(menu_centro_x + 20, fila0_y, 8, 8, letra_G, 14); // Gameboy
                if(config.paleta_tipo == 2) dibujar_matriz(menu_centro_x + 20, fila0_y, 8, 8, letra_N, 14); // Neón

                // Fila 1: RESOLUCIÓN
                int fila1_y = menu_base_y + espaciado_y * 1;
                if(opcion_seleccionada == 1) Dibujar_rect(menu_centro_x - 45, fila1_y + 2, 4, 4, 14);
                dibujar_matriz(menu_centro_x - 30, fila1_y, 8, 8, letra_R, 4);

                if(config.resolucion_tipo == 0) {
                    dibujar_matriz(menu_centro_x + 10, fila1_y, 8, 8, letra_C, 14);
                    dibujar_matriz(menu_centro_x + 18, fila1_y, 8, 8, letra_G, 14);
                    dibujar_matriz(menu_centro_x + 26, fila1_y, 8, 8, letra_A, 14);
                } else {
                    dibujar_matriz(menu_centro_x + 10, fila1_y, 8, 8, letra_V, 14);
                    dibujar_matriz(menu_centro_x + 18, fila1_y, 8, 8, letra_G, 14);
                    dibujar_matriz(menu_centro_x + 26, fila1_y, 8, 8, letra_A, 14);
                }

                // Fila 2: VELOCIDAD
                int fila2_y = menu_base_y + espaciado_y * 2;
                if(opcion_seleccionada == 2) Dibujar_rect(menu_centro_x - 45, fila2_y + 2, 4, 4, 14);
                dibujar_matriz(menu_centro_x - 30, fila2_y, 8, 8, letra_V, 4);
                // Representamos la velocidad de forma simple con barras o un indicador
                Dibujar_rect(menu_centro_x + 10, fila2_y + 2, (int)(config.velocidad_init * 20), 4, 14);

                // Fila 3: JUGAR
                int fila3_y = menu_base_y + espaciado_y * 3;
                if(opcion_seleccionada == 3) Dibujar_rect(menu_centro_x - 45, fila3_y + 2, 4, 4, 10);
                dibujar_matriz(menu_centro_x - 30, fila3_y, 8, 8, letra_J, 2);
                dibujar_matriz(menu_centro_x - 22, fila3_y, 8, 8, letra_U, 2);
                dibujar_matriz(menu_centro_x - 14, fila3_y, 8, 8, letra_G, 2);
                dibujar_matriz(menu_centro_x - 6,  fila3_y, 8, 8, letra_A, 2);
                dibujar_matriz(menu_centro_x + 2,  fila3_y, 8, 8, letra_R, 2);

                // Acción al presionar ENTER o ESPACIO en JUGAR
                if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_seleccionada == 3) {
                    guardar_configuracion(&config);

                    if (temporizador) {
                        gbt_temporizador_destruir(temporizador);
                        temporizador = NULL;
                    }
                    if (temporizadorLock) {
                        gbt_temporizador_destruir(temporizadorLock);
                        temporizadorLock = NULL;
                    }

                    tiempocaida = config.velocidad_init;
                    temporizador = gbt_temporizador_crear(tiempocaida);
                    temporizadorLock = gbt_temporizador_crear(0.2);

                    printf("Juego iniciado/reanudado. Gravedad: %.2f segundos por bloque.\n", tiempocaida);
                    estadoActual = estado_juego;
                }
                break;

            case estado_juego:
                if(tecla == GBTK_ESCAPE) {
                    estadoActual = estado_menu;
                    break;
                }

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

                // El renderizado de dibujarInterfaz debe internamente calcular offsets basados en ancho/alto pantalla
                dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje, config.paleta_tipo, ancho_pantalla, alto_pantalla);
                break;

            case estado_pausa:
                dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje, config.paleta_tipo, ancho_pantalla, alto_pantalla);

                // Letrero "PAUSA" centrado dinámicamente
                int pausa_x = (ancho_pantalla / 2) - 20;
                int pausa_y = alto_pantalla / 2;
                dibujar_matriz(pausa_x + 0,  pausa_y, 8, 8, letra_P, 12);
                dibujar_matriz(pausa_x + 8,  pausa_y, 8, 8, letra_A, 12);
                dibujar_matriz(pausa_x + 16, pausa_y, 8, 8, letra_U, 12);
                dibujar_matriz(pausa_x + 24, pausa_y, 8, 8, letra_S, 12);
                dibujar_matriz(pausa_x + 32, pausa_y, 8, 8, letra_A, 12);

                if(tecla == GBTK_p || tecla == GBTK_ESCAPE) {
                    estadoActual = estado_juego;
                }
                break;

            case estado_gameover:
                // Letrero "GAME OVER" o "GAME" centrado dinámicamente
                int go_x = (ancho_pantalla / 2) - 16;
                int go_y = alto_pantalla / 2;
                dibujar_matriz(go_x + 0,  go_y, 8, 8, letra_G, 4);
                dibujar_matriz(go_x + 8,  go_y, 8, 8, letra_A, 4);
                dibujar_matriz(go_x + 16, go_y, 8, 8, letra_M, 4);
                dibujar_matriz(go_x + 24, go_y, 8, 8, letra_E, 4);

                if(tecla == GBTK_ESPACIO || tecla == GBTK_ENTER) {
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

    if(tablero) destruirMatriz(tablero, ALTO_T);
    if(temporizador) gbt_temporizador_destruir(temporizador);
    if(temporizadorLock) gbt_temporizador_destruir(temporizadorLock);
}