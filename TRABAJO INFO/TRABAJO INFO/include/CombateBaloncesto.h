#pragma once
#include "Combates.h"
#include "Canasta.h"

class CombateBaloncesto : public Combates {

private:

	Canasta canasta; //objeto canasta para el combate de baloncesto

public:
    CombateBaloncesto();

    void actualizar() override;
    void dibujar() override;
    void tecla(unsigned char key) override;
};

