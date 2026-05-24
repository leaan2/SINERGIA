//Presentacion//
//Pantalla//

#include "presentacion.h"
#include <stdio.h>
#include "GBT/gbt.h"
#include "graficos.h"
#include "juego.h"
#include "letras.h"
#include "render.h"


//Dibuja la presentacion de pantalla principal
void dibujarPantalla(int ancho_p, int alto_p)
{
    Dibujar_rect(0, 0, ancho_p, alto_p, 9);

    int caja_w = (ancho_p * 62) / 100;
    int caja_h = (alto_p * 60) / 100;
    int caja_x = (ancho_p - caja_w) / 2;
    int caja_y = (alto_p - caja_h) / 2;

    Dibujar_rect(caja_x, caja_y, caja_w, caja_h, 9);
    dibujarBorde(caja_x, caja_y, caja_w, caja_h, 0);
    dibujarBorde(caja_x + 5, caja_y + 5, caja_w - 10, caja_h - 10, 15);

    int caja_tetris_w = (caja_w * 60) / 100;
    int caja_tetris_h = (caja_h * 12) / 100;
    int caja_tetris_x = caja_x + (caja_w - caja_tetris_w) / 2;
    int caja_tetris_y = caja_y + (caja_h * 16) / 100;
    Dibujar_rect(caja_tetris_x, caja_tetris_y, caja_tetris_w, caja_tetris_h, 0);

    int caja_user_w = (caja_w * 50) / 100;
    int caja_user_h = (caja_h * 8) / 100;
    int caja_user_x = caja_x + (caja_w - caja_user_w) / 2;
    int caja_user_y = caja_y + (caja_h * 50) / 100;
    Dibujar_rect(caja_user_x, caja_user_y, caja_user_w, caja_user_h, 0);

    int caja_press_w = (caja_w * 50) / 100;
    int caja_press_h = (caja_h * 8) / 100;
    int caja_press_x = caja_x + (caja_w - caja_press_w) / 2;
    int caja_press_y = caja_y + (caja_h * 83) / 100;
    Dibujar_rect(caja_press_x, caja_press_y, caja_press_w, caja_press_h, 0);
}

int Presentacion(char nombre[], int ancho_pantalla, int alto_pantalla)
{
    EstadoJuego estado_programa = estado_menu;
    int mostrar_palabra = 1;
    int longitud = 0;

    if(gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888) != 0)
    {
        printf("Error aplicando paleta\n");
        return -1;
    }

    tGBT_Temporizador *temporizador = gbt_temporizador_crear(0.5);
    if(!temporizador)
    {
        fprintf(stderr, "Error al crear el temporizador para los dibujos: %s\n", gbt_obtener_log());
        return -1;
    }

    while(estado_programa != estado_juego)
    {
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        if(gbt_tecla_presionada(GBTK_ENTER) && longitud > 0)
        {
            estado_programa = estado_juego;
            nombre[longitud] = '\0';
        }

        gbt_borrar_backbuffer(0);
        dibujarPantalla(ancho_pantalla, alto_pantalla);

        int caja_w = (ancho_pantalla * 62) / 100;
        int caja_h = (alto_pantalla * 60) / 100;
        int caja_x = (ancho_pantalla - caja_w) / 2;
        int caja_y = (alto_pantalla - caja_h) / 2;

        int titulo_x = caja_x + (caja_w - 53) / 2;
        int titulo_y = caja_y + (caja_h * 16) / 100 + (caja_h * 12 / 100 - 16) / 2;

        dibujar_matriz(titulo_x, titulo_y, 16, 8, letra_T_16, 4);
        dibujar_matriz(titulo_x + 9, titulo_y, 16, 8, letra_E_16, 4);
        dibujar_matriz(titulo_x + 18, titulo_y, 16, 8, letra_T_16, 4);
        dibujar_matriz(titulo_x + 27, titulo_y, 16, 8, letra_R_16, 4);
        dibujar_matriz(titulo_x + 36, titulo_y, 16, 8, letra_I_16, 4);
        dibujar_matriz(titulo_x + 45, titulo_y, 16, 8, letra_S_16, 4);

        int user_box_w = (caja_w * 50) / 100;
        int user_box_y = caja_y + (caja_h * 50) / 100;
        int texto_user_x = caja_x + (caja_w - user_box_w) / 2 + 10;
        int texto_user_y = user_box_y + ((caja_h * 8 / 100) - 8) / 2;

        dibujar_texto("USER:", texto_user_x, texto_user_y, 4);

        if(gbt_temporizador_consumir(temporizador))
            mostrar_palabra = !mostrar_palabra;

        if(mostrar_palabra && longitud < MAX_NOMBRE)
            dibujar_letra('_', texto_user_x + 40 + longitud * 8, texto_user_y, 4);

        if(((tecla >= 'a' && tecla <= 'z') || (tecla >= 'A' && tecla <= 'Z')) && longitud < MAX_NOMBRE - 1)
        {
            nombre[longitud] = tecla;
            longitud++;
        }

        if(tecla == GBTK_RETROCESO && longitud > 0)
            longitud--;

        for(int i = 0; i < longitud; i++)
            dibujar_letra(nombre[i], texto_user_x + 40 + i * 8, texto_user_y, 4);

        int press_box_y = caja_y + (caja_h * 83) / 100;
        int press_x = caja_x + (caja_w - 88) / 2;
        int press_y = press_box_y + ((caja_h * 8 / 100) - 8) / 2;

        dibujar_texto("PRESS", press_x, press_y, 4);

        if(mostrar_palabra)
            dibujar_texto("ENTER", press_x + 48, press_y, 4);

        gbt_volcar_backbuffer();
    }

    gbt_temporizador_destruir(temporizador);
    return longitud;
}
