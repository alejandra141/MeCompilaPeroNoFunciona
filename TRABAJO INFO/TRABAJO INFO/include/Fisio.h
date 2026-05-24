#pragma once
#include "Personaje.h"

class Fisio : public Personaje {
public:
    Fisio(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
