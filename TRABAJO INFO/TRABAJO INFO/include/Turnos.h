#pragma once

enum bandos
{
	BUENOS,
	MALOS
};

class Turnos {
private:
	int numeroCiclo = 0; //esto es para el contador de ciclos para el encarcelamiento del hechizo del fisio madre mía
	bandos turnoActual;

public:
	Turnos() { turnoActual = BUENOS; };
	bandos getTurnoActual() { return turnoActual; };

	void cambiarTurno();

	int getNumeroCiclo() const { return numeroCiclo; }// necesitamos la función esta para el hechizo del fisio me tiene cansada ya el fisio
};

