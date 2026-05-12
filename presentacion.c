#include <stdio.h>
#include <stdlib.h>
#include "presentacion.h"
#include "GBT/gbt.h"
#include "pieza.h"
void dibujar_letra(char c, int x, int y);
void dibujarPantalla ();
int Presentacion(char nombre[]);

void dibujarPantalla() {
    // fondo
    dibujarFondo();

    // rectángulo azul principal
    Dibujar_rect(60, 30, 200, 120, 9); // azul

    // borde blanco
    dibujarBorde(60, 30, 200, 120, 0);

    // borde interior (opcional)
    dibujarBorde(65, 35, 190, 110, 15);

    // texto simplificado (bloques)
    Dibujar_rect(100, 50, 120, 15, 0); //
    Dibujar_rect(110, 90, 100, 10, 0);  //

    // "Press START"
    Dibujar_rect(110, 130, 100, 9, 0);
}

void dibujar_letra(char c, int x, int y)
{
    switch (c)
    {
        case 'A': dibujar_matriz(x, y, 8, 8, letra_A, 4); break;
        case 'B': dibujar_matriz(x, y, 8, 8, letra_B, 4); break;
        case 'C': dibujar_matriz(x, y, 8, 8, letra_C, 4); break;
        case 'D': dibujar_matriz(x, y, 8, 8, letra_D, 4); break;
        case 'E': dibujar_matriz(x, y, 8, 8, letra_E, 4); break;
        case 'F': dibujar_matriz(x, y, 8, 8, letra_F, 4); break;
        case 'G': dibujar_matriz(x, y, 8, 8, letra_G, 4); break;
        case 'H': dibujar_matriz(x, y, 8, 8, letra_H, 4); break;
        case 'I': dibujar_matriz(x, y, 8, 8, letra_I, 4); break;
        case 'J': dibujar_matriz(x, y, 8, 8, letra_J, 4); break;
        case 'K': dibujar_matriz(x, y, 8, 8, letra_K, 4); break;
        case 'L': dibujar_matriz(x, y, 8, 8, letra_L, 4); break;
        case 'M': dibujar_matriz(x, y, 8, 8, letra_M, 4); break;
        case 'N': dibujar_matriz(x, y, 8, 8, letra_N, 4); break;
        case 'O': dibujar_matriz(x, y, 8, 8, letra_O, 4); break;
        case 'P': dibujar_matriz(x, y, 8, 8, letra_P, 4); break;
        case 'Q': dibujar_matriz(x, y, 8, 8, letra_Q, 4); break;
        case 'R': dibujar_matriz(x, y, 8, 8, letra_R, 4); break;
        case 'S': dibujar_matriz(x, y, 8, 8, letra_S, 4); break;
        case 'T': dibujar_matriz(x, y, 8, 8, letra_T, 4); break;
        case 'U': dibujar_matriz(x, y, 8, 8, letra_U, 4); break;
        case 'V': dibujar_matriz(x, y, 8, 8, letra_V, 4); break;
        case 'W': dibujar_matriz(x, y, 8, 8, letra_W, 4); break;
        case 'X': dibujar_matriz(x, y, 8, 8, letra_X, 4); break;
        case 'Y': dibujar_matriz(x, y, 8, 8, letra_Y, 4); break;
        case 'Z': dibujar_matriz(x, y, 8, 8, letra_Z, 4); break;
        case '_': dibujar_matriz(x, y, 8, 8, letra_guionbajo, 4); break;
    }
}


int Presentacion(char nombre [])
    {
        EstadoJuego estado_programa = estado_menu;
        int mostrar_palabra=1;

        int longitud = 0;
        // aplicar paleta
        if (gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888) != 0) {
            printf("Error aplicando paleta\n");
            return -1;
        }

        tGBT_Temporizador *temporizador = gbt_temporizador_crear(0.5);
        if (!temporizador) {
            fprintf(stderr, "Error al crear el temporizador para los dibujos: %s\n", gbt_obtener_log());
            return -1;
        }

            while (estado_programa!= estado_juego)
        {

                gbt_procesar_entrada();
                eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
                if (gbt_tecla_presionada(GBTK_ENTER) && longitud > 0)
                {
                    estado_programa = estado_juego;
                    nombre[longitud] ='\0';
                }


                // FONDO
                gbt_borrar_backbuffer(0); // negro

                dibujarPantalla();

                // variables para pixeles
                int y = 52;
                int x = (ANCHO_VENTANA - 58) / 2;

                //TITULO
                dibujar_matriz(x + 0,  y, 16, 8, letra_T_16, 4);
                dibujar_matriz(x + 9, y, 16, 8, letra_E_16, 4);
                dibujar_matriz(x + 18, y, 16, 8, letra_T_16, 4);
                dibujar_matriz(x + 27, y, 16, 8, letra_R_16, 4);
                dibujar_matriz(x + 36, y, 16, 8, letra_I_16, 4);
                dibujar_matriz(x + 45, y, 16, 8, letra_S_16, 4);

                // USER
                x=110;
                y=92;
                dibujar_matriz(x, y, 8, 8, letra_U, 4);
                dibujar_matriz(x+8, y, 8, 8, letra_S, 4);
                dibujar_matriz(x+16, y, 8, 8, letra_E, 4);
                dibujar_matriz(x+24, y, 8, 8, letra_R, 4);
                dibujar_matriz(x+32, y, 8, 8, letra_signopuntuacion, 4);
                if (gbt_temporizador_consumir(temporizador))
                {
                    mostrar_palabra = !mostrar_palabra; // setea en 1 y 0
                }

                if(mostrar_palabra && longitud < MAX_NOMBRE){
                    dibujar_matriz(x+40 + longitud * 8, y, 8, 8, letra_guionbajo, 4);
                }


                if ((tecla >= 'a' && tecla <= 'z') && longitud < MAX_NOMBRE - 1)
                {
                    nombre[longitud] = tecla - 32; // a may�scula
                    longitud++;
                }
                if (tecla == GBTK_RETROCESO && longitud > 0)
                {
                    longitud--;              // retrocede una posicion
                }



                for (int i = 0; i < longitud; i++)
                {
                    dibujar_letra(nombre[i], x + 40 + i * 8, y);
                }


                // PRESS START
                y=131;
                dibujar_matriz(x, y, 8, 8, letra_P, 4);
                dibujar_matriz(x+8, y, 8, 8, letra_R, 4);
                dibujar_matriz(x+16, y, 8, 8, letra_E, 4);
                dibujar_matriz(x+24, y, 8, 8, letra_S, 4);
                dibujar_matriz(x+32, y, 8, 8, letra_S, 4);


                if(mostrar_palabra){
                dibujar_matriz(x+48, y, 8, 8, letra_E, 4);
                dibujar_matriz(x+56, y, 8, 8, letra_N, 4);
                dibujar_matriz(x+64, y, 8, 8, letra_T, 4);
                dibujar_matriz(x+72, y, 8, 8, letra_E, 4);
                dibujar_matriz(x+80, y, 8, 8, letra_R, 4);
                }



                gbt_volcar_backbuffer();
            }


        gbt_temporizador_destruir(temporizador);
        return longitud;
    }




