#pragma once
#include "PersonajeTerrestre.h"

class Fisio : public PersonajeTerrestre {
public:

    Fisio(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
