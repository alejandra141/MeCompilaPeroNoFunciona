#pragma once
#include "Personaje.h"

class Jugador_Baloncesto : public Personaje {
public:
    Jugador_Baloncesto(bandos b, float px, float py)
        : Personaje(b, px, py, "Personajes/Espana/buenos/Jugador_Baloncesto_ESP.png")
    {
        // Estadísticas específicas del jugador de baloncesto
        vida = 130;
        fuerza = 22;
        defensa = 12;
        velocidad = 1.1f;
        agilidad = 1.0f;
        estela = 1;
    }

    void dibuja()  {

    }
    void mueve()  {

    }
    void habilidadEspecial()  {
       
    }
};