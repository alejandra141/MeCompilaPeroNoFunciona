#include "EstadoCreadoras.h"
#include "EstadoInstrucciones.h"
#include "FlujoJuego.h"
#include "ETSIDI.h"
#include "GL/freeglut.h"
#include <cmath>

EstadoCreadoras::EstadoCreadoras(FlujoJuego* f) : flujo(f) {}

void EstadoCreadoras::mueve(double dt) {}

void EstadoCreadoras::dibujar() {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    // IMAGEN
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("fondos/creadoras.png").id);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-18.0f, -8.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(18.0f, -8.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(18.0f, 12.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-18.0f, 12.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // RECUADRO GRIS ABAJO
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-20.0f, -14.0f);
    glVertex2f(20.0f, -14.0f);
    glVertex2f(20.0f, -5.0f);
    glVertex2f(-20.0f, -5.0f);
    glEnd();
    glDisable(GL_BLEND);

    // BORDE AZUL AL FINAL
    glLineWidth(2.0f);
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-20.0f, -14.0f);
    glVertex2f(20.0f, -14.0f);
    glVertex2f(20.0f, -5.0f);
    glVertex2f(-20.0f, -5.0f);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-20.0, 20.0, -14.0, 14.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // TEXTO BLANCO ENCIMA
    ETSIDI::setFont("fuentes/Bitwise.ttf", 13);
    ETSIDI::setTextColor(0.1f, 0.3f, 0.8f);
    ETSIDI::printxy("Somos las creadoras de esta aventura!", -9.0f, -8.0f);
    ETSIDI::printxy("Presta atencion aunque no estemos en clase...", -9.0f, -9.0f);
    ETSIDI::printxy("Este es un juego de estrategia, mueve bien", -9.0f, -10.0f);
    ETSIDI::printxy("tus piezas y domina el tablero!", -9.0f, -11.0f);

    ETSIDI::setTextColor(0.0f, 0.0f, 0.6f);
    ETSIDI::printxy("Pulsa ESPACIO para continuar", -7.0f, -13.0f);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void EstadoCreadoras::tecla(unsigned char key) {
    if (key == ' ' || key == 13)
        flujo->cambiarEstado(new EstadoInstrucciones(flujo));
}

void EstadoCreadoras::teclaEspecial(int key) {}