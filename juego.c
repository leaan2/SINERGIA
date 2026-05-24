// Bucle principal//
// configuracion//
//ranking//


#include "juego.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "GBT/gbt.h"
#include "graficos.h"
#include "menu.h"
#include "pieza.h"
#include "render.h"
#include "tablero.h"

#define MAX_REGISTROS_RANKING 100

void obtener_resolucion_config(const Configuracion *config, int *ancho, int *alto)
{
    if(config->resolucion_tipo == 0)
    {
        *ancho = 320;
        *alto = 200;
    }
    else
    {
        *ancho = 640;
        *alto = 480;
    }
}

void aplicar_resolucion_config(const Configuracion *config, int escala_ventana)
{
    int ancho = 0;
    int alto = 0;

    obtener_resolucion_config(config, &ancho, &alto);

    gbt_destruir_ventana();

    if(gbt_crear_ventana("Tetris", ancho, alto, escala_ventana) != 0)
    {
        fprintf(stderr, "Error cambiando resolucion: %s\n", gbt_obtener_log());
        return;
    }

    configurar_limites_dibujo(ancho, alto);

    if(gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888) != 0)
        fprintf(stderr, "Error reaplicando paleta: %s\n", gbt_obtener_log());
}

void guardar_configuracion(Configuracion *config)
{
    FILE *archivo = fopen("config.dat", "wb");

    if(archivo != NULL)
    {
        fwrite(config, sizeof(Configuracion), 1, archivo);
        fclose(archivo);
    }
}

void cargar_configuracion(Configuracion *config)
{
    FILE *archivo = fopen("config.dat", "rb");

    if(archivo != NULL)
    {
        fread(config, sizeof(Configuracion), 1, archivo);
        fclose(archivo);
    }
    else
    {
        config->paleta_tipo = 0;
        config->resolucion_tipo = 1;
        config->escala_ventana = ESCALA_VENTANA;
        config->velocidad_init = 0.5;
        guardar_configuracion(config);
    }
}

int sistemaPuntuacion(int puntaje, int filasborradas, double tiempocaida)
{
    double punt = 100.0;
    punt = (punt / tiempocaida) * 1.2;

    if(filasborradas == 1)
        puntaje += 1 * punt;
    else if(filasborradas == 2)
        puntaje += 3 * punt;
    else if(filasborradas == 3)
        puntaje += 5 * punt;
    else if(filasborradas == 4)
        puntaje += 8 * punt;

    return puntaje;
}

void registrar_en_ranking(const char* nombre, int puntaje)
{
    if(nombre == NULL || nombre[0] == '\0')
        return;

    RegistroRanking nuevo_registro;
    snprintf(nuevo_registro.nombre, MAX_NOMBRE, "%s", nombre);
    nuevo_registro.puntaje = puntaje;

    RegistroRanking registros[MAX_REGISTROS_RANKING];
    int total = 0;
    int encontrado = -1;

    FILE *archivo = fopen("ranking.dat", "rb");
    if(archivo != NULL)
    {
        while(total < MAX_REGISTROS_RANKING &&
              fread(&registros[total], sizeof(RegistroRanking), 1, archivo) == 1)
        {
            registros[total].nombre[MAX_NOMBRE - 1] = '\0';

            if(strcmp(registros[total].nombre, nuevo_registro.nombre) == 0)
                encontrado = total;

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
    if(archivo != NULL)
    {
        fwrite(registros, sizeof(RegistroRanking), total, archivo);
        fclose(archivo);
    }
}

void juego(int escala_ventana, int resolucion_inicial)
{
    Configuracion config;
    cargar_configuracion(&config);

    if(resolucion_inicial >= 0)
    {
        config.resolucion_tipo = resolucion_inicial;
        guardar_configuracion(&config);
    }

    int ancho_presentacion = 0;
    int alto_presentacion = 0;
    obtener_resolucion_config(&config, &ancho_presentacion, &alto_presentacion);

    char nombre[MAX_NOMBRE] = "";
    int longitud = Presentacion(nombre, ancho_presentacion, alto_presentacion);

    EstadoJuego estadoActual = estado_menu;
    EstadoJuego estadoAnteriorRanking = estado_menu;
    int opcion_seleccionada = 0;
    int opcion_pausa = 0;
    int opcion_configuracion = 0;

    int filasborradas = 0;
    int puntaje = 0;
    double tiempocaida = config.velocidad_init;
    uint8_t tocandoPiso = 0;

    tGBT_Temporizador *temporizador = NULL;
    tGBT_Temporizador *temporizadorLock = NULL;

    srand((unsigned)time(0));

    uint8_t corriendo = 1;
    int fila = 0;
    int columna = 3;

    BolsaPiezas bolsa;
    mezclarBolsa(&bolsa);

    int** tablero = crearMatriz(ALTO_T, ANCHO_T);
    inicializarMatriz(tablero, ALTO_T, ANCHO_T);
    Pieza piezaOrig = obtenerPiezaBolsa(&bolsa);

    while(corriendo)
    {
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        gbt_borrar_backbuffer(9);

        int ancho_pantalla = 0;
        int alto_pantalla = 0;
        obtener_resolucion_config(&config, &ancho_pantalla, &alto_pantalla);

        switch(estadoActual)
        {
            case estado_menu:
                if(tecla == GBTK_s || tecla == GBTK_ABAJO)
                    opcion_seleccionada = (opcion_seleccionada + 1) % 6;

                if(tecla == GBTK_w || tecla == GBTK_ARRIBA)
                    opcion_seleccionada = (opcion_seleccionada - 1 + 6) % 6;

                if(tecla == GBTK_d || tecla == GBTK_DERECHA || tecla == GBTK_a || tecla == GBTK_IZQUIERDA)
                {
                    int dir = (tecla == GBTK_d || tecla == GBTK_DERECHA) ? 1 : -1;

                    if(opcion_seleccionada == 0)
                    {
                        config.paleta_tipo = (config.paleta_tipo + dir + 3) % 3;
                    }
                    else if(opcion_seleccionada == 1)
                    {
                        config.resolucion_tipo = (config.resolucion_tipo + dir + 2) % 2;
                        aplicar_resolucion_config(&config, escala_ventana);
                        obtener_resolucion_config(&config, &ancho_pantalla, &alto_pantalla);
                    }
                    else if(opcion_seleccionada == 2)
                    {
                        config.velocidad_init -= dir * 0.1;

                        if(config.velocidad_init < 0.1)
                            config.velocidad_init = 0.1;

                        if(config.velocidad_init > 1.5)
                            config.velocidad_init = 1.5;
                    }
                }

                if(tecla == GBTK_ESCAPE)
                    corriendo = 0;

                dibujarMenuPrincipal(&config, opcion_seleccionada, ancho_pantalla, alto_pantalla);

                if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_seleccionada == 3)
                {
                    estadoAnteriorRanking = estado_menu;
                    estadoActual = estado_ranking;
                }
                else if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_seleccionada == 4)
                {
                    guardar_configuracion(&config);

                    if(temporizador)
                    {
                        gbt_temporizador_destruir(temporizador);
                        temporizador = NULL;
                    }

                    if(temporizadorLock)
                    {
                        gbt_temporizador_destruir(temporizadorLock);
                        temporizadorLock = NULL;
                    }

                    tiempocaida = config.velocidad_init;
                    temporizador = gbt_temporizador_crear(tiempocaida);
                    temporizadorLock = gbt_temporizador_crear(0.2);

                    estadoActual = estado_juego;
                }
                else if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_seleccionada == 5)
                {
                    corriendo = 0;
                }
                break;

            case estado_juego:
                if(tecla == GBTK_ESCAPE)
                {
                    estadoActual = estado_pausa;
                    break;
                }

                if(tecla == GBTK_a || tecla == GBTK_IZQUIERDA)
                    moverPieza(tablero, piezaOrig, &fila, &columna, 0, -1);

                if(tecla == GBTK_d || tecla == GBTK_DERECHA)
                    moverPieza(tablero, piezaOrig, &fila, &columna, 0, 1);

                if(tecla == GBTK_w || tecla == GBTK_ARRIBA)
                {
                    Pieza rotada = rotarPiezaIzquierda(piezaOrig);
                    if(puedeColocarPieza(tablero, rotada, fila, columna))
                        piezaOrig = rotada;
                }

                if(tecla == GBTK_s || tecla == GBTK_ABAJO)
                {
                    Pieza rotada = rotarPiezaDerecha(piezaOrig);
                    if(puedeColocarPieza(tablero, rotada, fila, columna))
                        piezaOrig = rotada;
                }

                if(gbt_tecla_sostenida(GBTK_f) || gbt_tecla_sostenida(GBTK_ESPACIO))
                    if(moverPieza(tablero, piezaOrig, &fila, &columna, 1, 0))
                        puntaje++;

                if(gbt_temporizador_consumir(temporizador))
                    moverPieza(tablero, piezaOrig, &fila, &columna, 1, 0);

                if(!puedeColocarPieza(tablero, piezaOrig, fila + 1, columna))
                {
                    if(!tocandoPiso)
                    {
                        tocandoPiso = 1;
                        gbt_temporizador_destruir(temporizadorLock);
                        temporizadorLock = gbt_temporizador_crear(0.2);
                    }

                    if(gbt_temporizador_consumir(temporizadorLock))
                    {
                        colocarPieza(tablero, piezaOrig, fila, columna);
                        filasborradas = eliminarFilasCompletas(tablero);
                        puntaje = sistemaPuntuacion(puntaje, filasborradas, tiempocaida);

                        fila = 0;
                        columna = 3;
                        piezaOrig = obtenerPiezaBolsa(&bolsa);
                        tocandoPiso = 0;

                        if(!puedeColocarPieza(tablero, piezaOrig, fila, columna))
                            estadoActual = estado_gameover;
                    }
                }
                else
                {
                    tocandoPiso = 0;
                }

                dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje, config.paleta_tipo, ancho_pantalla, alto_pantalla);
                break;

            case estado_pausa:
                dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje, config.paleta_tipo, ancho_pantalla, alto_pantalla);

                if(tecla == GBTK_ESCAPE)
                {
                    estadoActual = estado_juego;
                    break;
                }

                if(tecla == GBTK_w || tecla == GBTK_ARRIBA)
                    opcion_pausa = (opcion_pausa + 3) % 4;

                if(tecla == GBTK_s || tecla == GBTK_ABAJO)
                    opcion_pausa = (opcion_pausa + 1) % 4;

                dibujarMenuPausa(opcion_pausa, ancho_pantalla, alto_pantalla);

                if(tecla == GBTK_ENTER || tecla == GBTK_ESPACIO)
                {
                    if(opcion_pausa == 0)
                        estadoActual = estado_juego;
                    else if(opcion_pausa == 1)
                    {
                        opcion_configuracion = 0;
                        estadoActual = estado_configuracion;
                    }
                    else if(opcion_pausa == 2)
                    {
                        estadoAnteriorRanking = estado_pausa;
                        estadoActual = estado_ranking;
                    }
                    else if(opcion_pausa == 3)
                    {
                        estadoActual = estado_menu;
                    }
                }
                break;

            case estado_configuracion:
                dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje, config.paleta_tipo, ancho_pantalla, alto_pantalla);

                if(tecla == GBTK_w || tecla == GBTK_ARRIBA)
                    opcion_configuracion = (opcion_configuracion + 3) % 4;

                if(tecla == GBTK_s || tecla == GBTK_ABAJO)
                    opcion_configuracion = (opcion_configuracion + 1) % 4;

                if(tecla == GBTK_d || tecla == GBTK_DERECHA || tecla == GBTK_a || tecla == GBTK_IZQUIERDA)
                {
                    int dir = (tecla == GBTK_d || tecla == GBTK_DERECHA) ? 1 : -1;

                    if(opcion_configuracion == 0)
                    {
                        config.paleta_tipo = (config.paleta_tipo + dir + 3) % 3;
                    }
                    else if(opcion_configuracion == 1)
                    {
                        config.resolucion_tipo = (config.resolucion_tipo + dir + 2) % 2;
                        aplicar_resolucion_config(&config, escala_ventana);
                        obtener_resolucion_config(&config, &ancho_pantalla, &alto_pantalla);
                    }
                    else if(opcion_configuracion == 2)
                    {
                        config.velocidad_init -= dir * 0.1;

                        if(config.velocidad_init < 0.1)
                            config.velocidad_init = 0.1;

                        if(config.velocidad_init > 1.5)
                            config.velocidad_init = 1.5;

                        tiempocaida = config.velocidad_init;

                        if(temporizador)
                        {
                            gbt_temporizador_destruir(temporizador);
                            temporizador = gbt_temporizador_crear(tiempocaida);
                        }
                    }

                    guardar_configuracion(&config);
                }

                dibujarMenuConfiguracion(&config, opcion_configuracion, ancho_pantalla, alto_pantalla);

                if((tecla == GBTK_ENTER || tecla == GBTK_ESPACIO) && opcion_configuracion == 3)
                {
                    guardar_configuracion(&config);
                    estadoActual = estado_pausa;
                }

                if(tecla == GBTK_ESCAPE)
                {
                    guardar_configuracion(&config);
                    estadoActual = estado_pausa;
                }
                break;

            case estado_ranking:
                dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje, config.paleta_tipo, ancho_pantalla, alto_pantalla);
                dibujarRanking(ancho_pantalla, alto_pantalla);

                if(tecla == GBTK_ESCAPE)
                    estadoActual = estadoAnteriorRanking;
                break;

            case estado_gameover:
                dibujarInterfaz(tablero, piezaOrig, fila, columna, nombre, longitud, puntaje, config.paleta_tipo, ancho_pantalla, alto_pantalla);
                dibujarGameOver(puntaje, ancho_pantalla, alto_pantalla);

                if(tecla == GBTK_ESPACIO || tecla == GBTK_ENTER)
                {
                    registrar_en_ranking(nombre, puntaje);

                    inicializarMatriz(tablero, ALTO_T, ANCHO_T);
                    puntaje = 0;
                    fila = 0;
                    columna = 3;
                    mezclarBolsa(&bolsa);
                    piezaOrig = obtenerPiezaBolsa(&bolsa);

                    if(temporizador)
                        gbt_temporizador_destruir(temporizador);

                    if(temporizadorLock)
                        gbt_temporizador_destruir(temporizadorLock);

                    temporizador = NULL;
                    temporizadorLock = NULL;

                    estadoActual = estado_menu;
                }
                break;
        }

        gbt_volcar_backbuffer();
        gbt_esperar(20);
    }

    destruirMatriz(tablero, ALTO_T);

    if(temporizador)
        gbt_temporizador_destruir(temporizador);

    if(temporizadorLock)
        gbt_temporizador_destruir(temporizadorLock);
}
