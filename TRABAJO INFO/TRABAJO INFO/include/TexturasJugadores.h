
//TexturasJugadores.h

#pragma once
#include <GL/freeglut.h>

class TexturasJugadores {
private:
    unsigned int texID;
    float cx, cy, cz;
    float mitad;
    float offsetX;
    float offsetY;

public:
    TexturasJugadores();
    void setTextura(unsigned int id);
    void setPosicion(float x, float y);
    void setOffset(float ox, float oy);
    void dibuja() const;
    unsigned int getTexID() const { return texID; }
};


