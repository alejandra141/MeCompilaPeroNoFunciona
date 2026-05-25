#include "BolaBolos.h"
#include "GL/freeglut.h"
#include <cmath>
#include "ETSIDI.h"

void BolaBolos::dibuja() {

    if (!activa) return;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("elementos/bola bolos.png").id);
    glColor4f(1, 1, 1, 1);

    float tam = 0.8f;
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(posicion.x - tam, posicion.y - tam);
    glTexCoord2f(1, 1); glVertex2f(posicion.x + tam, posicion.y - tam);
    glTexCoord2f(1, 0); glVertex2f(posicion.x + tam, posicion.y + tam);
    glTexCoord2f(0, 0); glVertex2f(posicion.x - tam, posicion.y + tam);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}