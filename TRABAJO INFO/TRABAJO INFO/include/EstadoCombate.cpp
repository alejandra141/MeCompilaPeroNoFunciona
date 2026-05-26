
#include "EstadoCombate.h"
#include "FlujoJuego.h"
#include "EstadoTablero.h"
#include "CombateBaloncesto.h"
#include "CombateBolos.h"
#include "CombateBoxeo.h"
#include "Boxeador.h"

EstadoCombate::EstadoCombate(FlujoJuego* f, int tipo,
    const std::string& pJ1,
    const std::string& pJ2)
    : flujo(f), paisJ1(pJ1), paisJ2(pJ2)
{
    switch (tipo) {
    case 1: {
        Basketboller* p1 = new Basketboller(pJ1, 3, -8.0f, -3.0f, 0.0f);  // sin estela
        Basketboller* p2 = new Basketboller(pJ2, 10, 8.0f, -3.0f, 0.0f);  // con estela
        combate = new CombateBaloncesto(p1, p2);
        break;
    }
    case 2: {
        Bolerito* p1 = new Bolerito(pJ1, false);
        Bolerito* p2 = new Bolerito(pJ2, false);
        combate = new CombateBolos(p1, p2);
        break;

    };
    case 3: {
        Boxeador* p1 = new Boxeador();   
        Boxeador* p2 = new Boxeador();

        combate = new CombateBoxeo(p1, p2, false);
        break;
    }

    }
}

EstadoCombate::~EstadoCombate() {
    delete combate;
}

void EstadoCombate::mueve(double dt) {
    combate->mueve(dt);
}

void EstadoCombate::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    combate->dibujar();
}

void EstadoCombate::tecla(unsigned char key) {
    if (key == 'b') {
        // Vuelve al tablero con los países guardados
        flujo->cambiarEstado(new EstadoTablero(flujo, paisJ1, paisJ2));
    }
    else {
        combate->tecla(key);
    }
}
void EstadoCombate::teclaSuelta(unsigned char key) {
    combate->teclaSuelta(key);
}