#include "EstadoInstrucciones.h"
#include "EstadoSeleccionPais.h"
#include "FlujoJuego.h"
#include "ETSIDI.h"
#include "GL/freeglut.h"
#include <cmath>

EstadoInstrucciones::EstadoInstrucciones(FlujoJuego* f) : flujo(f) {}

void EstadoInstrucciones::mueve(double dt) {
    tiempo += (float)dt;
}

void EstadoInstrucciones::dibujar() {

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    // FONDO
    glColor3f(0.0f, 0.0f, 0.02f);
    glBegin(GL_QUADS);
    glVertex2f(-20, -15);
    glVertex2f(20, -15);
    glVertex2f(20, 15);
    glVertex2f(-20, 15);
    glEnd();

    // PANEL CENTRAL
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.05f, 0.0f, 0.1f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-14.0f, -9.5f);
    glVertex2f(14.0f, -9.5f);
    glVertex2f(14.0f, 9.5f);
    glVertex2f(-14.0f, 9.5f);
    glEnd();

    // BORDE MORADO
    glLineWidth(2.0f);
    glColor4f(0.6f, 0.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-14.0f, -9.5f);
    glVertex2f(14.0f, -9.5f);
    glVertex2f(14.0f, 9.5f);
    glVertex2f(-14.0f, 9.5f);
    glEnd();
    glDisable(GL_BLEND);

    // TÍTULO
    ETSIDI::setFont("fuentes/Bitwise.ttf", 22);
    ETSIDI::setTextColor(0.8f, 0.0f, 1.0f);
    ETSIDI::printxy("BIENVENIDO A ARCHON WII SPORTS", -12.5f, 8.0f);

    // DESCRIPCIÓN
    ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
    ETSIDI::setTextColor(0.8f, 0.8f, 0.8f);
    ETSIDI::printxy("Dos bandos, Luz y Oscuridad, luchan por el control del tablero.", -13.0f, 6.5f);
    ETSIDI::printxy("Mueve tus piezas y combate en minijuegos para eliminar al rival.", -13.0f, 5.7f);
    ETSIDI::printxy("Gana controlando las 5 casillas de poder o eliminando al rival.", -13.0f, 4.9f);

    // SEPARADOR
    //glLineWidth(1.0f);
    //glColor3f(0.4f, 0.0f, 0.8f);
    //glBegin(GL_LINES);
    //glVertex2f(-13.0f, 4.2f);
    //glVertex2f(13.0f, 4.2f);
    //glEnd();

    // CONTROLES TABLERO — dos columnas
    ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
    ETSIDI::setTextColor(0.3f, 0.7f, 1.0f);
    ETSIDI::printxy("CONTROLES DEL TABLERO", -13.0f, 3.5f);

    ETSIDI::setFont("fuentes/Bitwise.ttf", 11);

    // Columna izquierda — movimiento
    ETSIDI::setTextColor(0.9f, 0.9f, 0.9f);
    ETSIDI::printxy("Mover cursor:   Flechas", -13.0f, 2.3f);
    ETSIDI::printxy("Selec/Mover pieza: ESPACIO", -13.0f, 1.1f);
    ETSIDI::printxy("Modo hechizo:   H", -13.0f, -0.1f);
    ETSIDI::printxy("Elegir hechizo: 1-7", -13.0f, -1.3f);
    ETSIDI::printxy("Lanzar hechizo: ESPACIO", -13.0f, -2.6f);

    // Columna derecha — hechizos
    ETSIDI::setTextColor(0.8f, 0.5f, 1.0f);
    ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
    ETSIDI::printxy("HECHIZOS DEL FISIO", 1.0f, 2.5f);

    ETSIDI::setFont("fuentes/Bitwise.ttf", 11);
    ETSIDI::printxy("1.Teleport     5.Summon", 1.0f, 1.0f);
    ETSIDI::printxy("2.Heal         6.Revive", 1.0f, -0.5f);
    ETSIDI::printxy("3.ShiftTime    7.Imprison", 1.0f, -1.5f);
    ETSIDI::printxy("4.Exchange", 1.0f, -2.5f);

    // SEPARADOR
    //glBegin(GL_LINES);
    //vertex2f(-13.0f, -2.3f);
    //vertex2f(13.0f, -2.3f);
    //glEnd();

    // CASILLAS
    ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
    ETSIDI::setTextColor(0.3f, 0.7f, 1.0f);
    ETSIDI::printxy("TIPOS DE CASILLA", -13.0f, -3.8f);

    ETSIDI::setFont("fuentes/Bitwise.ttf", 11);
    ETSIDI::setTextColor(0.9f, 0.9f, 0.9f);
    ETSIDI::printxy("Blanca: bando Luz", -13.0f, -4.0f);
    ETSIDI::printxy("Negra:  bando Oscuridad", -13.0f, -5.2f);
    ETSIDI::printxy("Morada: aleatorio", -13.0f, -6.4f);
    ETSIDI::printxy("Poder:  casillas victoria", -13.0f, -7.6f);

    // BOTÓN CONTINUAR
    float alpha = 0.5f + 0.5f * sin(tiempo * 2.0f);
    ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
    ETSIDI::setTextColor(alpha, alpha * 0.8f, 0.0f);
    ETSIDI::printxy("Pulsa ESPACIO para seleccionar pais", -8.5f, -9.5f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void EstadoInstrucciones::tecla(unsigned char key) {
    if (key == ' ' || key == 13)
        flujo->cambiarEstado(new EstadoSeleccionPais(flujo));
}

void EstadoInstrucciones::teclaEspecial(int key) {}