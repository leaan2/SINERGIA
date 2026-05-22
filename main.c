#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graficos.h"
#include "GBT/gbt.h"
#include "letras.h"
#include "presentacion.h"
#include "pieza.h"

int main(int argc, char *argv[])
{
    int ancho = ANCHO_VENTANA;
    int alto = ALTO_VENTANA;
    int escala = ESCALA_VENTANA;

    // =========================
    // ARGUMENTO 1 -> RESOLUCION
    // =========================

    if(argc >= 2)
    {
        if(strcmp(argv[1], "CGA") == 0)
        {
            ancho = 320;
            alto = 200;
        }
        else if(strcmp(argv[1], "VGA") == 0)
        {
            ancho = 640;
            alto = 480;
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

    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    if (gbt_crear_ventana("Tetris", ancho, alto, escala) != 0) {
        fprintf(stderr, "Error: %s\n", gbt_obtener_log());
        return -1;
    }

    printf("Resolucion: %dx%d\n", ancho, alto);
    printf("Escala: %d\n", escala);

    juego();

    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;
}
