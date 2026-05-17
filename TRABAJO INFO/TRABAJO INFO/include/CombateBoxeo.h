#pragma once
#include "Combates.h"

class CombateBoxeo : public Combates {
public:
    void actualizar() override;
    void dibujar() override;
    void tecla(unsigned char key) override;
};

