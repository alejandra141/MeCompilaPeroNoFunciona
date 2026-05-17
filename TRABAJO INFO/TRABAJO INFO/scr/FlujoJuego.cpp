#include "FlujoJuego.h"
#include "EstadoTablero.h"

FlujoJuego::FlujoJuego() {
    estadoActual = new EstadoTablero(this);
}

FlujoJuego::~FlujoJuego() {
    delete estadoActual;
}

void FlujoJuego::cambiarEstado(EstadoJuego* nuevo) {
    delete estadoActual;
    estadoActual = nuevo;
}

void FlujoJuego::actualizar() {
    estadoActual->actualizar();
}

void FlujoJuego::dibujar() {
    estadoActual->dibujar();
}

void FlujoJuego::tecla(unsigned char key) {
    estadoActual->tecla(key);
}
