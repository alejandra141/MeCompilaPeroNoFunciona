#include "Bolos_Stroker.h"
#include "ETSIDI.h"

BoloStronker::BoloStronker(std::string pais, int numJugador)
    : Personaje("Stronker", "bolo_stronker", pais, 110, 12, 15, numJugador) {
}

void BoloStronker::cargarTextura() {
    std::string carpeta = (numJugador == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + pais + "/" + carpeta + "/Stronker.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    sprite.setTextura(id);
}

std::vector<std::pair<int, int>> BoloStronker::movimientosPosibles() {
    return {};
}
