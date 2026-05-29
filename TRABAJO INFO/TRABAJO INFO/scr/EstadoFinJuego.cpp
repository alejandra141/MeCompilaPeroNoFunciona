
#include "EstadoFinJuego.h"
#include "GL/freeglut.h"
#include "ETSIDI.h"
#include <string>

void EstadoFinJuego::dibujar() {
    // Imagen
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("elementos/finjuego.png").id);
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(-10, -10);
    glTexCoord2f(1, 1); glVertex2f(10, -10);
    glTexCoord2f(1, 0); glVertex2f(10, 10);
    glTexCoord2f(0, 0); glVertex2f(-10, 10);
    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    // Texto ganador
    std::string texto = "Ha ganado el Jugador " + std::to_string(idGanador);
    glColor3f(1, 1, 0);
    glRasterPos2f(-3, 7);
    for (char c : texto)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
}