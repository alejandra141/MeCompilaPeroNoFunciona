#pragma once
#include "Linea.h"
#include "Color.h"

class Cuadrado {
private:
    Linea p1;
    Linea p2;
    Color color;

public:
    Cuadrado(const Linea& Punto1, const Linea& Punto2, const Color c)
        : p1(Punto1), p2(Punto2), color(c) {
    }

    void dibuja() const;
};
