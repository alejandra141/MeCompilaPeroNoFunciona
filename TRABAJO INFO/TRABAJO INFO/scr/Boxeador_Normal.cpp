//Boxeador_Normal.cpp

#include "Boxeador_Normal.h"

Boxeador_Normal::Boxeador_Normal(int numJugador) {
    // Valores estándar para el combate normal
    vida = 100;
    fuerza = 10;
    defensa = 10;
    velocidad = 1.0f;
    agilidad = 1.0f;
    estela = 0;


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
    // IMAGEN: Aquí se cargaría el sprite del boxeador normal
    // Ejemplo: sprite.setTexture("assets/imagenes/boxeador_normal.png");
    // ---------------------------------------------------------
}
