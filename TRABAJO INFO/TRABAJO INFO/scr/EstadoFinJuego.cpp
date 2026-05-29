
#include "EstadoFinJuego.h"
#include "GL/freeglut.h"
#include "ETSIDI.h"
#include <string>
#include <iostream>
using namespace std; 

void EstadoFinJuego::dibujar() {
    // Imagen
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("elementos/finjuego.png").id);
    glColor4f(1, 1, 1, 1);

    float tam = 10.0f * escala;  // ← tamaño basado en escala
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(-tam, -tam);
    glTexCoord2f(1, 1); glVertex2f(tam, -tam);
    glTexCoord2f(1, 0); glVertex2f(tam, tam);
    glTexCoord2f(0, 0); glVertex2f(-tam, tam);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    // Texto ganador
    if (escala >= 1.0f) {
        glDisable(GL_DEPTH_TEST);
        std::string texto = "Ha ganado el Jugador " + std::to_string(idGanador);
        glColor3f(1, 1, 0);
        glRasterPos2f(-3, -4);
        for (char c : texto)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

}

void EstadoFinJuego::mueve(double dt) {
    cout << "escala: " << escala << endl;
    if (escala < 1.0f)
        escala += dt * 0.4f;
    if (escala > 1.0f)
        escala = 1.0f;
}