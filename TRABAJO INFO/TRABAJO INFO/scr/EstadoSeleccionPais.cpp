#include "EstadoSeleccionPais.h"
#include "FlujoJuego.h"
#include "EstadoTablero.h"
#include <GL/freeglut.h>

EstadoSeleccionPais::EstadoSeleccionPais(FlujoJuego* f)
    : flujo(f) {
}

void EstadoSeleccionPais::dibujar() {
    selector.dibuja();
}


void EstadoSeleccionPais::teclaEspecial(int key) {

    switch (key) {

    case GLUT_KEY_UP:
        selector.moverJ1(-1);   // J1 = derecha
        break;

    case GLUT_KEY_DOWN:
        selector.moverJ1(1);    // J1 = derecha
        break;
    }

    if (selector.seleccionCompleta()) {
        flujo->cambiarEstado(
            new EstadoTablero(
                flujo,
                selector.getPaisJ1(),   // DERECHA = J1
                selector.getPaisJ2()    // IZQUIERDA = J2
            )
        );
    }
}

//  WASD : JUGADOR 2 (izquierda)
//  ENTER : confirma J1
//  ESPACIO : confirma J2

void EstadoSeleccionPais::tecla(unsigned char key) {

    switch (key) {

        // Movimiento J2 (izquierda)
    case 'w':
    case 'W':
        selector.moverJ2(-1);
        break;

    case 's':
    case 'S':
        selector.moverJ2(1);
        break;

        // Confirmación J2 (izquierda)
    case ' ':
        selector.confirmarJ2();
        break;

        // Confirmación J1 (derecha)
    case 13:   // ENTER
        selector.confirmarJ1();
        break;
    }

    if (selector.seleccionCompleta()) {
        flujo->cambiarEstado(
            new EstadoTablero(
                flujo,
                selector.getPaisJ1(),   // DERECHA = J1
                selector.getPaisJ2()    // IZQUIERDA = J2
            )
        );
    }
}

