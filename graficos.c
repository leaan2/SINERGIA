// Paleta de colores//
// Dibujar lineas, rectangulos, lineas, matrices, bordes.//

#include "graficos.h"
#include "pieza.h"

//Paleta de colores

tGBT_ColorRGB paletaCGA[CANT_COLORES] = {
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0xAA},
    {0x00, 0xAA, 0x00},
    {0x00, 0xAA, 0xAA},
    {0xAA, 0x00, 0x00},
    {0xAA, 0x00, 0xAA},
    {0xAA, 0x55, 0x00},
    {0xAA, 0xAA, 0xAA},
    {0x55, 0x55, 0x55},
    {0x55, 0x55, 0xFF},
    {0x55, 0xFF, 0x55},
    {0x55, 0xFF, 0xFF},
    {0xFF, 0x55, 0x55},
    {0xFF, 0x55, 0xFF},
    {0xFF, 0xFF, 0x55},
    {0xFF, 0xFF, 0xFF}
};

static int limite_ancho_dibujo = ANCHO_VENTANA;
static int limite_alto_dibujo = ALTO_VENTANA;

// dibujar pixeles

void configurar_limites_dibujo(int ancho, int alto)
{
    if(ancho > 0)
        limite_ancho_dibujo = ancho;

    if(alto > 0)
        limite_alto_dibujo = alto;
}

static void dibujar_pixel_seguro(int x, int y, int color)
{
    if(x < 0 || y < 0)
        return;

    if(x >= limite_ancho_dibujo || y >= limite_alto_dibujo)
        return;

    gbt_dibujar_pixel((uint16_t)x, (uint16_t)y, (uint8_t)color);
}

void Dibujar_rect(int x, int y, int w, int h, int color)
{
    if(w <= 0 || h <= 0)
        return;

    int x0 = (x < 0) ? 0 : x;
    int y0 = (y < 0) ? 0 : y;
    int x1 = x + w;
    int y1 = y + h;

    if(x1 > limite_ancho_dibujo)
        x1 = limite_ancho_dibujo;

    if(y1 > limite_alto_dibujo)
        y1 = limite_alto_dibujo;

    if(x0 >= x1 || y0 >= y1)
        return;

    for(int i = x0; i < x1; i++)
        for(int j = y0; j < y1; j++)
            gbt_dibujar_pixel((uint16_t)i, (uint16_t)j, (uint8_t)color);
}

void dibujarBorde(int x, int y, int w, int h, int color)
{
    if(w <= 0 || h <= 0)
        return;

    Dibujar_rect(x, y, w, 1, color);
    Dibujar_rect(x, y + h - 1, w, 1, color);
    Dibujar_rect(x, y, 1, h, color);
    Dibujar_rect(x + w - 1, y, 1, h, color);
}


void dibujar_matriz(int x, int y, int filas, int cols, int matriz[filas][cols], int color)
{
    for(int i = 0; i < filas; i++)
        for(int j = 0; j < cols; j++)
            if(matriz[i][j] == 1)
                dibujar_pixel_seguro(x + j, y + i, color);
}

void dibujar_linea(int x, int y, int h, int color)
{
    for(int j = y; j < h; j++)
        dibujar_pixel_seguro(x, j, color);
}
