#include "TexturasJugadores.h"

TexturasJugadores::TexturasJugadores()
    : texID(0), cx(0), cy(0), cz(0.3f), mitad(2.5f),
    offsetX(0.0f), offsetY(0.0f) {
}

void TexturasJugadores::setTextura(unsigned int id) { texID = id; }

void TexturasJugadores::setPosicion(float x, float y) {
    cx = x;
    cy = y;
    cz = 0.3f;   
}
void TexturasJugadores::setOffset(float ox, float oy) {
    offsetX = ox;
    offsetY = oy;
}

void TexturasJugadores::dibuja() const {
    if (texID == 0) return;

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    glColor3f(1, 1, 1);

    glPushMatrix();

    glTranslatef(cx, cy, cz);        // mover al centro de la casilla
    glTranslatef(offsetX, offsetY, 0); // corregir el desplazamiento propio del PNG
    glScalef(mitad, mitad, 1.0f);     // escalar SIN moverlo

    // 3. Dibujar un cuadrado centrado en (0,0)
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 1); glVertex3f(-1.5, -1, 0);
    glTexCoord2d(1, 1); glVertex3f(1.5, -1, 0);
    glTexCoord2d(1, 0); glVertex3f(1.5, 1, 0);
    glTexCoord2d(0, 0); glVertex3f(-1.5, 1, 0);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}