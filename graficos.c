#include <stdio.h>
#include "graficos.h"
#include "pieza.h"
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
void dibujar_linea(int x, int y, int h ,int color);
void dibujarInterfaz();

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
    for (int y = 0; y < ALTO_VENTANA; y++) {
        for (int x = 0; x < ANCHO_VENTANA; x++) {
                gbt_dibujar_pixel(x, y, 9); // verde oscuro

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

void dibujar_linea(int x, int y, int h ,int color)
{
    for(int j=y;j< h; j++)
    {
        gbt_dibujar_pixel(x,j,color);
    }
}

void dibujarInterfaz(int** tablero, Pieza pieza, int fila, int columna, char Nombre[], int longitud, int puntaje, int paleta_tipo)
{
        int offsetX = (ANCHO_VENTANA - (ANCHO_T * TAM_BLOQUE)) / 2;
        int offsetY = (ALTO_VENTANA - (ALTO_T * TAM_BLOQUE)) / 2;
        dibujarFondo(9);
        dibujar_linea(offsetX-2, 0, 200, 4);
        dibujar_linea(offsetX-1, 0, 200, 4);
        dibujar_linea((offsetX + (ANCHO_T * TAM_BLOQUE)) , 0,200,4);
        dibujar_linea((offsetX + (ANCHO_T * TAM_BLOQUE))+1, 0,200,4);
        dibujarTablero(tablero, offsetX, offsetY, paleta_tipo);
        dibujarPieza(pieza, offsetX + columna * TAM_BLOQUE, offsetY + fila * TAM_BLOQUE, paleta_tipo);


        int x = 2;
        int y = 2;
      // USER
       dibujar_matriz(x ,  y, 8, 8, letra_J, 4);
       dibujar_matriz(x+6 ,  y, 8, 8, letra_U, 4);
       dibujar_matriz(x+12 ,  y, 8, 8, letra_G, 4);
       dibujar_matriz(x+18 ,  y, 8, 8, letra_A, 4);
       dibujar_matriz(x+26 ,  y, 8, 8, letra_D, 4);
       dibujar_matriz(x+32,  y, 8, 8, letra_O, 4);
       dibujar_matriz(x+40 ,  y, 8, 8, letra_R, 4);
       dibujar_matriz(x+46 ,  y, 8, 8, letra_signopuntuacion, 4);

       x= 52;
       // DIBUJAR USUARIO INGRESADO
       for(int i=0; i<longitud; i++)
       {

           dibujar_letra(Nombre[i],x,y);
           x= x + 8;
       }

       // SCORE

       x = 2;
       y=180;
       dibujar_matriz(x,y,8,8,letra_S,4);
       dibujar_matriz(x+8,y,8,8,letra_C,4);
       dibujar_matriz(x+16,y,8,8,letra_O,4);
       dibujar_matriz(x+24,y,8,8,letra_R,4);
       dibujar_matriz(x+32,y,8,8,letra_E,4);
       dibujar_matriz(x+40,y,8,8,letra_signopuntuacion,4);




        // PASAR PUNTAJE A VECTOR PARA PODER DIBUJAR
       int (*numeros[10])[8] = {
            numero_0,
            numero_1,
            numero_2,
            numero_3,
            numero_4,
            numero_5,
            numero_6,
            numero_7,
            numero_8,
            numero_9
        };
       int mil = puntaje / 1000;
       int cien = (puntaje / 100) % 10;
       int diez = (puntaje / 10) % 10;
       int uno = puntaje % 10;

        x = 50;
        y = 180;

        dibujar_matriz(x,  y, 8, 8, numeros[mil], 4);
        dibujar_matriz(x+8,  y, 8, 8, numeros[cien], 4);
        dibujar_matriz(x+16, y, 8, 8, numeros[diez], 4);
        dibujar_matriz(x+24, y, 8, 8, numeros[uno], 4);


}

void guardar_configuracion(Configuracion *config) {
    FILE *archivo = fopen("config.dat", "wb");
    if (archivo != NULL) {
        fwrite(config, sizeof(Configuracion), 1, archivo);
        fclose(archivo);
    }
}

void cargar_configuracion(Configuracion *config) {
    FILE *archivo = fopen("config.dat", "rb");
    if (archivo != NULL) {
        fread(config, sizeof(Configuracion), 1, archivo);
        fclose(archivo);
    } else {
        // Valores por defecto iniciales si el jugador abre el juego por primera vez
        config->paleta_tipo = 0;
        config->resolucion_tipo = 0;
        config->velocidad_init = 0.5;
        guardar_configuracion(config);
    }
}
