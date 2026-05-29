#pragma once
#include <string>
#include "FlujoJuego.h"
#include"EstadoJuego.h"

class EstadoFinJuego : public EstadoJuego {
    FlujoJuego* flujo;
    int idGanador;

public:
    EstadoFinJuego(FlujoJuego* f, int id) {
        flujo = f;
        idGanador = id;
    }
    void dibujar();
    void mueve(double dt) {}
    void tecla(unsigned char key) {}
};

