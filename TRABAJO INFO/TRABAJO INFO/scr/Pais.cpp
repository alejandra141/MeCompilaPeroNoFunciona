#include "Pais.h"

Pais paisDesdeTexto(const std::string& p) {
    if (p == "espana" || p == "españa") return Pais::ESPANA;
    if (p == "francia") return Pais::FRANCIA;
    if (p == "italia") return Pais::ITALIA;
    if (p == "inglaterra") return Pais::INGLATERRA;
    if (p == "usa") return Pais::USA;

    return Pais::DESCONOCIDO;
  
}

std::string texturaPersonaje(Pais pais, const std::string& tipo, int jugador) {

    std::string lado = (jugador == 1 ? "buenos" : "malos");

    switch (pais) {
    case Pais::ESPANA:
        if (tipo == "boxeo") return "Personajes/Espana/" + lado + "/BoxeadorNormal_ESP.png";
        if (tipo == "kickboxing") return "Personajes/Espana/" + lado + "/BoxeadorKickboxing_ESP.png";
        if (tipo == "cranker") return "Personajes/Espana/" + lado + "/Cranker_ESP.png";
        if (tipo == "stroker") return "Personajes/Espana/" + lado + "/Stroker_ESP.png";
        if (tipo == "baloncesto") return "Personajes/Espana/" + lado + "/Baloncesto_ESP.png";
        if (tipo == "extra") return "Personajes/Espana/" + lado + "/fisio.png";
        break;

    case Pais::FRANCIA:
        if (tipo == "boxeo") return "Personajes/Francia/" + lado + "/BoxeadorNormal_FRA.png";
        if (tipo == "kickboxing") return "Personajes/Francia/" + lado + "/BoxeadorKickboxing_FRA.png";
        if (tipo == "cranker") return "Personajes/Francia/" + lado + "/Cranker_FRA.png";
        if (tipo == "stroker") return "Personajes/Francia/" + lado + "/Stroker_FRA.png";
        if (tipo == "baloncesto") return "Personajes/Francia/" + lado + "/Baloncesto_FRA.png";
        if (tipo == "extra") return "Personajes/Francia/" + lado + "/fisio.png";
        break;


    case Pais::USA:
        if (tipo == "boxeo") return "Personajes/Usa/" + lado + "/BoxeadorNormal_USA.png";
        if (tipo == "kickboxing") return "Personajes/Usa/" + lado + "/BoxeadorKickboxing_USA.png";
        if (tipo == "cranker") return "Personajes/Usa/" + lado + "/Cranker_USA.png";
        if (tipo == "stroker") return "Personajes/Usa/" + lado + "/Stroker_USA.png";
        if (tipo == "baloncesto") return "Personajes/Usa/" + lado + "/Baloncesto_USA.png";
        if (tipo == "extra") return "Personajes/Usa/" + lado + "/fisio.png";
        break;

    case Pais::ITALIA:
        if (tipo == "boxeo") return "Personajes/Italia/" + lado + "/BoxeadorNormal_ITA.png";
        if (tipo == "kickboxing") return "Personajes/Italia/" + lado + "/BoxeadorKickboxing_ITA.png";
        if (tipo == "cranker") return "Personajes/Italia/" + lado + "/Cranker_ITA.png";
        if (tipo == "stroker") return "Personajes/Italia/" + lado + "/Stroker_ITA.png";
        if (tipo == "baloncesto") return "Personajes/Italia/" + lado + "/Baloncesto_ITA.png";
        if (tipo == "extra") return "Personajes/Italia/" + lado + "/fisio.png";
        break;

    case Pais::INGLATERRA:
        if (tipo == "boxeo") return "Personajes/Inglaterra/" + lado + "/BoxeadorNormal_ING.png";
        if (tipo == "kickboxing") return "Personajes/Inglaterra/" + lado + "/BoxeadorKickboxing_ING.png";
        if (tipo == "cranker") return "Personajes/Inglaterra/" + lado + "/Cranker_ING.png";
        if (tipo == "stroker") return "Personajes/Inglaterra/" + lado + "/Stroker_ING.png";
        if (tipo == "baloncesto") return "Personajes/Inglaterra/" + lado + "/Baloncesto_ING.png";
        if (tipo == "extra") return "Personajes/Inglaterra/" + lado + "/fisio.png";
        break;
    }

    return "texturas/default.png";
}