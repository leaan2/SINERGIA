


# **TETRIS – SINERGIA (GUIA DE USO Y INSTALACION)**

## **1. INTRODUCCIÓN DEL DOCUMENTO**

Este documento contiene toda la información necesaria para la configuración, vinculación de bibliotecas gráficas para el “**Tetris**” del grupo **SINERGIA**.

## **2. INSTALACIÓN DE CODE::BLOCKS Y BIBLIOTECA GBT**

[Link de descarga al CODE::BLOCKS](#)

Debe descargar el archivo conveniente a sus especificaciones de computadora e instalarlo ya que permite una interfaz intuitiva.

[Link de descarga biblioteca GBT](#)

Al ingresar al link propuesto, debe ir a code y descargar el archivo como ZIP, extraer la carpeta “**libgbt-dist-main**” a la carpeta “**SINERGIA**”. Una vez instalado el codeblocks y descargada la biblioteca GBT, abrir el archivo **Tetris.cbp**. Antes de compilar el programa debe verificar que la biblioteca esté bien vinculada de la siguiente manera:

Haga clic derecho sobre el nombre del proyecto (Tetris), pulse **Build options**, estando sobre el **Build target Debug** haga click en la solapa **Linker settings**. En **Other linker options** agregue **-lgbt**.

Acceda al tab **Search Directories**:

- En el **tab Compiler** agregue pulsando el botón **add** la ruta a la carpeta **include/** de la biblioteca.
- En el **tab Linker** agregue pulsando el botón **add** la ruta a la carpeta **lib/** de la biblioteca.

Pulse **OK** para guardar los cambios.

Para poder ejecutar el programa debe copiar el archivo **gbt.dll** en la ruta donde se generó el resultado de la compilación (la ubicación del archivo .exe que se encuentra explicado en la siguiente sección)

## **3. UBICACIÓN Y ESTRUCTURA DE ARCHIVOS**

Para que el proyecto compile de forma organizada sin ningún tipo de error, los archivos deben estar distribuidos en la carpeta **SINERGIA** de la siguiente forma:



- bin/Debug/ → Carpeta donde se crea el ejecutable final (Tetris.exe) y archivos guardado
- obj/Debug/ → Carpeta temporal donde el compilador guarda los archivos objeto (.o)
- GBT_v2026.1C.01/ → Carpeta interna que contiene la biblioteca gráfica.
- Tetris.cbp → Archivo del Proyecto de Code::Blocks
- Tetris.layout y Tetris.depend → Archivos automáticos de configuración de pantalla del IDE.
- main.c → Punto de entrada del programa
- graficos.c y graficos.h → Primitivas gráficas, paleta CGA/VGA y funciones de dibujo sobre GBT.
- juego.c y juego.h → Bucle principal, estados del juego, configuración, puntuación y ranking.
- letras.c y letras.h → Mapas de píxeles para letras, números y símbolos.
- menu.c y menu.h → Menú principal, pausa, configuración, ranking y pantalla de game over.
- pieza.c y pieza.h → Definición de tetrominos, rotación y sistema de bolsa de piezas.



- **presentacion.c** y **presentacion.h** → Pantalla inicial para ingresar el nombre del jugador.
- **render.c** y **render.h** → Dibujo del tablero, piezas, interfaz y textos.
- **tablero.c** y **tablero.h** → Matriz del tablero, colisiones, movimiento y eliminación de filas.
- **config.dat** y **ranking.dat** → Archivo de configuración (se crea o actualiza automáticamente) y Archivo binario de ranking ( Se actualiza al terminar la partida)

## 4. GUÍA DE USO

Ya teniendo la biblioteca compilada, sobre el nombre del proyecto pulse click derecho **"Build"** y luego **"Run" (F9)**.

Alternativamente, puede dirigirse a la siguiente ruta del archivo: **bin/Debug/** y ejecutar directamente el archivo **"Tetris.exe"**.



### Menú principal:

Al abrir el juego aparecerá una **pantalla de presentación** donde escribirá su usuario (máximo 6 caracteres, sin incluir símbolos especiales) y presionar **ENTER**.

Al haber introducido su **usuario**, será llevado al menú del juego que dispone de las siguientes opciones:

- **Paleta:** Permite cambiar la estética de colores en tiempo real (Clásica, Neón o GameBoy).
- **Res:** Cambia la resolución lógica entre CGA (320x200) o VGA (640x480).
- **Veloc:** Ajusta el temporizador de la velocidad de caída inicial de los tetrominos.
- **Ranking:** Muestra las puntuaciones más altas almacenadas localmente.
- **Jugar:** Inicia la partida con las configuraciones seleccionadas.
- **Salir:** Cierra de forma segura el programa.

### Navegación del menú:

Utilice las teclas **W/S** o las **Flechas Arriba/Abajo** para desplazarse verticalmente. Use las teclas **A/D** o las **Flechas Izquierda/Derecha** para modificar los valores de las opciones. Presione **ESC** si desea regresar al menú anterior. Para comenzar la partida, colóquese sobre la opción "**Jugar**" y presione **ENTER**.

### Controles durante el juego:

**W o flecha hacia arriba:** Rota la pieza hacia la izquierda

**S o flecha hacia abajo:** Rota la pieza hacia la derecha

**A o flecha hacia la izquierda:** Desplaza la pieza hacia la izquierda

**D o flecha hacia la derecha:** Desplaza la pieza hacia la derecha

**Espacio o F:** Bajar más rápido la pieza mientras se mantiene presionado

**ESC:** Abre el menú de pausa en medio de la partida, permitiendo ajustar configuraciones, revisar el ranking, salir al menú principal o reanudar la partida actual sin perder el progreso.

### Sistema de puntuación:



Suma de puntaje basado en:

**+1 punto:** Por cada fila que la pieza descienda manualmente de forma controlada.

**+100 puntos:** Al limpiar una sola fila

**+300 puntos:** Al limpiar dos filas simultáneamente.

**+500 puntos:** Al limpiar tres filas simultáneamente.

**+800 puntos:** Al realizar un "Tetris" (limpiar cuatro filas simultáneamente, siendo esta la cantidad máxima permitida).

La **velocidad** de caída del **tetromino** aumentará un **3%** automáticamente cada **10 piezas colocadas**. A mayor **velocidad** de juego, mayor será la **recompensa** de **puntos** obtenida por fila eliminada.