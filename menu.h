//Primitivas de Menu//

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "juego.h"

void dibujarMenuPrincipal(const Configuracion *config, int opcion_seleccionada, int ancho_pantalla, int alto_pantalla);
void dibujarMenuPausa(int opcion_pausa, int ancho_pantalla, int alto_pantalla);
void dibujarMenuConfiguracion(const Configuracion *config, int opcion_configuracion, int ancho_pantalla, int alto_pantalla);
void dibujarRanking(int ancho_pantalla, int alto_pantalla);
void dibujarGameOver(int puntaje, int ancho_pantalla, int alto_pantalla);

#endif // MENU_H_INCLUDED
