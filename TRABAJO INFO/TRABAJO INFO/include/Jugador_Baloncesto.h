#pragma once
#include "Personaje.h"

class Jugador_Baloncesto : public Personaje {
public:
    Jugador_Baloncesto(Bando b, float px, float pz)
        : Personaje(b, px, pz)
    {
        // Estadísticas específicas del boxeador normal
        vida = 120;
        fuerza = 20;
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