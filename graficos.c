#include <stdio.h>
#include "graficos.h"

tGBT_ColorRGB paletaCGA[CANT_COLORES] = {

    /// 0-15: Colores CGA (16 colores)
    {0x00, 0x00, 0x00}, // 0:   Negro
    {0x00, 0x00, 0xAA}, // 1:   Azul
    {0x00, 0xAA, 0x00}, // 2:   Verde
    {0x00, 0xAA, 0xAA}, // 3:   Cian
    {0xAA, 0x00, 0x00}, // 4:   Rojo
    {0xAA, 0x00, 0xAA}, // 5:   Magenta
    {0xAA, 0x55, 0x00}, // 6:   Marron
    {0xAA, 0xAA, 0xAA}, // 7:   Gris claro
    {0x55, 0x55, 0x55}, // 8:   Gris oscuro
    {0x55, 0x55, 0xFF}, // 9:   Azul brillante
    {0x55, 0xFF, 0x55}, // 10:  Verde brillante
    {0x55, 0xFF, 0xFF}, // 11:  Cian brillante
    {0xFF, 0x55, 0x55}, // 12:  Rojo brillante
    {0xFF, 0x55, 0xFF}, // 13:  Magenta brillante
    {0xFF, 0xFF, 0x55}, // 14:  Amarillo
    {0xFF, 0xFF, 0xFF}  // 15:  Usado como transparente por GBT
};


void Dibujar_rect(int x, int y, int w, int h, int color);
void dibujarBorde(int x, int y, int w, int h, int color);
void dibujarFondo();
void dibujar_matriz(int x, int y, int filas, int cols, int matriz[filas][cols], int color);

void Dibujar_rect(int x, int y, int w, int h, int color)
{
    for (int i = x; i < x + w; i++)
        for (int j = y; j < y + h; j++)
            gbt_dibujar_pixel(i, j, color);
}

//Prueba//
void dibujarBorde(int x, int y, int w, int h, int color) {
    for (int i = x; i < x + w; i++) {
        gbt_dibujar_pixel(i, y, color);
        gbt_dibujar_pixel(i, y + h - 1, color);
    }

    for (int j = y; j < y + h; j++) {
        gbt_dibujar_pixel(x, j, color);
        gbt_dibujar_pixel(x + w - 1, j, color);
    }
}

void dibujarFondo() {
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
            if ((x/10 + y/10) % 2 == 0)
                gbt_dibujar_pixel(x, y, 9); // verde oscuro
            else
                gbt_dibujar_pixel(x, y, 9); // verde claro
        }
    }
}

void dibujar_matriz(int x, int y, int filas, int cols, int matriz[filas][cols], int color)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matriz[i][j] == 1)
            {
                gbt_dibujar_pixel(x + j, y + i, color);
            }
        }
    }
}
