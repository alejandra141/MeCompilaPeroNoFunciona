#pragma once
#include "EstadoJuego.h"
#include "Tablero.h"
#include "Jugador.h"
#include "Turnos.h"
#include <string>


class FlujoJuego;

class EstadoTablero : public EstadoJuego {
private:
    FlujoJuego* flujo;
    Jugador j1, j2;
    std::string paisJ1, paisJ2; // esto es para las colisiones


    int cursorFila = 4; // cursor empieza en el centro del tablero 
    int cursorCol = 4;
    Personaje* piezaSeleccionada = nullptr; // al principio no hay ninguna pieza agarrada

    // para saber si estamos moviendo el cursor buscando pieza, o buscando destino
    bool modoDestino = false;

    Turnos gestionTurnos;


public:
    EstadoTablero(FlujoJuego* f,
        const std::string& paisJ1,
        const std::string& paisJ2);
    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
	void teclaEspecial(int key) override;

    //esto es para la detección de colisiones en el tablero entre personajes, para iniciar el combate

    void comprobarColision(Personaje* atacante, int filaDestino, int colDestino);
};

