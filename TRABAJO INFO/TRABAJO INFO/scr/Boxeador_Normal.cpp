#include "Boxeador_Normal.h"
#include "ETSIDI.h"

BoxeadorNormal::BoxeadorNormal(std::string pais, int numJugador)
    : Personaje("BoxeadorNormal", "boxeador_normal", pais, 80, 15, 10, numJugador) {
    getSprite().setOffset(0.25f, -1.25f);   // EJEMPLO


}


void BoxeadorNormal::cargarTextura() {
    std::string carpeta = (getNumJugador() == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + getPais() + "/" + carpeta + "/BoxeadorNormal.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    getSprite().setTextura(id);
}

std::vector<std::pair<int, int>> BoxeadorNormal::movimientosPosibles() {
    return {};
}


