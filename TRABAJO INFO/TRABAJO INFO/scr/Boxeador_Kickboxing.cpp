//Boxeador_Kickboxing.cpp

#include "Boxeador_Kickboxing.h"

Boxeador_Kickboxing::Boxeador_Kickboxing(int numJugador) {
    // Valores con ventaja 
    vida = 130;
    fuerza = 20;
    defensa = 15;
    velocidad = 1.2f;
    agilidad = 1.2f;
    estela = 1;


    // Posicionamiento según el jugador
    if (numJugador == 1) {
        posX = 100.0f;
        baseYa = 300.0f;
    }
    else {
        posX = 500.0f;
        baseYa = 300.0f;
    }
    posY = baseYa; // Empezamos en el suelo   

    // ---------------------------------------------------------
    // IMAGEN: Aquí se cargaría el sprite del boxeador de Kickboxing
    // Ejemplo: sprite.setTexture("assets/imagenes/boxeador_kickboxing.png");
    // ---------------------------------------------------------
}
