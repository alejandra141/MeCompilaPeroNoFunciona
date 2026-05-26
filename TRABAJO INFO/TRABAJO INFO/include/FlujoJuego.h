#pragma once
#include "EstadoJuego.h"

class FlujoJuego {
private:
    EstadoJuego* estadoActual;

public:
    FlujoJuego();
    ~FlujoJuego();

    void cambiarEstado(EstadoJuego* nuevo);

    void mueve(double dt);
    void dibujar();
    void tecla(unsigned char key);
    void teclaSuelta(unsigned char key);
    EstadoJuego* getEstado();
};
