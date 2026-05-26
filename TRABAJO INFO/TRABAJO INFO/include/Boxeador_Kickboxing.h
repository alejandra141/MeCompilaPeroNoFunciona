//Boxeador_Kickboxing.h

#pragma once
#include "Personaje.h"

class BoxeadorKickboxing : public Personaje {
public:
    BoxeadorKickboxing(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
