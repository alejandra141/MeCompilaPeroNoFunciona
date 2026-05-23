#pragma once
#include "EstadoJuego.h"

class FlujoJuego {
private:
    EstadoJuego* estadoActual;

public:
    FlujoJuego();
    ~FlujoJuego();

    void cambiarEstado(EstadoJuego* nuevo);

    void mueve();
    void dibujar();
    void tecla(unsigned char key);
};
