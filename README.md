# **TETRIS – SINERGIA (GUIA DE USO Y INSTALACION)**

## **1. INTRODUCCIÓN DEL DOCUMENTO**

Este documento contiene toda la información necesaria para la instalación, configuración y vinculación de las bibliotecas gráficas requeridas para ejecutar el juego "Tetris" desarrollado por el grupo **SINERGIA**.

## **2. INSTALACIÓN DE CODE::BLOCKS Y BIBLIOTECA GBT**

[Link de descarga al CODE::BLOCKS](#)

1. Descarga e instalación de **Code::Blocks**
2. Acceda al link de descarga de **Code::Blocks** proporcionado por la cátedra.
3. Descargue el archivo **codeblocks-25.03-nosetup.zip**. Esta versión es portable y de **64 bits** (verifique que su sistema operativo cumpla con este requisito).
4. Una vez descargado, muévalo al Escritorio y descomprímalo.
5. Ejecute el archivo "**Cblauncher**". En la ventana de selección que aparece al iniciar, seleccione "**GNU GCC COMPILER**".

### **Creación y configuración del proyecto**

1. En **Code::Blocks**, diríjase a **File > New > Project** y seleccione **Console application**.
2. Asegúrese de elegir el **lenguaje C** y seleccione la ruta de su preferencia para guardar el proyecto. Verifique que estén marcados los perfiles de **Debug** y **Release**.
3. Descomprima los archivos del paquete **TP\_TOPICOS\_2026\_1C\_LUNES\_SINERGIA.zip** directamente en la carpeta recién creada para su proyecto donde se encuentran los archivos .cbp y main.c. Reemplace el archivo main.c base por el que viene dentro del .ZIP. Al volver a Code::Blocks, acepte la recarga de cambios si el IDE se lo solicita.
4. En **Code::Blocks**, vaya a **File --> Add files** y seleccione todos los archivos .c y .h extraídos. Al agregarlos, asegúrese de marcar las casillas **Debug** y **Release**.

### **Vinculación de biblioteca GBT**

[Link de descarga biblioteca GBT](#)

1. Ingrese al repositorio de la biblioteca a través del link provisto, haga clic en el botón **Code** y descárguelo como archivo **ZIP**.
2. Extraiga la carpeta **GBT\_v2026.1C.01** dentro del directorio raíz de su proyecto.
3. En **Code::Blocks**, haga clic derecho sobre el nombre de su proyecto y seleccione **Build options**.
4. Posicionado sobre el objetivo **Debug** (en el árbol de la izquierda), haga clic en la pestaña Linker settings. En el campo **Other linker options**, escriba: -lgbt.
5. Cambie a la pestaña **Search Directories**:
6. En la subpestaña **Compiler**, haga clic en **Add** y seleccione la ruta a la carpeta **include/** de la biblioteca **GBT**.
7. En la subpestaña **Linker**, haga clic en **Add** y seleccione la ruta a la carpeta **lib/** de la biblioteca **GBT**.
8. Presione **OK** para guardar todos los cambios.
9. Para que el programa pueda ejecutarse correctamente, copie el archivo **gbt.dll** (incluido en la biblioteca) y péguelo en la misma ruta donde se genera el archivo ejecutable .exe (**detallado en la sección 4**).

## 3. UBICACIÓN Y ESTRUCTURA DE ARCHIVOS

Para que el proyecto compile de forma organizada sin ningún tipo de error, los archivos deben estar distribuidos en la carpeta **donde se creó su proyecto** de la siguiente forma:

■ main.c → Punto de entrada del programa

■ graficos.c y graficos.h → Primitivas gráficas, paleta CGA/VGA y funciones de dibujo sobre GBT.

■ juego.c y juego.h → Bucle principal, estados del juego, configuración, puntuación y ranking.

■ letras.c y letras.h → Mapas de píxeles para letras, números y símbolos.

■ menu.c y menu.h → Menú principal, pausa, configuración, ranking y pantalla de game over.

■ pieza.c y pieza.h → Definición de tetrominos, rotación y sistema de bolsa de piezas.

■ presentacion.c y presentacion.h → Pantalla inicial para ingresar el nombre del jugador.

■ render.c y render.h → Dibujo del tablero, piezas, interfaz y textos.

■ tablero.c y tablero.h → Matriz del tablero, colisiones, movimiento y eliminación de filas.


## 4. GUÍA DE USO

Ya teniendo los archivos en la carpeta de su proyecto y biblioteca vinculada, sobre el nombre del proyecto pulse click derecho **"Build"** y luego **"Run" (F9)** ubicado en la toolbar para iniciar el juego.

**Alternativa:** También puede dirigirse directamente a la ruta **bin/Debug/** dentro de la carpeta de su proyecto y ejecutar de forma directa el archivo ejecutable **.exe** generado (recuerde que el archivo **gbt.dll** debe estar en esa misma carpeta).

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

Utilice las teclas **W/S** o las **Flechas Arriba/Abajo** para desplazarse verticalmente. Use las teclas **A/D** o las **Flechas Izquierda/Derecha** para modificar los valores de las opciones. Presione **ESC** si desea regresar al menú anterior. Para comenzar la partida, colóquese sobre la opción **"Jugar"** y presione **ENTER**.

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

La **velocidad** de caída del **tetromino** aumentará un **3%** automáticamente cada **10 piezas colocadas**. A mayor **velocidad** de juego, mayor será la **recompensa de puntos** obtenida por fila eliminada.