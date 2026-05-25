#include "Boxeador_Kickboxing.h"
#include "ETSIDI.h"

BoxeadorKickboxing::BoxeadorKickboxing(std::string pais, int numJugador)
    : Personaje("BoxeadorKickboxing", "boxeador_kickboxing", pais, 85, 17, 11, numJugador) {
    getSprite().setOffset(0.5f, -1.0f);   // EJEMPLO
}


void BoxeadorKickboxing::cargarTextura() {
    std::string carpeta = (getNumJugador() == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + getPais() + "/" + carpeta + "/BoxeadorKickboxing.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    getSprite().setTextura(id);
}

std::vector<std::pair<int, int>> BoxeadorKickboxing::movimientosPosibles() {
    return {};
}
