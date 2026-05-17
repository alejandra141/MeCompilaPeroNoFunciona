
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
    case 3: combate = new CombateBoxeo(); break;
    }
}

EstadoCombate::~EstadoCombate() {
    delete combate;
}

void EstadoCombate::actualizar() {
    combate->actualizar();
}

void EstadoCombate::dibujar() {
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
