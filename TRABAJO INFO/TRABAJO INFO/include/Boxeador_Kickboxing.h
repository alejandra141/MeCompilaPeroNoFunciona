#pragma once
#include "PersonajeTeletransporte.h"

class BoxeadorKickboxing : public PersonajeTeletransporte {
public:
    BoxeadorKickboxing(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
