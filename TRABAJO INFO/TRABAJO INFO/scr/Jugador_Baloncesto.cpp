#include "Jugador_Baloncesto.h"
#include "ETSIDI.h"

JugadorBaloncesto::JugadorBaloncesto(std::string pais, int numJugador)
    : Personaje("Baloncesto", "jugador_baloncesto", pais, 70, 20, 10, numJugador) {
}

void JugadorBaloncesto::cargarTextura() {
    std::string carpeta = (numJugador == 1) ? "buenos" : "malos";
    std::string ruta = "Personajes/" + pais + "/" + carpeta + "/Baloncesto.png";

    unsigned int id = ETSIDI::getTexture(ruta.c_str()).id;
    sprite.setTextura(id);
}

std::vector<std::pair<int, int>> JugadorBaloncesto::movimientosPosibles() {
    return {};
}
