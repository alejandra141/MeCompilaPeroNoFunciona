//Boxeador.cpp

#include "Boxeador.h"
#include <iostream>
#include <cmath>

// Constructor base (lo dejamos vacío o con valores por defecto)
Boxeador::Boxeador() : vida(), fuerza(), defensa(), velocidad(), agilidad(), estela() {}

void Boxeador::recibirDanio(int danio) {
    // 1. Si está esquivando, el golpe falla y no hacemos nada más
    if (estaEsquivando) {
        estaEsquivando = false; // Gastamos el esquivo
        // Aquí iría el SONIDO de "esquivo" (aire) si quieres
        return;
    }

    // 2. Si no esquiva, calculamos el daño final restando la defensa
    int danioFinal = danio - (defensa / 5);
    if (danioFinal < 0) danioFinal = 0;

    vida -= danioFinal;

    // 3. Controlamos que la vida no sea negativa
    if (vida < 0) vida = 0;

    // ---------------------------------------------------------
    // SONIDO: Aquí es donde suena el impacto real
    // audio.reproducirPunetazo(); 
    // ---------------------------------------------------------
}

void Boxeador::realizarPunetazo() {
    std::cout << "¡Puñetazo lanzado con fuerza " << fuerza << "!" << std::endl;

    // ---------------------------------------------------------
    // SONIDO: Aquí va el efecto del guante cortando el aire o golpeando
    // Ejemplo: gestorAudio.reproducir("assets/sonidos/boxeo/golpe.wav");
    // ---------------------------------------------------------
}

void Boxeador::realizarPatada() {
    std::cout << "¡Patada lanzada con fuerza " << (fuerza + 5) << "!" << std::endl;

    // ---------------------------------------------------------
    // SONIDO: Sonido de patada (solo para Kickboxing)
    // Ejemplo: gestorAudio.reproducir("assets/sonidos/boxeo/patada.wav");
    // ---------------------------------------------------------
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
    tiempoBalanceo += 0.05f;
    posY = baseYa + (std::sin(tiempoBalanceo) * 5.0f);
}

