
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


    // getters necesarios para la detección de colisiones
    float getPosX()  const { return pos.x; }
    float getPosY()  const { return pos.y; }
    float getPosZ()  const { return pos.z; }
    float getRadio() const { return 1.5f; }
};