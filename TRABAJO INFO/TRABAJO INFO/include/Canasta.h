
#pragma once
#include "ETSIDI.h"

class Canasta {
private:
    float x, y, z;          
    float ancho, alto;      
    GLuint texID;

public:
    Canasta(float px = 0, float py = 0, float pz = 0);

    void dibuja();
    void mueve(float t);
    void setPos(float px, float py, float pz);
};