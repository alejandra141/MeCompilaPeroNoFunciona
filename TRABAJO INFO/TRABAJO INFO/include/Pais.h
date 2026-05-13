#pragma once
#include <string>

enum class Pais {
    ESPANA,
    FRANCIA,
    ITALIA,
    INGLATERRA,
    USA,
    DESCONOCIDO;
};

Pais paisDesdeTexto(const std::string& p); //declaración de funcion que convierte texto de consola en un miembro de enum pais (QUITARCUANDO PANTALLA INICIO)
std::string texturaPersonaje(Pais pais, const std::string& tipo); //La función que devuelve la textura según país y tipo de personaje (NO QUITAR)
