#pragma once

#include "Combates.h"

class CombateBolos : public Combates {
public:
    void mueve() override;
    void dibujar() override;
    void tecla(unsigned char key) override;
};

