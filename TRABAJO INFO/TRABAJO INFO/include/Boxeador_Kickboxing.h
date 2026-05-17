#pragma once
#include "Personaje.h"

class Boxeador_Kickboxing : public Personaje {
public:
    Boxeador_Kickboxing(bandos b, float px, float py)
        : Personaje(b, px, py, "Personajes/Espana/buenos/Boxeador_Kickboxing_ESP.png")
    {
        // Estadísticas específicas del boxeador normal
        vida = 120;
        fuerza = 20;
        defensa = 12;
        velocidad = 1.1f;
        agilidad = 1.0f;
        estela = 1;
    }

    void dibuja()   {

    }
    void mueve()   {

    }
    void habilidadEspecial()  {
       
    }
};