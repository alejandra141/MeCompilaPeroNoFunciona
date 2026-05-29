#pragma once
#include "PersonajeTerrestre.h"

class Tablero;

class Fisio : public PersonajeTerrestre {
public:

    Fisio(std::string pais, int numJugador);
    std::vector<std::pair<int, int>> movimientosPosibles() override;
    void cargarTextura() override;

//Los 7 hechizos del Fisio, cada uno con su propio método para lanzarlo.
   
   // El bool indica si se ha usado o no durante la partida

    bool usadoTeleport = false;
    bool usadoHeal = false;
    bool usadoShiftTime = false;
    bool usadoExchange = false;
    bool usadoSummon = false;
    bool usadoRevive = false;
    bool usadoImprison = false;

    // Devuelve false si el hechizo ya se usó
    bool lanzarTeleport(Personaje* aliado, int destFila, int destCol, Tablero& t);
    bool lanzarHeal(Personaje* aliado);
    bool lanzarShiftTime(Tablero& t);
    bool lanzarExchange(Personaje* p1, Personaje* p2, Tablero& t);
    bool lanzarSummon(Personaje* enemigo, Tablero& t);
    bool lanzarRevive(Personaje* aliado, Tablero& t);
    bool lanzarImprison(Personaje* enemigo, int cicloActual);

};
