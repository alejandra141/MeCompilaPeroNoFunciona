//Boxeador_Normal.h

#pragma once
#include "Boxeador.h"

class Boxeador_Normal : public Boxeador {
public:
    Boxeador_Normal(bandos b, float px, float py)
        : Personaje(b, px, py, "Personajes/Espana/buenos/BoxeadorNormal_ESP.png")
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
    // El constructor asignará los valores base fijos
    Boxeador_Normal(int numJugador);
};
