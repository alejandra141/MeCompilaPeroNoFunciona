#pragma once
#include "EstadoJuego.h"
#include "Tablero.h"
class FlujoJuego;

class EstadoTablero : public EstadoJuego {
private:
    FlujoJuego* flujo;
    Tablero tablero;

public:
    EstadoTablero(FlujoJuego* f);

    void actualizar() override;
    void dibujar() override;
    void tecla(unsigned char key) override;
};
