#pragma once
#include "EstadoJuego.h"
#include "Combates.h"
class FlujoJuego;

class EstadoCombate : public EstadoJuego {
private:
    FlujoJuego* flujo;
    Combates* combate;

public:
    EstadoCombate(FlujoJuego* f, int tipo);
    ~EstadoCombate();

    void actualizar() override;
    void dibujar() override;
    void tecla(unsigned char key) override;
};
