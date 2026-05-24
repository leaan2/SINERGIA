//Menu principal//
//Pausa//
//Configuracion//
//Ranking//
//Game over//

#include "menu.h"

#include <stdio.h>

#include "graficos.h"
#include "letras.h"
#include "render.h"

static void dibujarTituloTetris(int x, int y)
{
    dibujar_matriz(x, y, 16, 8, letra_T_16, 4);
    dibujar_matriz(x + 9, y, 16, 8, letra_E_16, 4);
    dibujar_matriz(x + 18, y, 16, 8, letra_T_16, 4);
    dibujar_matriz(x + 27, y, 16, 8, letra_R_16, 4);
    dibujar_matriz(x + 36, y, 16, 8, letra_I_16, 4);
    dibujar_matriz(x + 45, y, 16, 8, letra_S_16, 4);
}

void dibujarMenuPrincipal(const Configuracion *config, int opcion_seleccionada, int ancho_pantalla, int alto_pantalla)
{
    int menu_centro_x = ancho_pantalla / 2;
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

    dibujarTituloTetris(menu_centro_x - 27, menu_panel_y + (menu_compacto ? 14 : 18));

    const char* opciones_menu[6] = {"PALETA", "RES", "VELOC", "RANKING", "JUGAR", "SALIR"};

    for(int i = 0; i < 6; i++)
    {
        int opcion_y = menu_fila_y + menu_fila_espacio * i;
        int texto_color = 7;

        if(i <= 3)
            texto_color = 4;

        if(i == 4)
            texto_color = 2;

        if(i == opcion_seleccionada)
        {
            Dibujar_rect(menu_panel_x + 22, opcion_y - 4, menu_panel_w - 44, 17, 8);
            Dibujar_rect(menu_panel_x + 34, opcion_y + 2, 4, 4, 14);
            texto_color = 14;
        }

        dibujar_texto(opciones_menu[i], menu_texto_x, opcion_y, texto_color);
    }

    if(config->paleta_tipo == 0)
        dibujar_letra('C', menu_valor_x, menu_fila_y, 14);
    else if(config->paleta_tipo == 1)
        dibujar_letra('G', menu_valor_x, menu_fila_y, 14);
    else if(config->paleta_tipo == 2)
        dibujar_letra('N', menu_valor_x, menu_fila_y, 14);

    if(config->resolucion_tipo == 0)
        dibujar_texto("CGA", menu_valor_x, menu_fila_y + menu_fila_espacio, 14);
    else
        dibujar_texto("VGA", menu_valor_x, menu_fila_y + menu_fila_espacio, 14);

    Dibujar_rect(menu_valor_x, menu_fila_y + menu_fila_espacio * 2 + 3, 34, 4, 8);
    Dibujar_rect(menu_valor_x, menu_fila_y + menu_fila_espacio * 2 + 3, (int)(config->velocidad_init * 20), 4, 14);
}

void dibujarMenuPausa(int opcion_pausa, int ancho_pantalla, int alto_pantalla)
{
    int caja_w = 220;
    int caja_h = 170;
    int caja_x = (ancho_pantalla - caja_w) / 2;
    int caja_y = (alto_pantalla - caja_h) / 2;

    Dibujar_rect(caja_x, caja_y, caja_w, caja_h, 0);
    dibujarBorde(caja_x, caja_y, caja_w, caja_h, 14);
    dibujar_texto("PAUSA", caja_x + 80, caja_y + 10, 12);

    const char* opciones[4] = {"CONTINUAR", "CONFIG", "RANKING", "SALIR"};

    for(int i = 0; i < 4; i++)
    {
        int color = (i == opcion_pausa) ? 14 : 7;

        if(i == opcion_pausa)
            Dibujar_rect(caja_x + 25, caja_y + 47 + i * 25, 4, 4, 14);

        dibujar_texto(opciones[i], caja_x + 45, caja_y + 45 + i * 25, color);
    }
}

void dibujarMenuConfiguracion(const Configuracion *config, int opcion_configuracion, int ancho_pantalla, int alto_pantalla)
{
    int config_w = 260;
    int config_h = 170;
    int config_x = (ancho_pantalla - config_w) / 2;
    int config_y = (alto_pantalla - config_h) / 2;

    Dibujar_rect(config_x, config_y, config_w, config_h, 0);
    dibujarBorde(config_x, config_y, config_w, config_h, 14);
    dibujar_texto("CONFIG", config_x + 105, config_y + 10, 12);

    const char* opciones_config[4] = {"PALETA", "RES", "VELOC", "VOLVER"};

    for(int i = 0; i < 4; i++)
    {
        int color = (i == opcion_configuracion) ? 14 : 7;
        int y_opcion = config_y + 45 + i * 25;

        if(i == opcion_configuracion)
            Dibujar_rect(config_x + 25, y_opcion + 2, 4, 4, 14);

        dibujar_texto(opciones_config[i], config_x + 45, y_opcion, color);

        if(i == 0)
        {
            if(config->paleta_tipo == 0)
                dibujar_letra('C', config_x + 165, y_opcion, 14);
            else if(config->paleta_tipo == 1)
                dibujar_letra('G', config_x + 165, y_opcion, 14);
            else if(config->paleta_tipo == 2)
                dibujar_letra('N', config_x + 165, y_opcion, 14);
        }
        else if(i == 1)
        {
            if(config->resolucion_tipo == 0)
                dibujar_texto("CGA", config_x + 155, y_opcion, 14);
            else
                dibujar_texto("VGA", config_x + 155, y_opcion, 14);
        }
        else if(i == 2)
        {
            Dibujar_rect(config_x + 155, y_opcion + 2, 32, 4, 8);
            Dibujar_rect(config_x + 155, y_opcion + 2, (int)(config->velocidad_init * 20), 4, 14);
        }
    }
}

void dibujarRanking(int ancho_pantalla, int alto_pantalla)
{
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
    dibujar_texto("RANKING", rx + (rw - 56) / 2, titulo_y, 14);

    FILE *f_rank = fopen("ranking.dat", "rb");
    if(f_rank == NULL)
        return;

    RegistroRanking lista[100];
    int total = 0;

    while(total < 100 && fread(&lista[total], sizeof(RegistroRanking), 1, f_rank) == 1)
    {
        lista[total].nombre[MAX_NOMBRE - 1] = '\0';
        total++;
    }

    fclose(f_rank);

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
        char puntaje_texto[12];

        dibujar_letra(puesto, puesto_x, y, 14);

        for(int n = 0; lista[i].nombre[n] != '\0' && n < max_nombre_chars; n++)
            dibujar_letra(lista[i].nombre[n], nombre_x + n * 8, y, 7);

        snprintf(puntaje_texto, sizeof(puntaje_texto), "%d", lista[i].puntaje);
        dibujar_texto(puntaje_texto, puntaje_x, y, 12);
    }
}

void dibujarGameOver(int puntaje, int ancho_pantalla, int alto_pantalla)
{
    int go_panel_w = 220;
    int go_panel_h = 140;
    int go_panel_x = (ancho_pantalla - go_panel_w) / 2;
    int go_panel_y = (alto_pantalla - go_panel_h) / 2;
    char puntaje_numero[12];

    snprintf(puntaje_numero, sizeof(puntaje_numero), "%d", puntaje);

    Dibujar_rect(go_panel_x, go_panel_y, go_panel_w, go_panel_h, 0);
    dibujarBorde(go_panel_x, go_panel_y, go_panel_w, go_panel_h, 14);

    dibujar_texto("GAME", go_panel_x + 94, go_panel_y + 18, 4);
    dibujar_texto("OVER", go_panel_x + 94, go_panel_y + 38, 12);
    dibujar_texto("PUNTAJE", go_panel_x + 45, go_panel_y + 72, 14);
    dibujar_texto(puntaje_numero, go_panel_x + 125, go_panel_y + 72, 7);
    dibujar_texto("ENTER MENU", go_panel_x + 70, go_panel_y + 105, 7);
}
