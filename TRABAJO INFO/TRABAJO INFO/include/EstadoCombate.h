#pragma once
#include "EstadoJuego.h"
#include "Combates.h"
#include <string>             

class FlujoJuego;

class EstadoCombate : public EstadoJuego {
private:
    FlujoJuego* flujo;
    Combates* combate;
    std::string paisJ1, paisJ2;  

public:
    EstadoCombate(FlujoJuego* f, int tipo,
        const std::string& paisJ1,
        const std::string& paisJ2);  
    ~EstadoCombate();
    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
    void teclaSuelta(unsigned char key) override;
    void teclaEspecial(int key)        override;
    void teclaEspecialSuelta(int key)  override;
};
