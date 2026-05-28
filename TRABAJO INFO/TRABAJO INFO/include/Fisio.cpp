#include "Fisio.h"
#include "ETSIDI.h"
#include "Tablero.h"

Fisio::Fisio(std::string pais, int numJugador)
    : PersonajeTerrestre("Fisio", "fisio", pais, 60, 10, 8, numJugador) {
    getSprite().setOffset(0.5f, -0.75f);   // EJEMPLO
}


void Fisio::cargarTextura() {
    std::string carpeta = (getNumJugador() == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + getPais() + "/" + carpeta + "/Fisio.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    getSprite().setTextura(id);
}

std::vector<std::pair<int, int>> Fisio::movimientosPosibles() {
    return {};
}


//Los 7 hechizos del Fisio, cada uno con su propio método para lanzarlo.

// TELETRANSPORTACIÓN 

bool Fisio::lanzarTeleport(Personaje* aliado, int destFila, int destCol, Tablero& t) {

    if (usadoTeleport) return false;
    if (aliado == nullptr) return false;
    if (aliado->getNumJugador() != getNumJugador()) return false; // solo aliados
    if (t.hayPiezaEn(destFila, destCol)) return false; // casilla libre

    t.eliminarPersonaje(aliado);
    t.colocar(aliado, destFila, destCol);
    usadoTeleport = true;

    return true;

}

// CURACIÓN 
bool Fisio::lanzarHeal(Personaje* aliado) {
    if (usadoHeal) return false;
    if (aliado == nullptr) return false;
    if (aliado->getNumJugador() != getNumJugador()) return false;

    int curar = aliado->getVidaMax() - aliado->getVida();
    if (curar > 0) aliado->sanarVida(curar);
    usadoHeal = true;
    return true;
}

// INVIERTE LOS COLORES DEL TABLERO

bool Fisio::lanzarShiftTime(Tablero& t) {
    if (usadoShiftTime) return false;

    t.invertirCiclo(); 
    usadoShiftTime = true;
    return true;
}

// INTERCAMBIO DE POSICIONES

bool Fisio::lanzarExchange(Personaje* p1, Personaje* p2, Tablero& t) {
    if (usadoExchange) return false;
    if (p1 == nullptr || p2 == nullptr) return false;

    int f1 = p1->getFila(), c1 = p1->getColumna();
    int f2 = p2->getFila(), c2 = p2->getColumna();

    // Sacamos ambas del tablero
    t.eliminarPersonaje(p1);
    t.eliminarPersonaje(p2);

    // Las colocamos cruzadas
    t.colocar(p1, f2, c2);
    t.colocar(p2, f1, c1);

    usadoExchange = true;
    return true;
}

// ELIMINA PIEZA ENEMIGA (ES ESO DEL ELEMENTAL GANADO QUE VAMOS A HACER QUE SE QUEDE CON UNO Y YA)

bool Fisio::lanzarSummon(Personaje* enemigo, Tablero& t) {
    if (usadoSummon) return false;
    if (enemigo == nullptr) return false;
    if (enemigo->getNumJugador() == getNumJugador()) return false; // solo enemigos

    t.eliminarPersonaje(enemigo);
    // La pieza enemiga queda fuera del tablero; el Jugador rival
    // deberá llamar a j.eliminarPieza(enemigo) desde EstadoTablero
    usadoSummon = true;
    return true;
}

//  REVIVIR UNA PIEZUCA ALIADA

bool Fisio::lanzarRevive(Personaje* aliado, Tablero& t) {
    if (usadoRevive) return false;
    if (aliado == nullptr) return false;
    if (aliado->getNumJugador() != getNumJugador()) return false;
    if (aliado->estaVivo()) return false; // solo funciona con piezas muertas

    // Buscamos casilla libre adyacente al Fisio
    int filaLibre = -1, colLibre = -1;
    int df[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
    int dc[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

    for (int i = 0; i < 8; i++) {
        int nf = getFila() + df[i];
        int nc = getColumna() + dc[i];
        if (nf >= 0 && nf < 9 && nc >= 0 && nc < 9 && !t.hayPiezaEn(nf, nc)) {
            filaLibre = nf;
            colLibre = nc;
            break;
        }
    }

    if (filaLibre == -1) return false; // no hay hueco

    aliado->revivir(); // método que añadiremos en Personaje
    t.colocar(aliado, filaLibre, colLibre);
    usadoRevive = true;
    return true;
}

// ENCERRAMOS AL ENEMIGO QUE NO SALGA JAJAJ

bool Fisio::lanzarImprison(Personaje* enemigo) {
    if (usadoImprison) return false;
    if (enemigo == nullptr) return false;
    if (enemigo->getNumJugador() == getNumJugador()) return false;

    enemigo->encarcelar();
    usadoImprison = true;
    return true;
}
