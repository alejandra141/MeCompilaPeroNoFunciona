#include "FlujoJuego.h"
#include "EstadoSeleccionPais.h"   
#include "EstadoTablero.h"
#include "EstadoInicio.h"

FlujoJuego::FlujoJuego()
    : jugador1(1), jugador2(2)   
{
    estadoActual = new EstadoInicio(this);
}
FlujoJuego::~FlujoJuego() {
    delete estadoActual;
}
void FlujoJuego::cambiarEstado(EstadoJuego* nuevo) {
    delete estadoActual;
    estadoActual = nuevo;
}
void FlujoJuego::mueve(double dt) { estadoActual->mueve(dt); }
void FlujoJuego::dibujar() { estadoActual->dibujar(); }
void FlujoJuego::tecla(unsigned char key) { estadoActual->tecla(key); }
void FlujoJuego::teclaSuelta(unsigned char key) {
    estadoActual->teclaSuelta(key);
}
    EstadoJuego* FlujoJuego::getEstado() { return estadoActual; }
   
void FlujoJuego::teclaEspecial(int key) {
    estadoActual->teclaEspecial(key);
}
void FlujoJuego::teclaEspecialSuelta(int key) {
    estadoActual->teclaEspecialSuelta(key);
}

EstadoTablero* FlujoJuego::getEstadoTablero() {
    return dynamic_cast<EstadoTablero*>(estadoActual);
    // devuelve nullptr si no estamos en el tablero
}