#include "PersonajeSaltador.h"
#include "Tablero.h"

//Este tipo de movimiento permite diagonales y salta obstáculos

bool PersonajeSaltador::esMovimientoValido(int destFila, int destColumna, Tablero* tablero) {

	if (estaEncarcelada()) return false;//por si el fisio lo ha encerrado       

    // distancia máxima en cualquier eje (permite diagonales)
    int distFila = std::abs(destFila - getFila());
    int distCol = std::abs(destColumna - getColumna());
    if (distFila > radioMovimiento || distCol > radioMovimiento) return false;

    // puede saltar obstáculos — no se comprueba camino intermedio

    // no puede aterrizar sobre un aliado
    if (tablero->getBandoPiezaEn(destFila, destColumna) == getNumJugador()) return false;

    return true;
}