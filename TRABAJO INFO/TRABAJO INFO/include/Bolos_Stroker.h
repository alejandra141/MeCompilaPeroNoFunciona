#pragma once
#include "Personaje.h"

class BoloStronker : public Personaje {
public:
    BoloStronker(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
