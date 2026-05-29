

//EstadoCombate.cpp

#include "EstadoCombate.h"
#include "FlujoJuego.h"
#include "EstadoTablero.h"
#include "CombateBaloncesto.h"
#include "CombateBolos.h"
#include "CombateBoxeo.h"


EstadoCombate::EstadoCombate(FlujoJuego* f, int tipo,
    const std::string& pJ1,
    const std::string& pJ2,
    Personaje* p1,
    Personaje* p2)
    : flujo(f), paisJ1(pJ1), paisJ2(pJ2)
{
    switch (tipo) {
    case 1: {
        
        
        combate = new CombateBaloncesto(p1, p2);
        break;
    }
    case 2: {
        // Ya estaba bien
        combate = new CombateBolos(p1, p2);
        break;
    }
    case 3: {
        // Pasamos los personajes reales directamente

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

