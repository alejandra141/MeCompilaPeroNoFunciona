

//EstadoCombate.cpp

#include "EstadoCombate.h"
#include "FlujoJuego.h"
#include "EstadoTablero.h"
#include "CombateBaloncesto.h"
#include "CombateBolos.h"
#include "CombateBoxeo.h"
#include "Boxeador.h"

EstadoCombate::EstadoCombate(FlujoJuego* f, int tipo,
    const std::string& pJ1,
    const std::string& pJ2,
    Personaje* p1,
    Personaje* p2)
    : flujo(f), paisJ1(pJ1), paisJ2(pJ2)
{
    switch (tipo) {
    case 1: {
        Basketboller* player1 = new Basketboller(pJ1, 3, -8.0f, -3.0f, 0.0f);  // sin estela
        Basketboller* player2 = new Basketboller(pJ2, 10, 8.0f, -3.0f, 0.0f);  // con estela

        //metemos los sprites reales del tablero
        if (p1 != nullptr) {
            player1->setTextureID(p1->getSprite().getTexID());
        }
        if (p2 != nullptr) {
            player2->setTextureID(p2->getSprite().getTexID());
        }

        combate = new CombateBaloncesto(player1, player2);
        break;
    }
    case 2: {
        // ponemos p1 (atacante) y p2 (defensor) directos al minijuego de bolos
        combate = new CombateBolos(p1, p2);
        break;
    }
    case 3: {
        Boxeador* b1 = new Boxeador();
        Boxeador* b2 = new Boxeador();

        b1->inicializar(1);
        b2->inicializar(2);

        //metemos los sprites reales del tablero
        if (p1 != nullptr) {
            b1->recibirDanio(100 - p1->getVida());
            // Sacamos el ID de la textura que cargó el personaje en el tablero y se la damos al boxeador 1
            b1->setTextureID(p1->getSprite().getTexID());
        }
        if (p2 != nullptr) {
            b2->recibirDanio(130 - p2->getVida());
            // Hacemos lo mismo para el rival
            b2->setTextureID(p2->getSprite().getTexID());
        }

        combate = new CombateBoxeo(b1, b2, false);
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



void EstadoCombate::tecla(unsigned char key) {  //ESTO ES PRINCIPALMente PARA VOLVER DE COMBATE A TABLERO

    //CUANDO FINALIZA EL COMBATE
    if (combate->haTerminado()) {
        if (key == 'c' || key == 'C') {
            flujo->cambiarEstado(new EstadoTablero(flujo, paisJ1, paisJ2));
        }
        return; // No pasar teclas al combate
    }

    // MANUALMENTE VOLVER AL TABLER
    if (key == 'b') {
        flujo->cambiarEstado(new EstadoTablero(flujo, paisJ1, paisJ2));
        return;
    }

    // PASAR TECLAS AL COMBATE  
    combate->tecla(key);
}



void EstadoCombate::teclaSuelta(unsigned char key) {
    combate->teclaSuelta(key);
}
void EstadoCombate::teclaEspecial(int key) {
    combate->teclaEspecial(key);
}
void EstadoCombate::teclaEspecialSuelta(int key) {
    combate->teclaEspecialSuelta(key);
}

