//Integrantes
//Thiago Romeo
//Leandro Gonzalez



#include <stdio.h>
#include <stdlib.h>

#include "graficos.h"
#include "GBT/gbt.h"
#include "juego.h"
#include "pieza.h"

int main(int argc, char *argv[])
{
    Configuracion config;
    cargar_configuracion(&config);

    int escala = ESCALA_VENTANA;
    int resolucion_inicial = -1;

    // =========================
    // ARGUMENTO 1 -> RESOLUCION
    // =========================

    if(argc >= 2)
    {
        char resolucion_arg = argv[1][0];

        if(resolucion_arg == 'c' || resolucion_arg == 'C')
        {
            resolucion_inicial = 0;
        }
        else if(resolucion_arg == 'v' || resolucion_arg == 'V')
        {
            resolucion_inicial = 1;
        }

        if(resolucion_inicial >= 0)
        {
            config.resolucion_tipo = resolucion_inicial;
            guardar_configuracion(&config);
        }
    }

    // =========================
    // ARGUMENTO 2 -> ESCALA
    // =========================

    if(argc >= 3)
    {
        escala = atoi(argv[2]);

        if(escala <= 0)
            escala = 3;
    }

    // =========================

    int ancho = 0;
    int alto = 0;
    obtener_resolucion_config(&config, &ancho, &alto);

    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    if (gbt_crear_ventana("Tetris", ancho, alto, escala) != 0) {
        fprintf(stderr, "Error: %s\n", gbt_obtener_log());
        return -1;
    }

    configurar_limites_dibujo(ancho, alto);

    printf("Resolucion: %dx%d\n", ancho, alto);
    printf("Escala: %d\n", escala);

    juego(escala, resolucion_inicial);

    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;
}
