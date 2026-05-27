#pragma once
#include "PersonajeTerrestre.h"

//este va a ser el jugador de bolos normaluco

class BoloCranker : public PersonajeTerrestre {
public:
    BoloCranker(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
