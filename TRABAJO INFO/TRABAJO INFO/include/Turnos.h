#pragma once

enum bandos
{
	BUENOS,
	MALOS
};

class Turnos {
private:
	bandos turnoActual;

public:
	Turnos() { turnoActual = BUENOS; };
	bandos getTurnoActual() { return turnoActual; };

	void cambiarTurno();
};

