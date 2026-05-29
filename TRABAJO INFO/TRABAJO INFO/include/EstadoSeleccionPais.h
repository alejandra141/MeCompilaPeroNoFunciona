#pragma once
#include "EstadoJuego.h"
#include "SeleccionPais.h"

class FlujoJuego;

class EstadoSeleccionPais : public EstadoJuego {
private:
    FlujoJuego* flujo;
    SelectorPais selector;

public:
    EstadoSeleccionPais(FlujoJuego* f);

    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
    void teclaEspecial(int key) override;
};
