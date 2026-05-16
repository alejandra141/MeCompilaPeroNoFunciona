//CombateBoxeo.cpp

#include "CombateBoxeo.h"
#include <iostream>


// El constructor recibe los boxeadores ya decididos (Normal o Kickboxing)
CombateBoxeo::CombateBoxeo(Boxeador* p1, Boxeador* p2, bool contraIA) {
    jugador1 = p1;
    jugador2 = p2;
    esIA = contraIA;

    terminado = false;
    cooldownIA = 0.0f;

    // Inicializamos el azar solo si hay IA
    if (esIA) {
        std::srand(static_cast<unsigned int>(std::time(0)));
    }
}

void CombateBoxeo::iniciarPelea() {
    std::cout << "--- ¡FIGHT! ---" << std::endl;

    // ---------------------------------------------------------
    // SONIDO: Sonido de la campana de inicio (Wii Sports)
    // Ejemplo: gestorAudio.reproducir("assets/sonidos/boxeo/campana_inicio.wav");
    // ---------------------------------------------------------
}

void CombateBoxeo::finalizarPelea() {
    // ---------------------------------------------------------
    // SONIDO: Sonido de victoria o K.O.
    // Ejemplo: gestorAudio.reproducir("assets/sonidos/boxeo/victoria.wav");
    // ---------------------------------------------------------
}


void CombateBoxeo::detectarEntrada(char teclaPresionada) {

    // Si alguno ha muerto, no dejamos que sigan pegando
    if (!jugador1->estaVivo() || !jugador2->estaVivo()) {
        return; // Salimos de la función, el combate ha terminado . VUELVE A TABLERO
    }


    // --- CONTROLES JUGADOR 1 (A, W, S, D) ---
    // Puñetazo Izquierdo 
    if (teclaPresionada == 'a' || teclaPresionada == 'A') {
        jugador1->realizarPunetazo();
        procesarGolpe(jugador1, jugador2);
        // audio.reproducirPunetazo(); 
    }
    // Puñetazo Derecho
    else if (teclaPresionada == 'd' || teclaPresionada == 'D') {
        jugador1->realizarPunetazo();
        procesarGolpe(jugador1, jugador2);
        // audio.reproducirPunetazo(); 
    }
    // Patada (Ventaja Kickboxing) 
    else if (teclaPresionada == 'w' || teclaPresionada == 'W') {
        jugador1->realizarPatada();
        procesarGolpe(jugador1, jugador2);
        // audio.reproducirPatada(); 
    }
    // Esquivar
    else if (teclaPresionada == 's' || teclaPresionada == 'S') {
        jugador1->esquivar();
        // audio.reproducirEsquivo(); 
    }

    // --- CONTROLES JUGADOR 2 (J, K, L, I) (Solo si NO es IA)---
    // Puñetazo Izquierdo
    if (!esIA) {
        if (teclaPresionada == 'j' || teclaPresionada == 'J') {
            jugador2->realizarPunetazo();
            procesarGolpe(jugador2, jugador1);
            // audio.reproducirPunetazo();
        }
        // Puñetazo Derecho
        else if (teclaPresionada == 'l' || teclaPresionada == 'L') {
            jugador2->realizarPunetazo();
            procesarGolpe(jugador2, jugador1);
            // audio.reproducirPunetazo();
        }
        // Patada (Ventaja Kickboxing)
        else if (teclaPresionada == 'i' || teclaPresionada == 'I') {
            jugador2->realizarPatada();
            procesarGolpe(jugador2, jugador1);
            // audio.reproducirPatada();
        }
        // Esquivar
        else if (teclaPresionada == 'k' || teclaPresionada == 'K') {
            jugador2->esquivar();
            // audio.reproducirEsquivo();
        }
    }
}


void CombateBoxeo::procesarGolpe(Boxeador* atacante, Boxeador* victima) {
    // 1. Obtenemos la fuerza del que pega
    int danio = atacante->getFuerza();

    // 2. Mandamos el daño a la víctima (la función recibirDanio ya mira si esquiva)
    victima->recibirDanio(danio);

    // 3. SONIDOS: Aquí es donde conectas tus archivos .wav
    // Solo suena si la víctima sigue viva (para no solapar con el sonido de K.O.)
    if (victima->estaVivo()) {
        // audio.reproducirPunetazo(); 
    }
}



void CombateBoxeo::actualizar() {
    // Si el combate no ha terminado, ambos boxeadores botan
    if (!estaTerminado()) {
        jugador1->actualizarBalanceo();
        jugador2->actualizarBalanceo();

        // Solo llamamos a la IA si el modo está activo
        if (esIA) {
            actualizarIA();
        }
    }
}


void CombateBoxeo::actualizarIA() {
    if (cooldownIA > 0) {
        cooldownIA -= 0.016f;
        return;
    }

    int decision = std::rand() % 100;

    if (decision < 5) {
        jugador2->realizarPunetazo();
        procesarGolpe(jugador2, jugador1);
        cooldownIA = 1.0f;
    }
    else if (decision < 7) {
        jugador2->realizarPatada();
        procesarGolpe(jugador2, jugador1);
        cooldownIA = 1.5f;
    }
    else if (decision < 10) {
        jugador2->esquivar();
        cooldownIA = 0.5f;
    }
}

bool CombateBoxeo::estaTerminado() {
    return (!jugador1->estaVivo() || !jugador2->estaVivo());
}


