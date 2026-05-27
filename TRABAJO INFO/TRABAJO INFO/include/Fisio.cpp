#include "Fisio.h"
#include "ETSIDI.h"

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
