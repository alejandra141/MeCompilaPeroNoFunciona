#pragma once

#include "Combates.h"

class CombateBolos : public Combates {
public:
    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
};

