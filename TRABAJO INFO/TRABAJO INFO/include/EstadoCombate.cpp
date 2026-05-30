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

    //para poder poner siempre al J1 a la derecha y al j2  a la izquierda tenemos que ordenarlos
    //usamos el operador ternario para que poder ordnarlo que si no 

    Personaje* pLuz = (atac->getNumJugador() == 1) ? atac : defen;
    Personaje* pOscuridad = (atac->getNumJugador() == 2) ? atac : defen;

    switch (tipo) {
    case 1:
        combate = new CombateBaloncesto(pOscuridad, pLuz);  
        break;
    case 2:
        combate = new CombateBolos(pOscuridad, pLuz);
        break;
    case 3:
        combate = new CombateBoxeo(pOscuridad, pLuz, false);
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

                // ganador 1 = ganó pOscuridad (que pasamos primero al combate)
                // ganador 2 = ganó pLuz (que pasamos segundo)
                Personaje* pLuz = (atacante->getNumJugador() == 1) ? atacante : defensor;
                Personaje* pOscuridad = (atacante->getNumJugador() == 2) ? atacante : defensor;

                Personaje* vencedor = (ganador == 1) ? pOscuridad : pLuz;
                Personaje* perdedor = (ganador == 1) ? pLuz : pOscuridad;

                tablero.eliminarPersonaje(perdedor);
                tablero.colocar(vencedor, filaDestino, colDestino);
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

