#ifndef PRESENTACION_H_INCLUDED
#define PRESENTACION_H_INCLUDED

#define MAX_NOMBRE 7

typedef struct
{
    int paleta;
    int resolucion;
    int velocidad_inicial;
} ConfigurarJuego;

void dibujarPantalla(int ancho_p, int alto_p);
int Presentacion(char nombre[], int ancho_pantalla, int alto_pantalla);

#endif // PRESENTACION_H_INCLUDED
