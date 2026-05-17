#pragma once
#include "Combates.h"

class CombateBaloncesto : public Combates {
public:
    void actualizar() override;
    void dibujar() override;
    void tecla(unsigned char key) override;
};

