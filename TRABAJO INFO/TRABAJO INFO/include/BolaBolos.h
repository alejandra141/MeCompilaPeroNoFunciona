#pragma once
#include "vector2D.h"

class BolaBolos
{

public:
    vector2D posicion;
    vector2D velocidad;
    bool activa;

    BolaBolos() : posicion(0, 0), velocidad(0, 0), activa(false) {}

    void lanzar(float x, float y, float velX, float velY) {
        posicion = { x, y };
        velocidad = { velX, velY };
        activa = true;
    }

    void mueve(float dt) {
        if (!activa) return;
        posicion.x += velocidad.x * dt;
        posicion.y += velocidad.y * dt;
    }

    void resetear() { activa = false; }

    void dibuja();
};

