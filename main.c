#include <stdio.h>
#include <stdlib.h>
#include "graficos.h"
#include "GBT/gbt.h"
#include "letras.h"
#include "presentacion.h"
#include "pieza.h"
<<<<<<< HEAD
=======

>>>>>>> 653e12d60e2814431c2079275c60097e78d69b54
int main()
{

    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    if (gbt_crear_ventana("Tetris", ANCHO_VENTANA, ALTO_VENTANA, ESCALA_VENTANA) != 0) {
        fprintf(stderr, "Error: %s\n", gbt_obtener_log());
        return -1;
    }

    juego();
    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
