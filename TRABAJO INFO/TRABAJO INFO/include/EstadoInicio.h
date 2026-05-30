#pragma once
#include "EstadoJuego.h"
#include <string>

class FlujoJuego;

class EstadoInicio: public EstadoJuego
{

private:

    FlujoJuego* flujo;
	float tiempo = 0.0f;//para animar la cosa jajaj
    float pulsacion = 0.0f; //quiero poner parpadeo en el texto

public:

    EstadoInicio(FlujoJuego* f);
    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
    void teclaEspecial(int key) override;

};

