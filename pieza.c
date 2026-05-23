#include "pieza.h"
#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"
#include <time.h>
#include "presentacion.h" // 1° Las constantes base
#include "pieza.h"        // 2° Las estructuras de las piezas y ranking
#include "graficos.h"     // 3° Los gráficos que usan esas estructuras
#include "GBT/gbt.h"

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

static void obtener_resolucion_config(const Configuracion *config, int *ancho, int *alto)
{
    if(config->resolucion_tipo == 0)
    {
        *ancho = 320;
        *alto = 200;
    }
    else
    {
        *ancho = 640;
        *alto = 480;
    }
}

static void aplicar_resolucion_config(const Configuracion *config, int escala_ventana)
{
    int ancho = 0;
    int alto = 0;

    obtener_resolucion_config(config, &ancho, &alto);

    gbt_destruir_ventana();

    if(gbt_crear_ventana("Tetris", ancho, alto, escala_ventana) != 0)
    {
        fprintf(stderr, "Error cambiando resolucion: %s\n", gbt_obtener_log());
        return;
    }

    configurar_limites_dibujo(ancho, alto);

    if(gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888) != 0)
    {
        fprintf(stderr, "Error reaplicando paleta: %s\n", gbt_obtener_log());
    }
}

// --- Bucle Principal del Juego ---

void juego(int escala_ventana, int resolucion_inicial)
{
    // --- CARGAR CONFIGURACIÓN DESDE ARCHIVO ---
    Configuracion config;
    cargar_configuracion(&config);

    if(resolucion_inicial >= 0)
    {
        config.resolucion_tipo = resolucion_inicial;
        guardar_configuracion(&config);
    }

    int ancho_presentacion = 0;
    int alto_presentacion = 0;
    obtener_resolucion_config(&config, &ancho_presentacion, &alto_presentacion);

    char nombre[MAX_NOMBRE] = "";
    int longitud = Presentacion(nombre, ancho_presentacion, alto_presentacion);

    EstadoJuego estadoActual = estado_menu;
    EstadoJuego estadoAnteriorRanking = estado_menu;
    int opcion_seleccionada = 0;
    int opcion_pausa = 0;
    int opcion_configuracion = 0;

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
        int ancho_pantalla = 0;
        int alto_pantalla = 0;
        obtener_resolucion_config(&config, &ancho_pantalla, &alto_pantalla);

        switch(estadoActual)
        {
            case estado_menu:
                // --- LÓGICA DEL MENÚ GRÁFICO INTERACTIVO ---
                if(tecla == GBTK_s || tecla == GBTK_ABAJO) opcion_seleccionada = (opcion_seleccionada + 1) % 6;
                if(tecla == GBTK_w || tecla == GBTK_ARRIBA) opcion_seleccionada = (opcion_seleccionada - 1 + 6) % 6;

                // Modificar valores con Izquierda/Derecha
                if(tecla == GBTK_d || tecla == GBTK_DERECHA || tecla == GBTK_a || tecla == GBTK_IZQUIERDA) {
                    int dir = (tecla == GBTK_d || tecla == GBTK_DERECHA) ? 1 : -1;

                    if(opcion_seleccionada == 0) { // Cambiar Paleta
                        config.paleta_tipo = (config.paleta_tipo + dir + 3) % 3;
                    }
                    else if(opcion_seleccionada == 1) { // Cambiar Resolución en el Menú
                        config.resolucion_tipo = (config.resolucion_tipo + dir + 2) % 2;
                        aplicar_resolucion_config(&config, escala_ventana);
                        obtener_resolucion_config(&config, &ancho_pantalla, &alto_pantalla);

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

                // Fila 0: PALETA
                // Mostrar número de paleta al lado

                // Fila 1: RESOLUCIÓN

                // Fila 2: VELOCIDAD
                // Representamos la velocidad de forma simple con barras o un indicador

                // Fila 3: RANKING

                // Fila 4: JUGAR

                // Fila 5: SALIR

                int menu_compacto = (alto_pantalla <= 240);
                int menu_panel_w = menu_compacto ? 240 : 280;
                int menu_panel_h = menu_compacto ? 180 : 285;
                int menu_panel_x = menu_centro_x - menu_panel_w / 2;
                int menu_panel_y = (alto_pantalla - menu_panel_h) / 2;
                int menu_fila_y = menu_panel_y + (menu_compacto ? 50 : 78);
                int menu_fila_espacio = menu_compacto ? 20 : 30;
                int menu_texto_x = menu_panel_x + (menu_compacto ? 44 : 54);
                int menu_valor_x = menu_panel_x + (menu_compacto ? 155 : 190);

                Dibujar_rect(menu_panel_x, menu_panel_y, menu_panel_w, menu_panel_h, 0);
                dibujarBorde(menu_panel_x, menu_panel_y, menu_panel_w, menu_panel_h, 14);
                Dibujar_rect(menu_panel_x + 8, menu_panel_y + 8, menu_panel_w - 16, 2, 8);
                Dibujar_rect(menu_panel_x + 8, menu_panel_y + menu_panel_h - 10, menu_panel_w - 16, 2, 8);

                int menu_titulo_x = menu_centro_x - 27;
                int menu_titulo_y = menu_panel_y + (menu_compacto ? 14 : 18);
                dibujar_matriz(menu_titulo_x + 0,  menu_titulo_y, 16, 8, letra_T_16, 4);
                dibujar_matriz(menu_titulo_x + 9,  menu_titulo_y, 16, 8, letra_E_16, 4);
                dibujar_matriz(menu_titulo_x + 18, menu_titulo_y, 16, 8, letra_T_16, 4);
                dibujar_matriz(menu_titulo_x + 27, menu_titulo_y, 16, 8, letra_R_16, 4);
                dibujar_matriz(menu_titulo_x + 36, menu_titulo_y, 16, 8, letra_I_16, 4);
                dibujar_matriz(menu_titulo_x + 45, menu_titulo_y, 16, 8, letra_S_16, 4);

                char* opciones_menu[6] =
                {
                    "PALETA",
                    "RES",
                    "VELOC",
                    "RANKING",
                    "JUGAR",
                    "SALIR"
                };

                for(int i = 0; i < 6; i++)
                {
                    int opcion_y = menu_fila_y + menu_fila_espacio * i;
                    int texto_color = 7;

                    if(i <= 3) texto_color = 4;
                    if(i == 4) texto_color = 2;

                    if(i == opcion_seleccionada)
                    {
                        Dibujar_rect(menu_panel_x + 22, opcion_y - 4, menu_panel_w - 44, 17, 8);
                        Dibujar_rect(menu_panel_x + 34, opcion_y + 2, 4, 4, 14);
                        texto_color = 14;
                    }

                    for(int j = 0; opciones_menu[i][j] != '\0'; j++)
                    {
                        dibujar_letra(opciones_menu[i][j], menu_texto_x + j * 8, opcion_y, texto_color);
                    }
                }

                if(config.paleta_tipo == 0) dibujar_letra('C', menu_valor_x, menu_fila_y, 14);
                if(config.paleta_tipo == 1) dibujar_letra('G', menu_valor_x, menu_fila_y, 14);
                if(config.paleta_tipo == 2) dibujar_letra('N', menu_valor_x, menu_fila_y, 14);

                if(config.resolucion_tipo == 0)
                {
                    dibujar_letra('C', menu_valor_x, menu_fila_y + menu_fila_espacio, 14);
                    dibujar_letra('G', menu_valor_x + 8, menu_fila_y + menu_fila_espacio, 14);
                    dibujar_letra('A', menu_valor_x + 16, menu_fila_y + menu_fila_espacio, 14);
                }
                else
                {
                    dibujar_letra('V', menu_valor_x, menu_fila_y + menu_fila_espacio, 14);
                    dibujar_letra('G', menu_valor_x + 8, menu_fila_y + menu_fila_espacio, 14);
                    dibujar_letra('A', menu_valor_x + 16, menu_fila_y + menu_fila_espacio, 14);
                }

                Dibujar_rect(menu_valor_x, menu_fila_y + menu_fila_espacio * 2 + 3, 34, 4, 8);
                Dibujar_rect(menu_valor_x, menu_fila_y + menu_fila_espacio * 2 + 3, (int)(config.velocidad_init * 20), 4, 14);

                // Acción al presionar ENTER o ESPACIO en RANKING/JUGAR/SALIR
                if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_seleccionada == 3) {
                    estadoAnteriorRanking = estado_menu;
                    estadoActual = estado_ranking;
                }
                else if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_seleccionada == 4) {
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
                else if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_seleccionada == 5) {
                    corriendo = 0;
                }
                break;

            case estado_juego:
                if(tecla == GBTK_ESCAPE) {
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

            dibujarInterfaz(tablero, piezaOrig, fila, columna,
                            nombre, longitud, puntaje,
                            config.paleta_tipo,
                            ancho_pantalla, alto_pantalla);

            int caja_w = 220;
            int caja_h = 170;
            int caja_x = (ancho_pantalla - caja_w) / 2;
            int caja_y = (alto_pantalla - caja_h) / 2;

            Dibujar_rect(caja_x, caja_y, caja_w, caja_h, 0);
            dibujarBorde(caja_x, caja_y, caja_w, caja_h, 14);

            // TITULO
            char titulo[] = "PAUSA";

            for(int i = 0; titulo[i] != '\0'; i++)
            {
                dibujar_letra(titulo[i],
                               caja_x + 80 + i * 8,
                               caja_y + 10,
                               12);
            }

            if(tecla == GBTK_ESCAPE)
            {
                estadoActual = estado_juego;
                break;
            }

            // CONTROLES
            if(tecla == GBTK_w || tecla == GBTK_ARRIBA)
                opcion_pausa = (opcion_pausa + 3) % 4;

            if(tecla == GBTK_s || tecla == GBTK_ABAJO)
                opcion_pausa = (opcion_pausa + 1) % 4;

            // OPCIONES
            char* opciones[4] =
            {
                "CONTINUAR",
                "CONFIG",
                "RANKING",
                "SALIR"
            };

            for(int i = 0; i < 4; i++)
            {
                int color = (i == opcion_pausa) ? 14 : 7;

                // FLECHA SELECTOR
                if(i == opcion_pausa)
                {
                    Dibujar_rect(caja_x + 25,
                                 caja_y + 47 + i * 25,
                                 4, 4, 14);
                }

                // TEXTO
                for(int j = 0; opciones[i][j] != '\0'; j++)
                {
                    dibujar_letra(opciones[i][j],
                                   caja_x + 45 + j * 8,
                                   caja_y + 45 + i * 25,
                                   color);
                }
            }

            // ENTER
            if(tecla == GBTK_ENTER || tecla == GBTK_ESPACIO)
            {
                if(opcion_pausa == 0)
                {
                    estadoActual = estado_juego;
                }
                else if(opcion_pausa == 1)
                {
                    opcion_configuracion = 0;
                    estadoActual = estado_configuracion;
                }
                else if(opcion_pausa == 2)
                {
                    estadoAnteriorRanking = estado_pausa;
                    estadoActual = estado_ranking;
                }
                else if(opcion_pausa == 3)
                {
                    estadoActual = estado_menu;
                }
            }

            break;
            case estado_configuracion:
            {
                dibujarInterfaz(tablero, piezaOrig, fila, columna,
                                nombre, longitud, puntaje,
                                config.paleta_tipo,
                                ancho_pantalla, alto_pantalla);

                int config_w = 260;
                int config_h = 170;
                int config_x = (ancho_pantalla - config_w) / 2;
                int config_y = (alto_pantalla - config_h) / 2;

                Dibujar_rect(config_x, config_y, config_w, config_h, 0);
                dibujarBorde(config_x, config_y, config_w, config_h, 14);

                char titulo_config[] = "CONFIG";

                for(int i = 0; titulo_config[i] != '\0'; i++)
                {
                    dibujar_letra(titulo_config[i],
                                   config_x + 105 + i * 8,
                                   config_y + 10,
                                   12);
                }

                if(tecla == GBTK_w || tecla == GBTK_ARRIBA)
                    opcion_configuracion = (opcion_configuracion + 3) % 4;

                if(tecla == GBTK_s || tecla == GBTK_ABAJO)
                    opcion_configuracion = (opcion_configuracion + 1) % 4;

                if(tecla == GBTK_d || tecla == GBTK_DERECHA || tecla == GBTK_a || tecla == GBTK_IZQUIERDA)
                {
                    int dir = (tecla == GBTK_d || tecla == GBTK_DERECHA) ? 1 : -1;

                    if(opcion_configuracion == 0)
                    {
                        config.paleta_tipo = (config.paleta_tipo + dir + 3) % 3;
                    }
                    else if(opcion_configuracion == 1)
                    {
                        config.resolucion_tipo = (config.resolucion_tipo + dir + 2) % 2;
                        aplicar_resolucion_config(&config, escala_ventana);
                        obtener_resolucion_config(&config, &ancho_pantalla, &alto_pantalla);
                    }
                    else if(opcion_configuracion == 2)
                    {
                        config.velocidad_init -= dir * 0.1;
                        if(config.velocidad_init < 0.1) config.velocidad_init = 0.1;
                        if(config.velocidad_init > 1.5) config.velocidad_init = 1.5;

                        tiempocaida = config.velocidad_init;

                        if(temporizador)
                        {
                            gbt_temporizador_destruir(temporizador);
                            temporizador = gbt_temporizador_crear(tiempocaida);
                        }
                    }

                    guardar_configuracion(&config);
                }

                char* opciones_config[4] =
                {
                    "PALETA",
                    "RES",
                    "VELOC",
                    "VOLVER"
                };

                for(int i = 0; i < 4; i++)
                {
                    int color = (i == opcion_configuracion) ? 14 : 7;
                    int y_opcion = config_y + 45 + i * 25;

                    if(i == opcion_configuracion)
                    {
                        Dibujar_rect(config_x + 25, y_opcion + 2, 4, 4, 14);
                    }

                    for(int j = 0; opciones_config[i][j] != '\0'; j++)
                    {
                        dibujar_letra(opciones_config[i][j],
                                       config_x + 45 + j * 8,
                                       y_opcion,
                                       color);
                    }

                    if(i == 0)
                    {
                        if(config.paleta_tipo == 0) dibujar_letra('C', config_x + 165, y_opcion, 14);
                        if(config.paleta_tipo == 1) dibujar_letra('G', config_x + 165, y_opcion, 14);
                        if(config.paleta_tipo == 2) dibujar_letra('N', config_x + 165, y_opcion, 14);
                    }
                    else if(i == 1)
                    {
                        if(config.resolucion_tipo == 0)
                        {
                            dibujar_letra('C', config_x + 155, y_opcion, 14);
                            dibujar_letra('G', config_x + 163, y_opcion, 14);
                            dibujar_letra('A', config_x + 171, y_opcion, 14);
                        }
                        else
                        {
                            dibujar_letra('V', config_x + 155, y_opcion, 14);
                            dibujar_letra('G', config_x + 163, y_opcion, 14);
                            dibujar_letra('A', config_x + 171, y_opcion, 14);
                        }
                    }
                    else if(i == 2)
                    {
                        Dibujar_rect(config_x + 155, y_opcion + 2, 32, 4, 8);
                        Dibujar_rect(config_x + 155, y_opcion + 2, (int)(config.velocidad_init * 20), 4, 14);
                    }
                }

                if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_configuracion == 3)
                {
                    guardar_configuracion(&config);
                    estadoActual = estado_pausa;
                }

                if(tecla == GBTK_ESCAPE)
                {
                    guardar_configuracion(&config);
                    estadoActual = estado_pausa;
                }

                break;
            }
            case estado_ranking:
            {
                dibujarInterfaz(tablero, piezaOrig, fila, columna,
                                nombre, longitud, puntaje,
                                config.paleta_tipo,
                                ancho_pantalla, alto_pantalla);

                int ranking_compacto = (ancho_pantalla <= 360 || alto_pantalla <= 240);
                int margen = ranking_compacto ? 12 : 0;
                int rw = ranking_compacto ? ancho_pantalla - margen * 2 : 400;
                int rh = ranking_compacto ? alto_pantalla - margen * 2 : 300;
                int rx = ranking_compacto ? (ancho_pantalla - rw) / 2 : 120;
                int ry = ranking_compacto ? (alto_pantalla - rh) / 2 : 60;
                int titulo_y = ry + (ranking_compacto ? 8 : 10);
                int fila_y = ry + (ranking_compacto ? 38 : 50);
                int fila_espacio = ranking_compacto ? 24 : 30;
                int puesto_x = rx + (ranking_compacto ? 18 : 30);
                int nombre_x = rx + (ranking_compacto ? 44 : 60);
                int puntaje_x = ranking_compacto ? rx + rw - 70 : rx + 250;

                Dibujar_rect(rx, ry, rw, rh, 0);
                dibujarBorde(rx, ry, rw, rh, 14);

                char titulo_rank[] = "RANKING";
                int titulo_x = rx + (rw - 56) / 2;

                for(int i = 0; titulo_rank[i] != '\0'; i++)
                {
                    dibujar_letra(titulo_rank[i],
                                   titulo_x + i * 8,
                                   titulo_y,
                                   14);
                }

                FILE *f_rank = fopen("ranking.dat", "rb");

                if(f_rank != NULL)
                {
                    RegistroRanking lista[100];
                    int total = 0;

                    while(total < 100 &&
                          fread(&lista[total],
                                sizeof(RegistroRanking),
                                1,
                                f_rank) == 1)
                    {
                        lista[total].nombre[MAX_NOMBRE - 1] = '\0';
                        total++;
                    }

                    fclose(f_rank);

                    // ORDENAR
                    for(int i = 0; i < total - 1; i++)
                    {
                        for(int j = 0; j < total - i - 1; j++)
                        {
                            if(lista[j].puntaje < lista[j + 1].puntaje)
                            {
                                RegistroRanking aux = lista[j];
                                lista[j] = lista[j + 1];
                                lista[j + 1] = aux;
                            }
                        }
                    }

                    int max_nombre_chars = (puntaje_x - nombre_x - 8) / 8;
                    if(max_nombre_chars > MAX_NOMBRE - 1)
                        max_nombre_chars = MAX_NOMBRE - 1;
                    if(max_nombre_chars < 0)
                        max_nombre_chars = 0;

                    for(int i = 0; i < total && i < 5; i++)
                    {
                        int y = fila_y + fila_espacio * i;
                        char puesto = '1' + i;

                        dibujar_letra(puesto, puesto_x, y, 14);

                        for(int n = 0;
                            lista[i].nombre[n] != '\0' && n < max_nombre_chars;
                            n++)
                        {
                            dibujar_letra(lista[i].nombre[n],
                                           nombre_x + n * 8,
                                           y,
                                           7);
                        }

                        char puntaje_texto[12];
                        snprintf(puntaje_texto, sizeof(puntaje_texto), "%d", lista[i].puntaje);

                        for(int n = 0; puntaje_texto[n] != '\0'; n++)
                        {
                            dibujar_letra(puntaje_texto[n],
                                           puntaje_x + n * 8,
                                           y,
                                           12);
                        }
                    }
                }

                if(tecla == GBTK_ESCAPE)
                {
                    estadoActual = estadoAnteriorRanking;
                }

                break;
            }
           case estado_gameover:
                dibujarInterfaz(tablero, piezaOrig, fila, columna,
                                nombre, longitud, puntaje,
                                config.paleta_tipo,
                                ancho_pantalla, alto_pantalla);
                // Letrero "GAME OVER" centrado dinámicamente
                int go_panel_w = 220;
                int go_panel_h = 140;
                int go_panel_x = (ancho_pantalla - go_panel_w) / 2;
                int go_panel_y = (alto_pantalla - go_panel_h) / 2;

                Dibujar_rect(go_panel_x, go_panel_y, go_panel_w, go_panel_h, 0);
                dibujarBorde(go_panel_x, go_panel_y, go_panel_w, go_panel_h, 14);

                char game_texto[] = "GAME";
                char over_texto[] = "OVER";
                char puntaje_texto[] = "PUNTAJE";
                char volver_texto[] = "ENTER MENU";
                char puntaje_numero[12];

                snprintf(puntaje_numero, sizeof(puntaje_numero), "%d", puntaje);

                for(int i = 0; game_texto[i] != '\0'; i++)
                {
                    dibujar_letra(game_texto[i], go_panel_x + 94 + i * 8, go_panel_y + 18, 4);
                }

                for(int i = 0; over_texto[i] != '\0'; i++)
                {
                    dibujar_letra(over_texto[i], go_panel_x + 94 + i * 8, go_panel_y + 38, 12);
                }

                for(int i = 0; puntaje_texto[i] != '\0'; i++)
                {
                    dibujar_letra(puntaje_texto[i], go_panel_x + 45 + i * 8, go_panel_y + 72, 14);
                }

                for(int i = 0; puntaje_numero[i] != '\0'; i++)
                {
                    dibujar_letra(puntaje_numero[i], go_panel_x + 125 + i * 8, go_panel_y + 72, 7);
                }

                for(int i = 0; volver_texto[i] != '\0'; i++)
                {
                    dibujar_letra(volver_texto[i], go_panel_x + 70 + i * 8, go_panel_y + 105, 7);
                }

                if(tecla == GBTK_ESPACIO || tecla == GBTK_ENTER) {
                    // === NUEVO: GUARDAMOS EN EL ARCHIVO BINARIO ANTES DE REINICIAR ===
                    registrar_en_ranking(nombre, puntaje);

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
