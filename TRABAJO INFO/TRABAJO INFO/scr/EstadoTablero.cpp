#include "EstadoTablero.h"
#include "FlujoJuego.h"
#include "EstadoCombate.h"

EstadoTablero::EstadoTablero(FlujoJuego* f) : flujo(f) {}

void EstadoTablero::actualizar() {}

void EstadoTablero::dibujar() {
    tablero.dibuja();
}

void EstadoTablero::tecla(unsigned char key) {
    if (key == '1') flujo->cambiarEstado(new EstadoCombate(flujo, 1));
    if (key == '2') flujo->cambiarEstado(new EstadoCombate(flujo, 2));
    if (key == '3') flujo->cambiarEstado(new EstadoCombate(flujo, 3));
}
