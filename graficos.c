#include <stdio.h>
#include <string.h>
#include "graficos.h"
#include "pieza.h"
#include "presentacion.h"

#define MAX_REGISTROS_RANKING 100
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

static int limite_ancho_dibujo = ANCHO_VENTANA;
static int limite_alto_dibujo = ALTO_VENTANA;

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


void Dibujar_rect(int x, int y, int w, int h, int color);
void dibujarBorde(int x, int y, int w, int h, int color);
void dibujarFondo();
void dibujar_matriz(int x, int y, int filas, int cols, int matriz[filas][cols], int color);
void dibujar_linea(int x, int y, int h ,int color);
void dibujarInterfaz();

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

    for (int i = x0; i < x1; i++)
        for (int j = y0; j < y1; j++)
            gbt_dibujar_pixel((uint16_t)i, (uint16_t)j, (uint8_t)color);
}

//Prueba//
void dibujarBorde(int x, int y, int w, int h, int color) {
    if(w <= 0 || h <= 0)
        return;

    Dibujar_rect(x, y, w, 1, color);
    Dibujar_rect(x, y + h - 1, w, 1, color);
    Dibujar_rect(x, y, 1, h, color);
    Dibujar_rect(x + w - 1, y, 1, h, color);
}

void dibujarFondo() {
    Dibujar_rect(0, 0, limite_ancho_dibujo, limite_alto_dibujo, 9);
}

void dibujar_matriz(int x, int y, int filas, int cols, int matriz[filas][cols], int color)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matriz[i][j] == 1)
            {
                dibujar_pixel_seguro(x + j, y + i, color);
            }
        }
    }
}

void dibujar_linea(int x, int y, int h ,int color)
{
    for(int j=y;j< h; j++)
    {
        dibujar_pixel_seguro(x, j, color);
    }
}

void dibujarInterfaz(int** tablero, Pieza piezaActual, int filaLogica, int colLogica,
                     char* nombre, int longitud, int puntaje, int paleta_tipo,
                     int ancho_pantalla, int alto_pantalla)
{
    // 1. Calcular el tamaño total del tablero en píxeles
    int ancho_tablero_px = ANCHO_T * TAM_BLOQUE;
    int alto_tablero_px = ALTO_T * TAM_BLOQUE;

    // 2. Centrar el tablero dinámicamente en la pantalla actual
    int offsetX = (ancho_pantalla - ancho_tablero_px) / 2;
    int offsetY = (alto_pantalla - alto_tablero_px) / 2;

    // ==========================================
    // 3. DIBUJAR LÍMITES DEL TABLERO (Líneas Rojas)
    // ==========================================
    // Línea izquierda (un rectángulo finito vertical de ancho 2)
    Dibujar_rect(offsetX - 2, offsetY, 2, alto_tablero_px, 4);

    // Línea derecha (un rectángulo finito vertical de ancho 2)
    Dibujar_rect(offsetX + ancho_tablero_px, offsetY, 2, alto_tablero_px, 4);

    // Piso del tablero (un rectángulo finito horizontal de alto 2)
    Dibujar_rect(offsetX - 2, offsetY + alto_tablero_px, ancho_tablero_px + 4, 2, 4);

    // ==========================================
    // 4. DIBUJAR BLOQUES FIJOS DEL TABLERO
    // ==========================================
    dibujarTablero(tablero, offsetX, offsetY, paleta_tipo);

    // ==========================================
    // 5. DIBUJAR PIEZA EN CAÍDA
    // ==========================================
    int pieza_x = offsetX + (colLogica * TAM_BLOQUE);
    int pieza_y = offsetY + (filaLogica * TAM_BLOQUE);

    dibujarPieza(piezaActual, pieza_x, pieza_y, paleta_tipo);

    // ==========================================
    // 6. TEXTOS DE INTERFAZ (SCORE Y NOMBRE)
    // ==========================================

    // --- PANEL IZQUIERDO: SCORE ---
    int score_label_x = offsetX - 70;
    int score_y = offsetY + 20;

    if (score_label_x > 5) {
        // Dibuja la palabra "S C O R E" usando tu función en color Rojo (4)
        dibujar_letra('S', score_label_x + 0,  score_y, 4);
        dibujar_letra('C', score_label_x + 8,  score_y, 4);
        dibujar_letra('O', score_label_x + 16, score_y, 4);
        dibujar_letra('R', score_label_x + 24, score_y, 4);
        dibujar_letra('E', score_label_x + 32, score_y, 4);

        int score_valores_y = score_y + 12;

        // Descomponemos el puntaje en 4 dígitos
        int digito1 = (puntaje / 1000) % 10;
        int digito2 = (puntaje / 100) % 10;
        int digito3 = (puntaje / 10) % 10;
        int digito4 = puntaje % 10;

        // Dibujamos los números dinámicos convirtiendo el int a char ('0' + numero)
        dibujar_letra('0' + digito1, score_label_x + 0,  score_valores_y, 12); // Rojo brillante
        dibujar_letra('0' + digito2, score_label_x + 8,  score_valores_y, 12);
        dibujar_letra('0' + digito3, score_label_x + 16, score_valores_y, 12);
        dibujar_letra('0' + digito4, score_label_x + 24, score_valores_y, 12);
    }

    // --- PANEL DERECHO: NOMBRE DE USUARIO ---
    int nombre_x = offsetX + ancho_tablero_px + 20;
    int nombre_y = offsetY + 20;

    if (nombre_x < ancho_pantalla - 40) {
        // Recorremos la cadena imprimiendo directo con tu función en color Amarillo (14)
        for (int i = 0; i < longitud; i++) {
            dibujar_letra(nombre[i], nombre_x + (i * 8), nombre_y, 14);
        }
    }
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
        config->resolucion_tipo = 1;
        config->velocidad_init = 0.5;
        guardar_configuracion(config);
    }
}
void registrar_en_ranking(const char* nombre, int puntaje) {
    // Si el nombre está vacío, no guardamos basura
    if (nombre == NULL || nombre[0] == '\0') return;

    RegistroRanking nuevo_registro;
    // Copiamos el nombre de forma segura
    snprintf(nuevo_registro.nombre, MAX_NOMBRE, "%s", nombre);
    nuevo_registro.puntaje = puntaje;

    RegistroRanking registros[MAX_REGISTROS_RANKING];
    int total = 0;
    int encontrado = -1;

    FILE *archivo = fopen("ranking.dat", "rb");
    if (archivo != NULL) {
        while(total < MAX_REGISTROS_RANKING &&
              fread(&registros[total], sizeof(RegistroRanking), 1, archivo) == 1)
        {
            registros[total].nombre[MAX_NOMBRE - 1] = '\0';

            if(strcmp(registros[total].nombre, nuevo_registro.nombre) == 0)
            {
                encontrado = total;
            }

            total++;
        }

        fclose(archivo);
    }

    if(encontrado >= 0)
    {
        int nuevo_total = 0;
        int reemplazado = 0;

        for(int i = 0; i < total; i++)
        {
            if(strcmp(registros[i].nombre, nuevo_registro.nombre) == 0)
            {
                if(!reemplazado)
                {
                    registros[nuevo_total] = nuevo_registro;
                    nuevo_total++;
                    reemplazado = 1;
                }
            }
            else
            {
                registros[nuevo_total] = registros[i];
                nuevo_total++;
            }
        }

        total = nuevo_total;
    }
    else if(total < MAX_REGISTROS_RANKING)
    {
        registros[total] = nuevo_registro;
        total++;
    }

    archivo = fopen("ranking.dat", "wb");
    if (archivo != NULL) {
        fwrite(registros, sizeof(RegistroRanking), total, archivo);
        fclose(archivo);
    }
}
