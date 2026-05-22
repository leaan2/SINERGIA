#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDED

// Estructura para transportar las opciones elegidas
typedef struct {
    int paleta;           // 0: Clasica, 1: Neon, 2: GameBoy, etc.
    int resolucion;       // 0: 320x240, 1: 640x480, etc. (O los bloques del tablero si es resolucion logica del Tetris)
    int velocidad_inicial;// 1: Facil, 2: Normal, 3: Dificil (afecta el delay de caida)
} ConfigurarJuego;

#endif // CONFIGURACION_H_INCLUDED
