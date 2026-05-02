#include <stdio.h>
#include "presentacion.h"
#include "juego.h"
#include "graficos.h"
#include "GBT/gbt.h"

#define FILAS 20
#define COLUMNAS 10
#define TAM 8   // tamaño de cada bloque

// tablero
int tablero[FILAS][COLUMNAS] = {0};

// pieza simple (cuadrado 2x2)
int pieza[2][2] = {
    {1,1},
    {1,1}
};

int pieza_x = 4;
int pieza_y = 0;

// temporizador
tGBT_Temporizador *timer;

// ================= DIBUJO =================
void dibujar_tablero() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j]) {
                Dibujar_rect(j*TAM, i*TAM, TAM, TAM, 4);
            }
        }
    }
}

void dibujar_pieza() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (pieza[i][j]) {
                Dibujar_rect((pieza_x + j)*TAM,
                             (pieza_y + i)*TAM,
                             TAM, TAM, 15);
            }
        }
    }
}

// ================= COLISION =================
int colision(int nx, int ny) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (pieza[i][j]) {
                int x = nx + j;
                int y = ny + i;

                if (x < 0 || x >= COLUMNAS || y >= FILAS)
                    return 1;

                if (tablero[y][x])
                    return 1;
            }
        }
    }
    return 0;
}

// ================= FIJAR =================
void fijar_pieza() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (pieza[i][j]) {
                tablero[pieza_y + i][pieza_x + j] = 1;
            }
        }
    }

    // reiniciar pieza
    pieza_x = 4;
    pieza_y = 0;
}

// ================= INPUT =================
void manejar_input() {
    if (gbt_tecla_presionada(GBTK_IZQUIERDA)) {
        if (!colision(pieza_x - 1, pieza_y))
            pieza_x--;
    }

    if (gbt_tecla_presionada(GBTK_DERECHA)) {
        if (!colision(pieza_x + 1, pieza_y))
            pieza_x++;
    }

    if (gbt_tecla_presionada(GBTK_ABAJO)) {
        if (!colision(pieza_x, pieza_y + 1))
            pieza_y++;
    }
}

// ================= LOOP =================
void juego_loop() {

    timer = gbt_temporizador_crear(0.5);
    if (gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888) != 0) {
    printf("Error paleta\n");
    }
    while (1) {

        gbt_procesar_entrada();
        gbt_borrar_backbuffer(0);
        Dibujar_rect(10, 10, 20, 20, 15);
        manejar_input();

        // caída automática
        if (gbt_temporizador_consumir(timer)) {
            if (!colision(pieza_x, pieza_y + 1)) {
                pieza_y++;
            } else {
                fijar_pieza();
            }
        }


        dibujar_tablero();
        dibujar_pieza();

        gbt_volcar_backbuffer();

    }

    gbt_temporizador_destruir(timer);
}
