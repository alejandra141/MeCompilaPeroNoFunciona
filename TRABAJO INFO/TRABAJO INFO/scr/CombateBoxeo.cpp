//CombateBoxeo.cpp

#include "CombateBoxeo.h"
#include "GL/freeglut.h"
#include "ETSIDI.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath> // Para std::abs

// El constructor recibe los boxeadores ya decididos (Normal o Kickboxing)
CombateBoxeo::CombateBoxeo(Boxeador* p1, Boxeador* p2, bool contraIA) {
    jugador1 = p1;
    jugador2 = p2;
    //esIA = contraIA;
    esIA = false; // Forzado a falso para ignorar la IA por ahora

    terminado = false;
    cooldownIA = 0.0f;

    // Inicializamos a los boxeadores pasándoles su número de jugador -- luego se cambiara, es para las pruebass
    if (jugador1 != nullptr) jugador1->inicializar(1);
    if (jugador2 != nullptr) jugador2->inicializar(2);

    /*// Inicializamos el azar solo si hay IA
    if (esIA) {
        std::srand(static_cast<unsigned int>(std::time(0)));
    }*/
}


void CombateBoxeo::iniciarPelea() {
    std::cout << "--- ¡FIGHT! ---" << std::endl;

    ETSIDI::play("sonidos/boxeo/campana_inicio.wav");
}

void CombateBoxeo::finalizarPelea() {
    std::cout << "--- FIN DEL COMBATE ---" << std::endl;

    ETSIDI::play("sonidos/boxeo/campana_fin.wav");
}

// Vinculamos la lectura de teclado de FreeGLUT con la lógica de ataques
void CombateBoxeo::tecla(unsigned char key) {
    detectarEntrada(key);
}


void CombateBoxeo::detectarEntrada(char teclaPresionada) {

    // Si alguno ha muerto KO, no dejamos que sigan pegando, ni moverse ni golpear
    if (!jugador1->estaVivo() || !jugador2->estaVivo()) {
        return; // Salimos de la función, el combate ha terminado . VUELVE A TABLERO
    }

    // LIMITES DEL RING (Paredes de la pantalla) 
    float limiteIzquierdo = -9.0f;
    float limiteDerecho = 9.0f;

    /*// Guardamos las posiciones por si hay que deshacer el movimiento tras un choque
    float antiguoX1 = jugador1->getX();
    float antiguoX2 = jugador2->getX();*/

    // ---------------------------------------------
    // CONTROLES JUGADOR 1 (Lado izquierdo) --- por ahoraaa
    // ---------------------------------------------
    // Movimiento
    if (teclaPresionada == 'a' || teclaPresionada == 'A') {
        //imponemos limite izquierdo del ring para que no se salga de la pantalla
        if (jugador1->getX() > limiteIzquierdo) { // Izquierda
            jugador1->darPaso(-1);
        }
    }
    else if (teclaPresionada == 'd' || teclaPresionada == 'D') {
        //imponemos limite derecho del ring para que no se salga de la pantalla
        if (jugador1->getX() < limiteDerecho) { // Derecha
            jugador1->darPaso(1);
        }
    }
    // Ataques y Defensa
    else if (teclaPresionada == 'q' || teclaPresionada == 'Q') {
        jugador1->realizarPunetazo();

        ETSIDI::play("sonidos/boxeo/puño_flojo.wav");

        // std::abs calcula la distancia real (positiva) entre ambos boxeadores
        // da igual si esta a la derecha o izq, por eso usamos el valor absoluto
        // < 5.0f es el rango de alcance
        // Si la distancia es menor a 5.0f, el golpe conecta; si no, da al aire.
        if (std::abs(jugador1->getX() - jugador2->getX()) < 5.0f) {
            procesarGolpe(jugador1, jugador2);
        }
    }
    else if (teclaPresionada == 'e' || teclaPresionada == 'E') {
        jugador1->realizarPatada();
        if (std::abs(jugador1->getX() - jugador2->getX()) < 5.0f) {
            procesarGolpe(jugador1, jugador2);
        }
    }
    else if (teclaPresionada == 's' || teclaPresionada == 'S') {
        // Activa el estado de esquivo del boxeador. 
        // Mientras esté activo, el próximo golpe recibido no le restará vida.
        // Cambia 'estaEsquivando' a true para que la función recibirDanio() ignore el próximo golpe.
        jugador1->esquivar();

        ETSIDI::play("sonidos/boxeo/esquivo.wav");
    }

    // ---------------------------------------------
    // CONTROLES JUGADOR 2 (Lado derecho) --- por shora no hay IA
    // ---------------------------------------------
    // Movimiento
    if (teclaPresionada == 'j' || teclaPresionada == 'J') {
        if (jugador2->getX() > limiteIzquierdo) {// Izquierda
            jugador2->darPaso(-1);
        }
    }
    else if (teclaPresionada == 'l' || teclaPresionada == 'L') {
        if (jugador2->getX() < limiteDerecho) { // Derecha
            jugador2->darPaso(1);
        }
    }
    // Ataques y Defensa
    else if (teclaPresionada == 'u' || teclaPresionada == 'U') {
        jugador2->realizarPunetazo();

        ETSIDI::play("sonidos/boxeo/puño_flojo.wav");

        if (std::abs(jugador1->getX() - jugador2->getX()) < 5.0f) {
            procesarGolpe(jugador2, jugador1);
        }
    }
    else if (teclaPresionada == 'i' || teclaPresionada == 'I') {
        jugador2->realizarPatada();
        if (std::abs(jugador1->getX() - jugador2->getX()) < 5.0f) {
            procesarGolpe(jugador2, jugador1);
        }
    }
    else if (teclaPresionada == 'k' || teclaPresionada == 'K') {
        jugador2->esquivar();
        ETSIDI::play("sonidos/boxeo/esquivo.wav");
    }


}


void CombateBoxeo::procesarGolpe(Boxeador* atacante, Boxeador* victima) {
    // Obtenemos la fuerza del que pega
    int danio = atacante->getFuerza();

    // Guardamos la vida antes del impacto para saber si el daño fue real
    int vidaAntes = victima->getVida();

    // Mandamos el daño a la víctima 
    victima->recibirDanio(danio);

    // Solo suena si la víctima sigue viva (para no solapar con el sonido de K.O.)
    // IMPACTOS REALES (Puñetazo y Patada)
    // Si la vida bajó, significa que el rival NO esquivó y el golpe le dio
    if (victima->getVida() < vidaAntes) {

        if (danio > 15) {
            // Para golpes fuertes (el Kickboxer tiene fuerza 20)
            ETSIDI::play("sonidos/boxeo/patada.wav");
        }
        else {
            // Para impactos normales (fuerza 10)
            ETSIDI::play("sonidos/boxeo/puñetazo.wav");
        }

        // Si tras el impacto la víctima muere, llamamos al fin de la pelea
        if (!victima->estaVivo()) {
            finalizarPelea();
        }
    }
}



void CombateBoxeo::mueve(double dt) {
    // Si el combate no ha terminado, ambos boxeadores botan
    if (estaTerminado()) return;

    //los jugadores se balancean de forma automatica, sin necesidad de que el jugador pulse nada
    jugador1->actualizarBalanceo();
    jugador2->actualizarBalanceo();

    /*// Solo llamamos a la IA si el modo está activo
    if (esIA) {
        actualizarIA();
    }*/

}


/*void CombateBoxeo::actualizarIA() {
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
}*/



bool CombateBoxeo::estaTerminado() {
    return (!jugador1->estaVivo() || !jugador2->estaVivo());
}



void CombateBoxeo::dibujar() {
    //DIBUJAMOS EL RING DE BOXEO
    glDisable(GL_LIGHTING);      // que la luz no afecte al fondo
    glEnable(GL_TEXTURE_2D);     // activar texturas

    //POR AQUI PINTAMOS UNA BOLERITA DE FONDO
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("fondos/fondo boxeo.png").id);

    glColor3f(1, 1, 1);

    glBegin(GL_POLYGON);

    // plano sobre el que se pone la imagen
    glTexCoord2d(0, 1); glVertex3f(-20, -20, -5);
    glTexCoord2d(1, 1); glVertex3f(20, -20, -5);
    glTexCoord2d(1, 0); glVertex3f(20, 15, -5);
    glTexCoord2d(0, 0); glVertex3f(-20, 15, -5);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    // dibujamos a los boxeadores por polimorfismo
    // al combate no le importa si son Normal o Kickboxing, ambos tienen la función .dibuja()
   // jugador1->dibuja();
   // jugador2->dibuja();

    glEnable(GL_LIGHTING);

    // -------------------------------------------------------------------------
    // RECTÁNGULOS TEMPORALES DE PRUEBA (Jugadores)
    // -------------------------------------------------------------------------
    //posicionamiento
    float w = 6.0f;
    float h = 8.0f;

    // RECTÁNGULO JUGADOR 1
    if (jugador1 != nullptr) {
        float x1 = jugador1->getX();
        float y1 = jugador1->getY();

        glColor3ub(0, 0, 255); 
        glBegin(GL_QUADS);
        glVertex2f(x1 - w / 2, y1);
        glVertex2f(x1 + w / 2, y1);
        glVertex2f(x1 + w / 2, y1 + h);
        glVertex2f(x1 - w / 2, y1 + h);
        glEnd();
    }

    // RECTÁNGULO JUGADOR 2
    if (jugador2 != nullptr) {
        float x2 = jugador2->getX();
        float y2 = jugador2->getY();

        glColor3ub(255, 105, 180);
        glBegin(GL_QUADS);
        glVertex2f(x2 - w / 2, y2);
        glVertex2f(x2 + w / 2, y2);
        glVertex2f(x2 + w / 2, y2 + h);
        glVertex2f(x2 - w / 2, y2 + h);
        glEnd();
    }

    glEnable(GL_LIGHTING);


    // fuentes para que se vea la vida ue le queda a cada jugador


    ETSIDI::setFont("fuentes/Bitwise.ttf", 16);

    // --- JUGADOR 1: TEXTO AZUL ---
    ETSIDI::setTextColor(0, 0, 1); // Azul 
    ETSIDI::printxy("JUGADOR 1 ", -14, 9);
    //para hacer que la vida vaya cambiando de valor
    char vidaJ1[50];
    sprintf_s(vidaJ1, "Vida: %d", jugador1->getVida());
    ETSIDI::printxy(vidaJ1, -14, 8);


    // --- JUGADOR 2: TEXTO ROSA ---
    ETSIDI::setTextColor(1, 0.4, 0.7); // Rosa
    ETSIDI::printxy("JUGADOR 2 ", 9, 9);

    char vidaJ2[50];
    sprintf_s(vidaJ2, "Vida: %d", jugador2->getVida());
    ETSIDI::printxy(vidaJ2, 9, 8);
}

