


//CombateBoxeo.cpp

#include "CombateBoxeo.h"
#include "EstadoTablero.h"
#include "FlujoJuego.h"
#include "GL/freeglut.h"
#include "ETSIDI.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath> // Para std::abs

// El constructor recibe los boxeadores ya decididos (Normal o Kickboxing)
CombateBoxeo::CombateBoxeo(Personaje* p1, Personaje* p2, bool contraIA) {
    jugador1 = p1;
    jugador2 = p2;
    esIA = false;
    terminado = false;
    cooldownIA = 0.0f;

    // Posiciones del ring — solo internas, NO tocamos setPosicion
    posXj1 = -6.0f; posYj1 = -8.0f;
    posXj2 = 6.0f; posYj2 = -8.0f;
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
        if (posXj1 > limiteIzquierdo) posXj1 -= 1.0f;
    }
    else if (teclaPresionada == 'd' || teclaPresionada == 'D') {
        if (posXj1 < limiteDerecho) posXj1 += 1.0f;
    }
    // Ataques y Defensa
    else if (teclaPresionada == 'q' || teclaPresionada == 'Q') {
        jugador1->realizarPunetazo();

        ETSIDI::play("sonidos/boxeo/puño_flojo.wav");

        // std::abs calcula la distancia real (positiva) entre ambos boxeadores
        // da igual si esta a la derecha o izq, por eso usamos el valor absoluto
        // < 5.0f es el rango de alcance
        // Si la distancia es menor a 5.0f, el golpe conecta; si no, da al aire.
        if (std::abs(posXj1 - posXj2) < 5.0f) {
            procesarGolpe(jugador1, jugador2);
        }
    }
    else if (teclaPresionada == 'e' || teclaPresionada == 'E') {
        jugador1->realizarPatada();
        if (std::abs(posXj1 - posXj2) < 5.0f) {
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
        if (posXj2 > limiteIzquierdo) posXj2 -= 1.0f;
    }
    else if (teclaPresionada == 'l' || teclaPresionada == 'L') {
        if (posXj2 < limiteDerecho) posXj2 += 1.0f;
    }



    // Ataques y Defensa
    else if (teclaPresionada == 'u' || teclaPresionada == 'U') {
        jugador2->realizarPunetazo();

        ETSIDI::play("sonidos/boxeo/puño_flojo.wav");

        if (std::abs(posXj1 - posXj2) < 5.0f) {
            procesarGolpe(jugador2, jugador1);
        }
    }
    else if (teclaPresionada == 'i' || teclaPresionada == 'I') {
        jugador2->realizarPatada();
        if (std::abs(posXj1 - posXj2) < 5.0f) {
            procesarGolpe(jugador2, jugador1);
        }
    }
    else if (teclaPresionada == 'k' || teclaPresionada == 'K') {
        jugador2->esquivar();
        ETSIDI::play("sonidos/boxeo/esquivo.wav");
    }


}


void CombateBoxeo::procesarGolpe(Personaje* atacante, Personaje* victima) {
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
            estado = FIN; //ACTIVAR EL ESTADO FIN

            if (jugador1->estaVivo()) ganador = 1;  //DETERMINAR QUE JUGADOR ES EL GANADOR
            else ganador = 2;
        }
    }
}



void CombateBoxeo::mueve(double dt) {
    // Si el combate no ha terminado, ambos boxeadores botan
    if (estado == FIN) return;


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


    // RENDERIZADO DE LOS SPRITES PNG REALES EN EL RING 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);  // ← FALTABA
    glDisable(GL_LIGHTING);   // ← FALTABA

    float mitadW = 3.0f;
    float altoH = 8.0f;

    // DIBUJA SPRITE JUGADOR 1
    if (jugador1 != nullptr && jugador1->getSprite().getTexID() != 0) {
        glBindTexture(GL_TEXTURE_2D, jugador1->getSprite().getTexID());
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 1); glVertex3f(posXj1 - mitadW, posYj1, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(posXj1 + mitadW, posYj1, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(posXj1 + mitadW, posYj1 + altoH, 0.0f);
        glTexCoord2d(0, 0); glVertex3f(posXj1 - mitadW, posYj1 + altoH, 0.0f);
        glEnd();
    }

    // DIBUJA SPRITE JUGADOR 2
    if (jugador2 != nullptr && jugador2->getSprite().getTexID() != 0) {
        glBindTexture(GL_TEXTURE_2D, jugador2->getSprite().getTexID());
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 1); glVertex3f(posXj2 - mitadW, posYj2, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(posXj2 + mitadW, posYj2, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(posXj2 + mitadW, posYj2 + altoH, 0.0f);
        glTexCoord2d(0, 0); glVertex3f(posXj2 - mitadW, posYj2 + altoH, 0.0f);
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    /*// -------------------------------------------------------------------------
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

    glEnable(GL_LIGHTING);*/


    // fuentes para que se vea la vida ue le queda a cada jugador


    ETSIDI::setFont("fuentes/Bitwise.ttf", 16);

    // JUGADOR 1: TEXTO AZUL
    ETSIDI::setTextColor(0, 0, 1); // Azul 
    ETSIDI::printxy("JUGADOR 1 ", -14, 9);
    //para hacer que la vida vaya cambiando de valor
    char vidaJ1[50];
    sprintf_s(vidaJ1, "Vida: %d", jugador1->getVida());
    ETSIDI::printxy(vidaJ1, -14, 8);


    // JUGADOR 2: TEXTO ROSA 
    ETSIDI::setTextColor(1, 0.4, 0.7); // Rosa
    ETSIDI::printxy("JUGADOR 2 ", 9, 9);

    char vidaJ2[50];
    sprintf_s(vidaJ2, "Vida: %d", jugador2->getVida());
    ETSIDI::printxy(vidaJ2, 9, 8);



    if (estado == FIN) {  //SOY LORENA ESTO ES PARA QUE ANUNCIA EL GANADOR Y PULSANDO C VUELVES AL TABLERO  

        ETSIDI::setTextColor(1, 1, 0);

        if (ganador == 1)
            ETSIDI::printxy("GANADOR: JUGADOR 1", -5, 5);
        else if (ganador == 2)
            ETSIDI::printxy("GANADOR: JUGADOR 2", -5, 15);

        ETSIDI::setTextColor(1, 0, 0);
        ETSIDI::printxy("Pulsa C para volver", -5, 3);
    }

}



