#pragma once
#include "Personaje.h"

class BoloCranker : public Personaje {
public:
    BoloCranker(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
