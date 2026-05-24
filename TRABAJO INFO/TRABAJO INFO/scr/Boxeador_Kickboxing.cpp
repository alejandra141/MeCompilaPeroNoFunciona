#include "Boxeador_Kickboxing.h"
#include "ETSIDI.h"

BoxeadorKickboxing::BoxeadorKickboxing(std::string pais, int numJugador)
    : Personaje("BoxeadorKickboxing", "boxeador_kickboxing", pais, 85, 17, 11, numJugador) {
}

void BoxeadorKickboxing::cargarTextura() {
    std::string carpeta = (numJugador == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + pais + "/" + carpeta + "/BoxeadorKickboxing.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    sprite.setTextura(id);
}

std::vector<std::pair<int, int>> BoxeadorKickboxing::movimientosPosibles() {
    return {};
}
