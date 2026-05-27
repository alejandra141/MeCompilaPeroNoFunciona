#pragma once
#include "PersonajeTerrestre.h"

class BoxeadorNormal : public PersonajeTerrestre {
public:
    BoxeadorNormal(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
