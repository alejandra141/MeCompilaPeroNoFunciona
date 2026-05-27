#pragma once
#include "Personaje.h"

class PersonajeSaltador : public Personaje{

public:

	PersonajeSaltador(std::string nombre, std::string tipo, std::string pais,
		int vida, int ataque, int defensa, int numJugador)
		: Personaje(nombre, tipo, pais, vida, ataque, defensa, numJugador) {
	}

	bool esMovimientoValido(int destFila, int destColumna, Tablero* tablero) override;
};

