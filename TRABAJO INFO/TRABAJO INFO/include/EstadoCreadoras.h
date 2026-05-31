#pragma once
#include "EstadoJuego.h"
#include <string>

class FlujoJuego;

class EstadoCreadoras : public EstadoJuego {
private:
    FlujoJuego* flujo;

public:
    EstadoCreadoras(FlujoJuego* f);
    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
    void teclaEspecial(int key) override;
};