#include "Bolos_Cranker.h"

BoloCranker::BoloCranker(std::string pais, int numJugador)
    : Personaje("Cranker", "bolo_cranker", pais, 90, 18, 12, numJugador) {
}

void BoloCranker::cargarTextura() {
    std::string carpeta = (numJugador == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + pais + "/" + carpeta + "/Cranker.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    sprite.setTextura(id);
}


std::vector<std::pair<int, int>> BoloCranker::movimientosPosibles() {
    return {};
}
