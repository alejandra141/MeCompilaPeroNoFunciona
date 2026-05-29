#include "PersonajeTerrestre.h"
#include "Tablero.h"


//Este tipo de movimiento hace que se mueva 1 casilla en cualquier dirección no diagonal

bool PersonajeTerrestre::esMovimientoValido(int destFila, int destColumna, Tablero* tablero) {

    if (estaEncarcelada()) return false;//por si el fisio lo ha encerrado

    // no permite diagonales
    if (destFila != getFila() && destColumna != getColumna()) return false;

    // no supera su rango de paso máximo
    int distancia = std::abs(destFila - getFila()) + std::abs(destColumna - getColumna());
    if (distancia > radioMovimiento) return false;

    // no puede atravesar casillas ocupadas
    if (destFila != getFila()) {
        int paso = (destFila > getFila()) ? 1 : -1;
        for (int f = getFila() + paso; f != destFila; f += paso)
            if (tablero->hayPiezaEn(f, getColumna())) return false;
    }
    else {
        int paso = (destColumna > getColumna()) ? 1 : -1;
        for (int c = getColumna() + paso; c != destColumna; c += paso)
            if (tablero->hayPiezaEn(getFila(), c)) return false;
    }

    // no puede terminar sobre una pieza aliada
    if (tablero->getBandoPiezaEn(destFila, destColumna) == getNumJugador()) return false;

    return true;
}