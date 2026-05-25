#include "Jugador_Baloncesto.h"
#include "ETSIDI.h"

JugadorBaloncesto::JugadorBaloncesto(std::string pais, int numJugador)
    : Personaje("Baloncesto", "jugador_baloncesto", pais, 70, 20, 10, numJugador) {
    getSprite().setOffset(0.25f, 0.0f);   // EJEMPLO
}


void JugadorBaloncesto::cargarTextura() {
    std::string carpeta = (getNumJugador() == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + getPais() + "/" + carpeta + "/Baloncesto.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    getSprite().setTextura(id);
}

std::vector<std::pair<int, int>> JugadorBaloncesto::movimientosPosibles() {
    return {};
}
