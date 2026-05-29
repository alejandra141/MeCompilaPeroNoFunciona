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
    Jugador* j1;
    Jugador* j2;
    std::string paisJ1, paisJ2; // esto es para las colisiones


    int cursorFila = 4; // cursor empieza en el centro del tablero 
    int cursorCol = 4;
    Personaje* piezaSeleccionada = nullptr; // al principio no hay ninguna pieza agarrada

    // para saber si estamos moviendo el cursor buscando pieza, o buscando destino
    bool modoDestino = false;

    Turnos gestionTurnos;


	//para ver las stats de la pieza bajo el cursor, aunque no se haya seleccionado, para que se vea en la pantalla de abajo
    Personaje* piezaHover = nullptr;

    // hay que ponerle como un modo hechizo al fisio 
    bool modoHechizo = false;   // estamos eligiendo objetivo de un hechizo
    int  hechizoPendiente = 0;       // del 1 al 7 según el hechizo del Fisio
    Personaje* primerObjetivo = nullptr; // para Intercambio que se necesitan dos piezas
    EstadoJuego* estadoPendiente = nullptr; 


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

