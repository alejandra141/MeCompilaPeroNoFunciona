#include "PersonajeTeletransporte.h"
#include "Tablero.h"

//Este movimiento hace un salto instantáneo a cualquier casilla


bool PersonajeTeletransporte::esMovimientoValido(int destFila, int destColumna, Tablero* tablero) {

    // sin restricción de distancia ni obstáculos

    // única restricción: no puede caer sobre un aliado
    if (tablero->getBandoPiezaEn(destFila, destColumna) == getNumJugador()) return false;

    return true;
}