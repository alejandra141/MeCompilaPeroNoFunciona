#pragma once
#include "EstadoJuego.h"

class FlujoJuego;

class EstadoInstrucciones : public EstadoJuego
{

private:
    FlujoJuego* flujo;
    float tiempo = 0.0f;

public:
    EstadoInstrucciones(FlujoJuego* f);
    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
    void teclaEspecial(int key) override;

};

