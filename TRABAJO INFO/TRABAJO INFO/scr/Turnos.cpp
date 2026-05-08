#include "Turnos.h"

void Turnos::cambiarTurno()
{
	if (turnoActual == BUENOS)
		turnoActual = MALOS;
	else
		turnoActual = BUENOS;
};
