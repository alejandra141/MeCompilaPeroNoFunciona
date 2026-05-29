#pragma once
#include "EstadoJuego.h"
#include "Jugador.h"     
#include <string>

class EstadoTablero;

class FlujoJuego {
private:
    EstadoJuego* estadoActual;
    Jugador jugador1{ 1 };
    Jugador jugador2{ 2 };

public:
    FlujoJuego();
    ~FlujoJuego();

    void cambiarEstado(EstadoJuego* nuevo);

    Jugador* getJugador1() { return &jugador1; }
    Jugador* getJugador2() { return &jugador2; }

    void mueve(double dt);
    void dibujar();
    void tecla(unsigned char key);
    void teclaSuelta(unsigned char key);
    void teclaEspecial(int key);
    void teclaEspecialSuelta(int key);
    EstadoJuego* getEstado();
    EstadoTablero* getEstadoTablero();
};


