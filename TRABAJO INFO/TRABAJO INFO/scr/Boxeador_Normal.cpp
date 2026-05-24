#include "Boxeador_Normal.h"
#include "ETSIDI.h"

BoxeadorNormal::BoxeadorNormal(std::string pais, int numJugador)
    : Personaje("BoxeadorNormal", "boxeador_normal", pais, 80, 15, 10, numJugador) {
}

void BoxeadorNormal::cargarTextura() {
    std::string carpeta = (numJugador == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + pais + "/" + carpeta + "/BoxeadorNormal.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    sprite.setTextura(id);
}

std::vector<std::pair<int, int>> BoxeadorNormal::movimientosPosibles() {
    return {};
}
