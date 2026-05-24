#include "Fisio.h"
#include "ETSIDI.h"

Fisio::Fisio(std::string pais, int numJugador)
    : Personaje("Fisio", "fisio", pais, 60, 10, 8, numJugador) {
}

void Fisio::cargarTextura() {
    std::string carpeta = (numJugador == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + pais + "/" + carpeta + "/Fisio.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    sprite.setTextura(id);
}

std::vector<std::pair<int, int>> Fisio::movimientosPosibles() {
    return {};
}
