#include "Bolo.h"
#include "GL/freeglut.h"

void Bolo::dibuja() {

    if (derribado) return;

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(p1.x, p1.y);
    glTexCoord2f(1, 1); glVertex2f(p2.x, p1.y);
    glTexCoord2f(1, 0); glVertex2f(p2.x, p2.y);
    glTexCoord2f(0, 0); glVertex2f(p1.x, p2.y);
    glEnd();


}
