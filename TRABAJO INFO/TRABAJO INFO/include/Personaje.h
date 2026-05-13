#pragma once
#include "Turnos.h"
#include "Vector2D.h"

class Personaje {
public:
    Bando bando;
    int vida;
    int fuerza;
    int defensa;
    float velocidad;
    float agilidad;
    int estela;
    vector2D posicion;

public:
    Personaje(Bando b, float px, float py)
        : bando(b), posicion(px, py),
        vida(100), fuerza(10), defensa(5),
        velocidad(1.0f), agilidad(1.0f), estela(1)
    {
    }


    void dibuja() const  {
        
    }

    void mueve()  {

    }
    Bando getBando() const {  }
};
