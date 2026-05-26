//Boxeador.cpp

#include "Boxeador.h"
#include <iostream>
#include <cmath>
#include <cstdio> // Para sprintf_s si fuera necesario


// Constructor base: lo dejamos limpio porque todo el peso va a la función inicializar
Boxeador::Boxeador() {
    vida = 0;
    fuerza = 0;
    defensa = 0;
    velocidad = 0.0f;
    agilidad = 0.0f;
    estela = 0;
    posX = 0.0f;
    posY = 0.0f;
    baseYa = 0.0f;
    numJugador = 0;
}

void Boxeador::inicializar(int numJug) {
    this->numJugador = numJug;

    // Ambos comparten la misma altura en el suelo de la lona
    baseYa = -7.5f;
    posY = baseYa;

    if (numJugador == 1) {
        // Características del Boxeador NORMAL
        vida = 100;
        fuerza = 10;
        defensa = 10;
        velocidad = 1.0f;
        agilidad = 1.0f;
        estela = 0;


        posX = -10.0f; // Lado izquierdo de la lona
    }
    else {
        // Características del Boxeador KICKBOXING
        vida = 130;
        fuerza = 20;
        defensa = 15;
        velocidad = 1.2f;
        agilidad = 1.2f;
        estela = 1;


        posX = 10.0f;  // Lado derecho de la lona
    }
}

void Boxeador::recibirDanio(int danio) {
    // 1. Si está esquivando, el golpe falla y no hacemos nada más
    if (estaEsquivando) {
        estaEsquivando = false; // Gastamos el esquivo
        return;
    }

    // 2. Si no esquiva, calculamos el daño final restando la defensa
    int danioFinal = danio - (defensa / 5);
    if (danioFinal < 0) danioFinal = 0;

    vida -= danioFinal;

    // 3. Controlamos que la vida no sea negativa
    if (vida < 0) vida = 0;
}

void Boxeador::realizarPunetazo() {
    std::cout << "¡Punietazo lanzado con fuerza " << fuerza << "!" << std::endl;
}

void Boxeador::realizarPatada() {
    std::cout << "¡Patada lanzada con fuerza " << (fuerza + 5) << "!" << std::endl;
}

int Boxeador::getVida() { return vida; }
int Boxeador::getFuerza() { return fuerza; }
bool Boxeador::estaVivo() { return vida > 0; }

void Boxeador::esquivar() {
    estaEsquivando = true;
}

void Boxeador::actualizarBalanceo() {
    // Usamos la función seno (sin) para crear un movimiento de vaivén suave
    // El 0.05f controla la velocidad y el 5.0f la altura del bote
    tiempoBalanceo += 0.2f;
    posY = baseYa + (std::sin(tiempoBalanceo) * 0.2f);
}

void Boxeador::darPaso(int direccion) {
    // El boxeador avanza una distancia fija multiplicada por su velocidad de atributo (depende si es normal o kickboxing)
    posX += direccion * velocidad * 1.5f;
}
