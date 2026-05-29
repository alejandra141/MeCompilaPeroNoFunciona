#pragma once
#include "EstadoJuego.h"
#include "Combates.h"
#include "Personaje.h"
#include <string>

class FlujoJuego;

class EstadoCombate : public EstadoJuego {
private:
    FlujoJuego* flujo;
    Combates* combate;
    std::string paisJ1, paisJ2;
    Personaje* atacante;
    Personaje* defensor;
    int         filaDestino;
    int         colDestino;
public:
    EstadoCombate(FlujoJuego* f, int tipo,
        const std::string& paisJ1,
        const std::string& paisJ2,
        Personaje* atacante = nullptr,
        Personaje* defensor = nullptr,
        int        filaDestino = 0,
        int        colDestino = 0);
    ~EstadoCombate();
    void mueve(double dt)              override;
    void dibujar()                     override;
    void tecla(unsigned char key)      override;
    void teclaSuelta(unsigned char key) override;
    void teclaEspecial(int key)        override;
    void teclaEspecialSuelta(int key)  override;
};