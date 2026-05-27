#pragma once
#include "EstadoJuego.h"
#include "Tablero.h"
#include "Jugador.h"
#include <string>


class FlujoJuego;

class EstadoTablero : public EstadoJuego {
private:
    FlujoJuego* flujo;
    Jugador j1, j2;
    std::string paisJ1, paisJ2; // esto es para las colisiones

public:
    EstadoTablero(FlujoJuego* f,
        const std::string& paisJ1,
        const std::string& paisJ2);
    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;

    //esto es para la detección de colisiones en el tablero entre personajes, para iniciar el combate

    void comprobarColision(Personaje* atacante, int filaDestino, int colDestino);
};

