
#pragma once
#include <GL/freeglut.h>

class TexturasJugadores {
private:
    unsigned int texID;
    float cx, cy, cz;
    float mitad;
public:
    TexturasJugadores();
    void setTextura(unsigned int id);
    void setPosicion(float x, float y);
    void dibuja() const;
};