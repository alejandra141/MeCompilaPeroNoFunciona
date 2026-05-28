#pragma once
#include "Personaje.h"

class PersonajeTerrestre : public Personaje {

public:
	PersonajeTerrestre(std::string nombre, std::string tipo, std::string pais,
		int vida, int ataque, int defensa, int numJugador)
		: Personaje(nombre, tipo, pais, vida, ataque, defensa, numJugador) {
		radioMovimiento = 3; // los bolos se mueven 3 casillas
	}

	bool esMovimientoValido(int destFila, int destColumna, Tablero* tablero) override;

};
