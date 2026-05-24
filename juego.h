#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "presentacion.h"

typedef enum
{
    estado_menu,
    estado_juego,
    estado_pausa,
    estado_configuracion,
    estado_ranking,
    estado_gameover
} EstadoJuego;

typedef struct
{
    int paleta_tipo;
    int resolucion_tipo;
    int escala_ventana;
    double velocidad_init;
} Configuracion;

typedef struct
{
    char nombre[MAX_NOMBRE];
    int puntaje;
} RegistroRanking;

void juego(int escala_ventana, int resolucion_inicial);

void obtener_resolucion_config(const Configuracion *config, int *ancho, int *alto);
void aplicar_resolucion_config(const Configuracion *config, int escala_ventana);
void guardar_configuracion(Configuracion *config);
void cargar_configuracion(Configuracion *config);

int sistemaPuntuacion(int puntaje, int filasborradas, double tiempocaida);
void registrar_en_ranking(const char* nombre, int puntaje);

#endif // JUEGO_H_INCLUDED
