#include "EstadoSeleccionPais.h"
#include "FlujoJuego.h"
#include "EstadoTablero.h"
#include <GL/freeglut.h>

extern Tablero tablero;

EstadoSeleccionPais::EstadoSeleccionPais(FlujoJuego* f)
    : flujo(f) {
}

void EstadoSeleccionPais::dibujar() {
    selector.dibuja();
}

void EstadoSeleccionPais::teclaEspecial(int key) {

    switch (key) {

    case GLUT_KEY_UP:
        selector.moverJ1(-1);
        break;

    case GLUT_KEY_DOWN:
        selector.moverJ1(1);
        break;
    }

    if (selector.seleccionCompleta()) {

        // 1. Obtener jugadores reales
        Jugador* j1 = flujo->getJugador1();
        Jugador* j2 = flujo->getJugador2();

        // 2. Asignar países
        j1->setPais(selector.getPaisJ1());
        j2->setPais(selector.getPaisJ2());

        // 3. Crear piezas una sola vez
        j1->inicializarPiezas();
        j2->inicializarPiezas();

        // 4. Colocar piezas en el tablero
        tablero.inicializarJ1(*j2);   // izquierda
        tablero.inicializarJ2(*j1);   // derecha

        // 5. Cambiar al tablero
        flujo->cambiarEstado(
            new EstadoTablero(
                flujo,
                selector.getPaisJ1(),
                selector.getPaisJ2()
            )
        );
    }
}

void EstadoSeleccionPais::tecla(unsigned char key) {

    switch (key) {

    case 'w':
    case 'W':
        selector.moverJ2(-1);
        break;

    case 's':
    case 'S':
        selector.moverJ2(1);
        break;

    case ' ':
        selector.confirmarJ2();
        break;

    case 13: // ENTER
        selector.confirmarJ1();
        break;
    }

    if (selector.seleccionCompleta()) {

        Jugador* j1 = flujo->getJugador1();
        Jugador* j2 = flujo->getJugador2();

        j1->setPais(selector.getPaisJ1());
        j2->setPais(selector.getPaisJ2());

        j1->inicializarPiezas();
        j2->inicializarPiezas();

        tablero.inicializarJ1(*j1);
        tablero.inicializarJ2(*j2);

        flujo->cambiarEstado(
            new EstadoTablero(
                flujo,
                selector.getPaisJ1(),
                selector.getPaisJ2()
            )
        );
    }
}
