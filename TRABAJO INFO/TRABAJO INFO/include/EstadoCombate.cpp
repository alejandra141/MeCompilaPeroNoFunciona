
#include "EstadoCombate.h"
#include "FlujoJuego.h"
#include "EstadoTablero.h"
#include "CombateBaloncesto.h"
#include "CombateBolos.h"
#include "CombateBoxeo.h"

EstadoCombate::EstadoCombate(FlujoJuego* f, int tipo) : flujo(f) {
    switch (tipo) {
    case 1: combate = new CombateBaloncesto(); break;
    case 2: combate = new CombateBolos(); break;
    case 3: {
        // Creamos los dos boxeadores
        Boxeador* p1 = new Boxeador_Normal(1);       // Jugador 1
        Boxeador* p2 = new Boxeador_Kickboxing(2);   // Jugador 2 o IA

        bool contraIA = false;  // true = IA, false = jugador 2

        combate = new CombateBoxeo(p1, p2, contraIA);
        break;
    }
    }
}

EstadoCombate::~EstadoCombate() {
    delete combate;
}

void EstadoCombate::actualizar() {
    combate->actualizar();
}

void EstadoCombate::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //ESTO ES PARA LIMPIAR LO DE LA PANTALLA ANTERIOR
    combate->dibujar();
}

void EstadoCombate::tecla(unsigned char key) {
    if (key == 'b') {
        flujo->cambiarEstado(new EstadoTablero(flujo));
    }
    else {
        combate->tecla(key);
    }
}
