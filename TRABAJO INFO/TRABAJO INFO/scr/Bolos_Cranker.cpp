#include "Bolos_Cranker.h"

BoloCranker::BoloCranker(std::string pais, int numJugador)
    : PersonajeTerrestre("Cranker", "bolo_cranker", pais, 90, 18, 12, numJugador) {
    getSprite().setOffset(1.0f, -1.0f);   //para eliminar el offset al pegar la imagen
}

void BoloCranker::cargarTextura() {
    std::string carpeta = (getNumJugador() == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + getPais() + "/" + carpeta + "/Cranker.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    getSprite().setTextura(id);
}


std::vector<std::pair<int, int>> BoloCranker::movimientosPosibles() {
    return {};
}
