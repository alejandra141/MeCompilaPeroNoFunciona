#include "FlujoJuego.h"
#include "EstadoSeleccionPais.h"    

FlujoJuego::FlujoJuego() {
    estadoActual = new EstadoSeleccionPais(this);
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
EstadoJuego* FlujoJuego::getEstado() { return estadoActual; }