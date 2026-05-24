//Dibujo de bloques, piezas, tablero, interfaz y texto/letras//

#include "render.h"

#include "graficos.h"
#include "letras.h"

void dibujarBloque(int x, int y, uint8_t color_original, int paleta_tipo)
{
    if(color_original == 0)
        return;

    uint8_t color_base = color_original;
    uint8_t brillo = 15;
    uint8_t sombra = 0;
    uint8_t centro = color_original;

    if(color_base == 1)
    {
        color_base = 9;
        centro = 9;
    }
    else if(color_base == 8)
    {
        color_base = 7;
        centro = 7;
    }

    if(paleta_tipo == 1)
    {
        color_base = 2;
        brillo = 10;
        sombra = 0;
        centro = 2;
    }
    else if(paleta_tipo == 2)
    {
        brillo = 15;
        sombra = 8;
    }

    Dibujar_rect(x, y, TAM_BLOQUE, TAM_BLOQUE, color_base);
    Dibujar_rect(x, y, TAM_BLOQUE, 2, brillo);
    Dibujar_rect(x, y, 2, TAM_BLOQUE, brillo);
    Dibujar_rect(x, y + TAM_BLOQUE - 2, TAM_BLOQUE, 2, sombra);
    Dibujar_rect(x + TAM_BLOQUE - 2, y, 2, TAM_BLOQUE, sombra);
    Dibujar_rect(x + 3, y + 3, TAM_BLOQUE - 6, TAM_BLOQUE - 6, centro);
    Dibujar_rect(x + 2, y + 2, 2, 2, 15);
}

void dibujarTablero(int** tablero, int offsetX, int offsetY, int paleta_tipo)
{
    for(int i = FILAS_OCULTAS_T; i < ALTO_MATRIZ_T; i++)
    {
        for(int j = 0; j < ANCHO_T; j++)
        {
            if(tablero[i][j] != 0)
            {
                dibujarBloque(
                    offsetX + j * TAM_BLOQUE,
                    offsetY + (i - FILAS_OCULTAS_T) * TAM_BLOQUE,
                    (uint8_t)tablero[i][j],
                    paleta_tipo
                );
            }
        }
    }
}

static void dibujarVistaPrevia(Pieza pieza, int x, int y, int paleta_tipo)
{
    int min_fila = TAM;
    int max_fila = -1;
    int min_columna = TAM;
    int max_columna = -1;

    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            if(pieza.forma[i][j] == 1)
            {
                if(i < min_fila)
                    min_fila = i;

                if(i > max_fila)
                    max_fila = i;

                if(j < min_columna)
                    min_columna = j;

                if(j > max_columna)
                    max_columna = j;
            }
        }
    }

    if(max_fila < 0)
        return;

    int ancho_pieza = (max_columna - min_columna + 1) * TAM_BLOQUE;
    int alto_pieza = (max_fila - min_fila + 1) * TAM_BLOQUE;
    int origen_x = x + (TAM * TAM_BLOQUE - ancho_pieza) / 2 - min_columna * TAM_BLOQUE;
    int origen_y = y + (TAM * TAM_BLOQUE - alto_pieza) / 2 - min_fila * TAM_BLOQUE;

    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++)
            if(pieza.forma[i][j] == 1)
                dibujarBloque(origen_x + j * TAM_BLOQUE, origen_y + i * TAM_BLOQUE, pieza.color, paleta_tipo);
}

void dibujarInterfaz(int** tablero, Pieza piezaActual, Pieza piezaSiguiente, int filaLogica, int colLogica,
                     char* nombre, int longitud, int puntaje, int paleta_tipo,
                     int ancho_pantalla, int alto_pantalla)
{
    int ancho_tablero_px = ANCHO_T * TAM_BLOQUE;
    int alto_tablero_px = ALTO_T * TAM_BLOQUE;

    int offsetX = (ancho_pantalla - ancho_tablero_px) / 2;
    int offsetY = (alto_pantalla - alto_tablero_px) / 2;

    Dibujar_rect(offsetX - 2, offsetY, 2, alto_tablero_px, 4);
    Dibujar_rect(offsetX + ancho_tablero_px, offsetY, 2, alto_tablero_px, 4);
    Dibujar_rect(offsetX - 2, offsetY + alto_tablero_px, ancho_tablero_px + 4, 2, 4);

    dibujarTablero(tablero, offsetX, offsetY, paleta_tipo);

    for(int i = 0; i < TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            int fila_visible = filaLogica + i - FILAS_OCULTAS_T;

            if(piezaActual.forma[i][j] == 1 && fila_visible >= 0 && fila_visible < ALTO_T)
            {
                dibujarBloque(
                    offsetX + (colLogica + j) * TAM_BLOQUE,
                    offsetY + fila_visible * TAM_BLOQUE,
                    piezaActual.color,
                    paleta_tipo
                );
            }
        }
    }

    int score_label_x = offsetX - 70;
    int score_y = offsetY + 20;

    if(score_label_x > 5)
    {
        dibujar_texto("SCORE", score_label_x, score_y, 4);

        int score_valores_y = score_y + 12;
        int digito1 = (puntaje / 1000) % 10;
        int digito2 = (puntaje / 100) % 10;
        int digito3 = (puntaje / 10) % 10;
        int digito4 = puntaje % 10;

        dibujar_letra('0' + digito1, score_label_x, score_valores_y, 12);
        dibujar_letra('0' + digito2, score_label_x + 8, score_valores_y, 12);
        dibujar_letra('0' + digito3, score_label_x + 16, score_valores_y, 12);
        dibujar_letra('0' + digito4, score_label_x + 24, score_valores_y, 12);
    }

    int nombre_x = offsetX + ancho_tablero_px + 20;
    int nombre_y = offsetY + 20;

    if(nombre_x < ancho_pantalla - 40)
        for(int i = 0; i < longitud; i++)
            dibujar_letra(nombre[i], nombre_x + (i * 8), nombre_y, 14);

    int preview_x = nombre_x;
    int preview_y = nombre_y + 28;

    if(preview_x + TAM * TAM_BLOQUE + 8 < ancho_pantalla &&
       preview_y + TAM * TAM_BLOQUE + 8 < alto_pantalla)
    {
        dibujar_texto("PROX", preview_x, preview_y - 12, 4);
        Dibujar_rect(preview_x - 4, preview_y - 4, TAM * TAM_BLOQUE + 8, TAM * TAM_BLOQUE + 8, 0);
        dibujarBorde(preview_x - 4, preview_y - 4, TAM * TAM_BLOQUE + 8, TAM * TAM_BLOQUE + 8, 14);
        dibujarVistaPrevia(piezaSiguiente, preview_x, preview_y, paleta_tipo);
    }
}

void dibujar_letra(char c, int x, int y, int color)
{
    if(c >= 'a' && c <= 'z')
        c = c - 32;

    switch(c)
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

void dibujar_texto(const char *texto, int x, int y, int color)
{
    for(int i = 0; texto[i] != '\0'; i++)
        dibujar_letra(texto[i], x + (i * 8), y, color);
}
