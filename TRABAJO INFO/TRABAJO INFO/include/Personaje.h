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
    bandos bando;
    int vida;
    int fuerza;
    int defensa;
    float velocidad;
    float agilidad;
    int estela;
    vector2D posicion;

    Personaje(bandos b, float px, float py, const char* rutaTextura);


    void dibuja() const;


    bandos getBando() const { return bando; }
};
