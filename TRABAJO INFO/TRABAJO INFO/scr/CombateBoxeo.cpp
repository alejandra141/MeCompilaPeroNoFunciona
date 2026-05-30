
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
    posXj2 = 6.0f;  posYj2 = -8.0f;
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

    if (estado == INSTRUCCIONES) {
        if (key == ' ' || key == 13) { // al pulsar Espacio o Enter, arranca la pelea
            iniciarPelea(); // suena la campana de inicio
            estado = JUGANDO;
        }
        return; // bloqueamos ataques mientras se leen las instrucciones
    }

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
        jugador1->esquivar();
        // Kickboxing esquiva 0.8s, Normal solo 0.3s
        tiempoEsquivaJ1 = (jugador1->getTipo() == "boxeador_kickboxing") ? 0.8f : 0.3f;//AÑADIENDO VENTAJAS
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
        tiempoEsquivaJ2 = (jugador2->getTipo() == "boxeador_kickboxing") ? 0.8f : 0.3f;//AÑADIENDO VENTAJAS
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


            // cuando uno de los dos gane sonara el publico aplaudiendo
            ETSIDI::play("sonidos/genericos/CrowdCheer.wav");

        }
    }
}



void CombateBoxeo::mueve(double dt) {

    // si estamos leyendo las instrucciones, congelamos el movimiento del ring
    if (estado == INSTRUCCIONES) return;


    // Si el combate no ha terminado, ambos boxeadores botan
    if (estado == FIN) return;


    //los jugadores se balancean de forma automatica, sin necesidad de que el jugador pulse nada
    jugador1->actualizarBalanceo();
    jugador2->actualizarBalanceo();

    //SOY ALEJANDRA ESTOY AÑADIENDO ESTO PARA QUE TENGAN MÁS VENTAJA LOS DE KICKBOXING

    if (tiempoEsquivaJ1 > 0) {
        tiempoEsquivaJ1 -= (float)dt;
        if (tiempoEsquivaJ1 <= 0) jugador1->realizarPunetazo(); // resetea esquiva
    }
    if (tiempoEsquivaJ2 > 0) {
        tiempoEsquivaJ2 -= (float)dt;
        if (tiempoEsquivaJ2 <= 0) jugador2->realizarPunetazo(); // resetea esquiva
    }
}


bool CombateBoxeo::estaTerminado() {
    return (!jugador1->estaVivo() || !jugador2->estaVivo());
}


void CombateBoxeo::dibujar() {
    //DIBUJAMOS EL RING DE BOXEO
    glDisable(GL_LIGHTING);      // que la luz no afecte al fondo
    glEnable(GL_TEXTURE_2D);     // activar texturas

    //POR AQUI PINTAMOS UN RING DE FONDO
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

    // INSTRUCCIONES

    if (estado == INSTRUCCIONES) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // RECUADRO NEGRO TRANSLÚCIDO EN EL MEDIO
        glColor4ub(0, 0, 0, 220); // Negro opaco
        glBegin(GL_QUADS);
        glVertex2f(-12.0f, -6.0f);
        glVertex2f(12.0f, -6.0f);
        glVertex2f(12.0f, 7.0f);
        glVertex2f(-12.0f, 7.0f);
        glEnd();

        // BORDE BLANCO DEL RECUADRO
        glLineWidth(3.0f);
        glColor3ub(255, 255, 255);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-12.0f, -6.0f);
        glVertex2f(12.0f, -6.0f);
        glVertex2f(12.0f, 7.0f);
        glVertex2f(-12.0f, 7.0f);
        glEnd();
        glDisable(GL_BLEND);

        // TEXTOS CON LAS INSTRUCCIONES
        ETSIDI::setFont("fuentes/Bitwise.ttf", 24);
        ETSIDI::setTextColor(1, 1, 0); // amarillo 
        ETSIDI::printxy("COMBATE BOXEO CONTROLES", -9.5f, 5.2f);

        ETSIDI::setFont("fuentes/Bitwise.ttf", 14);

        // CONTROLES JUGADOR 1 
        ETSIDI::setTextColor(0.2f, 0.6f, 1.0f); //azul
        ETSIDI::printxy("JUGADOR 1 (IZQUIERDA)", -11.0f, 3.2f);
        ETSIDI::setTextColor(1, 1, 1);
        ETSIDI::printxy("- Moverse IZQ: A", -11.0f, 2.0f);
        ETSIDI::printxy("- Moverse DERCH: D", -11.0f, 1.0f);
        ETSIDI::printxy("- Punetazo: Q", -11.0f, 0.0f);
        ETSIDI::printxy("- Patada: E", -11.0f, -1.0f);
        ETSIDI::printxy("- Esquivar: S", -11.0f, -2.0f);

        // CONTROLES JUGADOR 2 
        ETSIDI::setTextColor(1.0f, 0.4f, 0.7f); //rosa
        ETSIDI::printxy("JUGADOR 2 (DERECHA)", 1.5f, 3.2f);
        ETSIDI::setTextColor(1, 1, 1);
        ETSIDI::printxy("- Moverse IZQ: J", 1.5f, 2.0f);
        ETSIDI::printxy("- Moverse DERCH: L", 1.5f, 1.0f);
        ETSIDI::printxy("- Punetazo: U", 1.5f, 0.0f);
        ETSIDI::printxy("- Patada: O", 1.5f, -1.0f);
        ETSIDI::printxy("- Esquivar: K", 1.5f, -2.0f);

        // SALIDA
        ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
        ETSIDI::setTextColor(1, 0, 0); // Rojo 
        ETSIDI::printxy("PULSA ENTER/ESPACIO PARA EMPEZAR LA PELEA", -10.5f, -4.0f);

        glEnable(GL_LIGHTING);
        return; // salimos de la función para que NO dibuje los personajes ni las vidas todavía
    }

    // RENDERIZADO DE LOS SPRITES PNG REALES EN EL RING 

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // Por esto:
    float mitadW = 10.0f;
    float altoH = 21.0f;

    // DIBUJA SPRITE JUGADOR 1
    if (jugador1 != nullptr && jugador1->getSprite().getTexID() != 0) {
        glBindTexture(GL_TEXTURE_2D, jugador1->getSprite().getTexID());
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 1); glVertex3f(posXj1 - mitadW, -19.0f, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(posXj1 + mitadW, -19.0f, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(posXj1 + mitadW, -19.0f + altoH, 0.0f);
        glTexCoord2d(0, 0); glVertex3f(posXj1 - mitadW, -19.0f + altoH, 0.0f);
        glEnd();
    }

    // DIBUJA SPRITE JUGADOR 2
    if (jugador2 != nullptr && jugador2->getSprite().getTexID() != 0) {
        glBindTexture(GL_TEXTURE_2D, jugador2->getSprite().getTexID());
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 1); glVertex3f(posXj2 - mitadW, -19.0f, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(posXj2 + mitadW, -19.0f, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(posXj2 + mitadW, -19.0f + altoH, 0.0f);
        glTexCoord2d(0, 0); glVertex3f(posXj2 - mitadW, -19.0f + altoH, 0.0f);
        glEnd();
    }


    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, 0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // fuentes para que se vea la vida ue le queda a cada jugador

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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

