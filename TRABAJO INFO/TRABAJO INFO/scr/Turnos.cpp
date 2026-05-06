#include "Turnos.h"

// DEFINICIÓN VARIABLE
Bando turno = BUENOS;

void cambiarTurno() {
    turno = (turno == BUENOS ? MALOS : BUENOS);
}
