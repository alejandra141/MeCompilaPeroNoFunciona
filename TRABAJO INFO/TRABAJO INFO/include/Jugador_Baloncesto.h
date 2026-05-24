#pragma once
#include "Personaje.h"

class JugadorBaloncesto : public Personaje {
public:
    JugadorBaloncesto(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
