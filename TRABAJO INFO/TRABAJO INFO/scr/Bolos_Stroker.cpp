#include "Bolos_Stroker.h"
#include "ETSIDI.h"

BoloStronker::BoloStronker(std::string pais, int numJugador)
    : Personaje("Stronker", "bolo_stronker", pais, 110, 12, 15, numJugador) {
    getSprite().setOffset(1.0f, -1.5f);   // EJEMPLO
}


void BoloStronker::cargarTextura() {
    std::string carpeta = (getNumJugador() == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + getPais() + "/" + carpeta + "/Stronker.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    getSprite().setTextura(id);
}

std::vector<std::pair<int, int>> BoloStronker::movimientosPosibles() {
    return {};
}
