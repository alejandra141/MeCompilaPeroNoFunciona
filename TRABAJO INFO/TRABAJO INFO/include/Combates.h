#pragma once

class Combates {
public:
    virtual void mueve(double dt) = 0;
    virtual void dibujar() = 0;
    virtual void tecla(unsigned char key) = 0;
    virtual ~Combates() {}
};


