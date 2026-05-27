#pragma once
#include "PersonajeSaltador.h"

class JugadorBaloncesto : public PersonajeSaltador {
public:
    JugadorBaloncesto(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};
