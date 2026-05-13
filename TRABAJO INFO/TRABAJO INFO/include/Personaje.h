#pragma once
#include "Turnos.h"
#include "Vector2D.h"
#include "Textura.h"

class Personaje {
private:
    vector2D p1;   // esquina inferior izquierda
    vector2D p2;   // esquina superior derecha
    Textura tex;

public:
    Bando bando;
    int vida;
    int fuerza;
    int defensa;
    float velocidad;
    float agilidad;
    int estela;
    vector2D posicion;

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
