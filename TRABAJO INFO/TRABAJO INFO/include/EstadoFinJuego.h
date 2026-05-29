#pragma once
#include <string>
#include "FlujoJuego.h"
#include"EstadoJuego.h"


class EstadoFinJuego : public EstadoJuego {
    FlujoJuego* flujo;
    int idGanador;
    float escala = 0.1f;
public:
    EstadoFinJuego(FlujoJuego* f, int id) {
        flujo = f;
        idGanador = id;
    }
    void dibujar();
    void tecla(unsigned char key) {}
    void mueve(double dt) override;
};

