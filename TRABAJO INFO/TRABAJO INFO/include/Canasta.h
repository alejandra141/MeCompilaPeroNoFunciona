
#pragma once
#include "ETSIDI.h"
#include "Linea.h"

class Canasta {
private:
    Linea pos;      
    Linea vel;
    float ancho, alto;      
    GLuint texID;

public:
    Canasta(const Linea& p);
    void dibuja();
    void mueve(float t);
    void setPos(const Linea& p);
};