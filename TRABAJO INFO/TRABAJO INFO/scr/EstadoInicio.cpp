#include "EstadoInicio.h"
#include "EstadoInstrucciones.h"
#include "FlujoJuego.h"
#include "ETSIDI.h"
#include "GL/freeglut.h"
#include <cmath>

EstadoInicio::EstadoInicio(FlujoJuego* f) : flujo(f) {}

void EstadoInicio::mueve(double dt) {
    tiempo += (float)dt;
    pulsacion += (float)dt * 2.0f;
    if (pulsacion > 6.28f) pulsacion -= 6.28f;
}

void EstadoInicio::dibujar() {

    // FONDO NEGRO
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glColor3f(0.0f, 0.0f, 0.02f);
    glBegin(GL_QUADS);
    glVertex2f(-20, -15);
    glVertex2f(20, -15);
    glVertex2f(20, 15);
    glVertex2f(-20, 15);
    glEnd();

    // ESTRELLAS ANIMADAS
    srand(42);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 80; i++) {
        float sx = ((rand() % 400) - 200) / 10.0f;
        float sy = ((rand() % 300) - 150) / 10.0f;
        float brillo = 0.5f + 0.5f * sin(tiempo * 1.5f + i * 0.7f);
        glColor3f(brillo, brillo, brillo);
        glVertex2f(sx, sy);
    }
    glEnd();

    // LÍNEA SEPARADORA SUPERIOR
    glLineWidth(2.0f);
    glColor3f(0.5f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(-15.0f, 6.5f);
    glVertex2f(15.0f, 6.5f);
    glEnd();

    // LÍNEA SEPARADORA INFERIOR
    glBegin(GL_LINES);
    glVertex2f(-15.0f, -6.5f);
    glVertex2f(15.0f, -6.5f);
    glEnd();

    // TÍTULO PRINCIPAL — degradado luz/oscuridad
    ETSIDI::setFont("fuentes/Bitwise.ttf", 40);
    ETSIDI::setTextColor(0.8f, 0.0f, 1.0f); // morado Luz
    ETSIDI::printxy("ARCHON", -5.5f, 3.5f);

    ETSIDI::setFont("fuentes/Bitwise.ttf", 20);
    ETSIDI::setTextColor(0.3f, 0.6f, 1.0f); // azul
    ETSIDI::printxy("WII  SPORTS  EDITION", -8.5f, 1.5f);

    // SUBTÍTULO
    ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
    ETSIDI::setTextColor(0.6f, 0.6f, 0.6f);
    ETSIDI::printxy("Luz  vs  Oscuridad", -5.5f, -0.5f);

    // TEXTO PARPADEANTE
    float alpha = 0.5f + 0.5f * sin(pulsacion);
    ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
    ETSIDI::setTextColor(alpha, alpha * 0.8f, 0.0f);
    ETSIDI::printxy("Pulsa ESPACIO para comenzar", -9.0f, -4.5f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void EstadoInicio::tecla(unsigned char key) {
    if (key == ' ' || key == 13)
        flujo->cambiarEstado(new EstadoInstrucciones(flujo));
}

void EstadoInicio::teclaEspecial(int key) {}