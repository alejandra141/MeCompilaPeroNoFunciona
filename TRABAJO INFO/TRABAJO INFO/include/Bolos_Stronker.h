//Bolos_Stronker.h

#pragma once
#include "PersonajeSaltador.h"

//este va a ser el jugador de bolos experto

class BoloStronker : public PersonajeSaltador {
public:
    BoloStronker(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;
};

