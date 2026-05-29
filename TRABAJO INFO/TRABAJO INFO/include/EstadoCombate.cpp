

//EstadoCombate.cpp

#include "EstadoCombate.h"
#include "FlujoJuego.h"
#include "EstadoTablero.h"
#include "CombateBaloncesto.h"
#include "CombateBolos.h"
#include "CombateBoxeo.h"
#include "Tablero.h"



extern Tablero tablero;


EstadoCombate::EstadoCombate(FlujoJuego* f, int tipo,
    const std::string& pJ1, const std::string& pJ2,
    Personaje* atac, Personaje* defen,
    int fila, int col)
    : flujo(f), paisJ1(pJ1), paisJ2(pJ2),
    atacante(atac), defensor(defen),
    filaDestino(fila), colDestino(col)
{
    switch (tipo) {
    case 1:
        combate = new CombateBaloncesto(atac, defen);  
        break;
    case 2:
        combate = new CombateBolos(atac, defen);
        break;
    case 3:
        combate = new CombateBoxeo(atac, defen, false);
        break;
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

    if (combate->haTerminado()) {

        if (key == 'c' || key == 'C') {

            if (atacante != nullptr && defensor != nullptr) {

                int ganador = combate->getGanador();

                Personaje* vencedor = (ganador == 1) ? atacante : defensor;
                Personaje* perdedor = (ganador == 1) ? defensor : atacante;

                // 1. Eliminar solo al perdedor
                tablero.eliminarPersonaje(perdedor);

                // 2. Colocar al vencedor en la casilla donde estaba el defensor
                tablero.colocar(vencedor, filaDestino, colDestino);

                // 3. La vida del vencedor ya está actualizada por el combate
                //    No hay que hacer nada más
            }

            flujo->cambiarEstado(new EstadoTablero(flujo, paisJ1, paisJ2));
        }

        return;
    }

    if (key == 'b') {
        flujo->cambiarEstado(new EstadoTablero(flujo, paisJ1, paisJ2));
        return;
    }

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

