#include "EstadoSeleccionPais.h"
#include "FlujoJuego.h"
#include "EstadoTablero.h"

EstadoSeleccionPais::EstadoSeleccionPais(FlujoJuego* f) : flujo(f) {}

void EstadoSeleccionPais::mueve(double dt) {}
void EstadoSeleccionPais::tecla(unsigned char key) {}

void EstadoSeleccionPais::dibujar() {
    selector.dibuja();
}

void EstadoSeleccionPais::click(float mx, float my) {
    bool listo = selector.update(mx, my, true);
    if (listo) {
        flujo->cambiarEstado(
            new EstadoTablero(flujo,
                selector.getPaisJ1(),
                selector.getPaisJ2()));
    }
}