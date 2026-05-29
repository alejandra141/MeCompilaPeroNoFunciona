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


void EstadoSeleccionPais::mueve(double dt) {

    if (selector.listos) {
        selector.tiempoEspera += (float)dt;
        if (selector.tiempoEspera > 1.0f) {
            selector.listos = false;

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

        selector.listos = true;
        selector.tiempoEspera = 0.0f;
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

        selector.listos = true;
        selector.tiempoEspera = 0.0f;
    }
}
