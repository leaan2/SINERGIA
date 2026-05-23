#include <stdio.h>
#include <stdlib.h>
#include "presentacion.h"
#include "GBT/gbt.h"
#include "pieza.h"

void dibujar_letra(char c, int x, int y, int color);
void dibujarPantalla (int ancho_p, int alto_p);
int Presentacion(char nombre[], int ancho_pantalla, int alto_pantalla);
void dibujar_texto(const char *texto, int x, int y, int color);

// --- RECIBE EL ANCHO Y ALTO DINÁMICOS ---
void dibujarPantalla(int ancho_p, int alto_p) {
    // fondo
    Dibujar_rect(0, 0, ancho_p, alto_p, 9);

    // 1. Calculamos el tamaño del contenedor principal proporcionalmente
    int caja_w = (ancho_p * 62) / 100; 
    int caja_h = (alto_p * 60) / 100; 

    // Centramos la caja principal en la pantalla actual
    int caja_x = (ancho_p - caja_w) / 2;
    int caja_y = (alto_p - caja_h) / 2;

    // rectángulo azul principal
    Dibujar_rect(caja_x, caja_y, caja_w, caja_h, 9); // azul

    // borde blanco externo
    dibujarBorde(caja_x, caja_y, caja_w, caja_h, 0);

    // borde interior separado por 5 píxeles
    dibujarBorde(caja_x + 5, caja_y + 5, caja_w - 10, caja_h - 10, 15);

    // --- CÁLCULO DE CAJAS NEGRAS INTERNAS PARA TEXTOS ---
    // Título TETRIS
    int caja_tetris_w = (caja_w * 60) / 100;
    int caja_tetris_h = (caja_h * 12) / 100;
    int caja_tetris_x = caja_x + (caja_w - caja_tetris_w) / 2;
    int caja_tetris_y = caja_y + (caja_h * 16) / 100;
    Dibujar_rect(caja_tetris_x, caja_tetris_y, caja_tetris_w, caja_tetris_h, 0);

    // Caja USER
    int caja_user_w = (caja_w * 50) / 100;
    int caja_user_h = (caja_h * 8) / 100;
    int caja_user_x = caja_x + (caja_w - caja_user_w) / 2;
    int caja_user_y = caja_y + (caja_h * 50) / 100;
    Dibujar_rect(caja_user_x, caja_user_y, caja_user_w, caja_user_h, 0);

    // Caja "PRESS ENTER"
    int caja_press_w = (caja_w * 50) / 100;
    int caja_press_h = (caja_h * 8) / 100;
    int caja_press_x = caja_x + (caja_w - caja_press_w) / 2;
    int caja_press_y = caja_y + (caja_h * 83) / 100;
    Dibujar_rect(caja_press_x, caja_press_y, caja_press_w, caja_press_h, 0);
}

void dibujar_letra(char c, int x, int y, int color)
{
    // Si viene en minúscula, la pasamos a mayúscula para que entre en el switch
    if (c >= 'a' && c <= 'z') {
        c = c - 32;
    }

    switch (c)
    {
        case 'A': dibujar_matriz(x, y, 8, 8, letra_A, color); break;
        case 'B': dibujar_matriz(x, y, 8, 8, letra_B, color); break;
        case 'C': dibujar_matriz(x, y, 8, 8, letra_C, color); break;
        case 'D': dibujar_matriz(x, y, 8, 8, letra_D, color); break;
        case 'E': dibujar_matriz(x, y, 8, 8, letra_E, color); break;
        case 'F': dibujar_matriz(x, y, 8, 8, letra_F, color); break;
        case 'G': dibujar_matriz(x, y, 8, 8, letra_G, color); break;
        case 'H': dibujar_matriz(x, y, 8, 8, letra_H, color); break;
        case 'I': dibujar_matriz(x, y, 8, 8, letra_I, color); break;
        case 'J': dibujar_matriz(x, y, 8, 8, letra_J, color); break;
        case 'K': dibujar_matriz(x, y, 8, 8, letra_K, color); break;
        case 'L': dibujar_matriz(x, y, 8, 8, letra_L, color); break;
        case 'M': dibujar_matriz(x, y, 8, 8, letra_M, color); break;
        case 'N': dibujar_matriz(x, y, 8, 8, letra_N, color); break;
        case 'O': dibujar_matriz(x, y, 8, 8, letra_O, color); break;
        case 'P': dibujar_matriz(x, y, 8, 8, letra_P, color); break;
        case 'Q': dibujar_matriz(x, y, 8, 8, letra_Q, color); break;
        case 'R': dibujar_matriz(x, y, 8, 8, letra_R, color); break;
        case 'S': dibujar_matriz(x, y, 8, 8, letra_S, color); break;
        case 'T': dibujar_matriz(x, y, 8, 8, letra_T, color); break;
        case 'U': dibujar_matriz(x, y, 8, 8, letra_U, color); break;
        case 'V': dibujar_matriz(x, y, 8, 8, letra_V, color); break;
        case 'W': dibujar_matriz(x, y, 8, 8, letra_W, color); break;
        case 'X': dibujar_matriz(x, y, 8, 8, letra_X, color); break;
        case 'Y': dibujar_matriz(x, y, 8, 8, letra_Y, color); break;
        case 'Z': dibujar_matriz(x, y, 8, 8, letra_Z, color); break;
        case '_': dibujar_matriz(x, y, 8, 8, letra_guionbajo, color); break;

        // Soporte para números usando tus matrices
        case '0': dibujar_matriz(x, y, 8, 8, numero_0, color); break;
        case '1': dibujar_matriz(x, y, 8, 8, numero_1, color); break;
        case '2': dibujar_matriz(x, y, 8, 8, numero_2, color); break;
        case '3': dibujar_matriz(x, y, 8, 8, numero_3, color); break;
        case '4': dibujar_matriz(x, y, 8, 8, numero_4, color); break;
        case '5': dibujar_matriz(x, y, 8, 8, numero_5, color); break;
        case '6': dibujar_matriz(x, y, 8, 8, numero_6, color); break;
        case '7': dibujar_matriz(x, y, 8, 8, numero_7, color); break;
        case '8': dibujar_matriz(x, y, 8, 8, numero_8, color); break;
        case '9': dibujar_matriz(x, y, 8, 8, numero_9, color); break;
    }
}

int Presentacion(char nombre[], int ancho_pantalla, int alto_pantalla)
{
    EstadoJuego estado_programa = estado_menu;
    int mostrar_palabra = 1;
    int longitud = 0;

    // aplicar paleta
    if (gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888) != 0) {
        printf("Error aplicando paleta\n");
        return -1;
    }

    tGBT_Temporizador *temporizador = gbt_temporizador_crear(0.5);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador para los dibujos: %s\n", gbt_obtener_log());
        return -1;
    }

    while (estado_programa != estado_juego)
    {
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
        if (gbt_tecla_presionada(GBTK_ENTER) && longitud > 0)
        {
            estado_programa = estado_juego;
            nombre[longitud] = '\0';
        }

        // FONDO
        gbt_borrar_backbuffer(0); // negro

        // Dibujamos la pantalla pasándole el tamaño actual
        dibujarPantalla(ancho_pantalla, alto_pantalla);

        // --- CÁLCULO DINÁMICO DE POSICIÓN DE LETRAS ---
        int caja_w = (ancho_pantalla * 62) / 100;
        int caja_h = (alto_pantalla * 60) / 100;
        int caja_x = (ancho_pantalla - caja_w) / 2;
        int caja_y = (alto_pantalla - caja_h) / 2;

        // 1. TITULO CENTRADO DINÁMICAMENTE (Mantenemos tus fuentes especiales de 16x8 de alto para TETRIS)
        int titulo_x = caja_x + (caja_w - 53) / 2;
        int titulo_y = caja_y + (caja_h * 16) / 100 + (caja_h * 12 / 100 - 16) / 2;

        dibujar_matriz(titulo_x + 0,  titulo_y, 16, 8, letra_T_16, 4);
        dibujar_matriz(titulo_x + 9,  titulo_y, 16, 8, letra_E_16, 4);
        dibujar_matriz(titulo_x + 18, titulo_y, 16, 8, letra_T_16, 4);
        dibujar_matriz(titulo_x + 27, titulo_y, 16, 8, letra_R_16, 4);
        dibujar_matriz(titulo_x + 36, titulo_y, 16, 8, letra_I_16, 4);
        dibujar_matriz(titulo_x + 45, titulo_y, 16, 8, letra_S_16, 4);

        // 2. USER CENTRADO DINÁMICAMENTE
        int user_box_w = (caja_w * 50) / 100;
        int user_box_y = caja_y + (caja_h * 50) / 100;

        int texto_user_x = caja_x + (caja_w - user_box_w) / 2 + 10;
        int texto_user_y = user_box_y + ((caja_h * 8 / 100) - 8) / 2;

        // Simplificado con tu función dibujar_texto!
        dibujar_texto("USER:", texto_user_x, texto_user_y, 4);

        if (gbt_temporizador_consumir(temporizador))
        {
            mostrar_palabra = !mostrar_palabra;
        }

        if (mostrar_palabra && longitud < MAX_NOMBRE) {
            dibujar_letra('_', texto_user_x + 40 + longitud * 8, texto_user_y, 4);
        }

        // Entrada teclado
        if (((tecla >= 'a' && tecla <= 'z') || (tecla >= 'A' && tecla <= 'Z')) && longitud < MAX_NOMBRE - 1)
        {
            nombre[longitud] = tecla; // Guardamos el char nativo, dibujar_letra se encarga de pasarlo a mayúscula
            longitud++;
        }
        if (tecla == GBTK_RETROCESO && longitud > 0)
        {
            longitud--;
        }

        // Renderizar caracteres ingresados usando el cuarto parámetro de color (Rojo 4)
        for (int i = 0; i < longitud; i++)
        {
            dibujar_letra(nombre[i], texto_user_x + 40 + i * 8, texto_user_y, 4);
        }

        // 3. PRESS ENTER CENTRADO DINÁMICAMENTE (¡Se removió press_box_w sin usar!)
        int press_box_y = caja_y + (caja_h * 83) / 100;
        int press_x = caja_x + (caja_w - 88) / 2; 
        int press_y = press_box_y + ((caja_h * 8 / 100) - 8) / 2;

        dibujar_texto("PRESS", press_x, press_y, 4);

        if (mostrar_palabra) {
            dibujar_texto("ENTER", press_x + 48, press_y, 4);
        }

        gbt_volcar_backbuffer();
    }

    gbt_temporizador_destruir(temporizador);
    return longitud;
}

void dibujar_texto(const char *texto, int x, int y, int color) {
    for (int i = 0; texto[i] != '\0'; i++) {
        dibujar_letra(texto[i], x + (i * 8), y, color);
    }
}
