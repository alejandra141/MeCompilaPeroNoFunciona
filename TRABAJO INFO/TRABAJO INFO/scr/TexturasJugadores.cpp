#include "TexturasJugadores.h"

TexturasJugadores::TexturasJugadores() : texID(0), cx(0), cy(0), cz(0.3f), mitad(2.0f) {}

void TexturasJugadores::setTextura(unsigned int id) { texID = id; }

void TexturasJugadores::setPosicion(float x, float y) { cx = x; cy = y; }

void TexturasJugadores::dibuja() const {
    if (texID == 0) return;

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    glColor3f(1, 1, 1);

    glPushMatrix();

    // 1. Mover al centro de la casilla
    glTranslatef(cx, cy, cz);

    // 2. Tamaño REAL que tú quieres (mitad)
    float tamReal = mitad * 2.0f;   // tamaño total del personaje

    // 3. Tamaño máximo permitido dentro de la casilla
    float tamCasilla = 2.0f;        // tu casilla mide 2 unidades
    float tamMax = tamCasilla * 0.95f; // 95% de la casilla

    // 4. Calcular escala automática
    float escala = tamMax / tamReal;
    if (escala > 1.0f) escala = 1.0f; // si es pequeño, no lo reduzcas

    glScalef(escala, escala, 1.0f);

    // 5. Dibujar un cuadrado base de 1x1
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 1); glVertex3f(-1, -1, 0);
    glTexCoord2d(1, 1); glVertex3f(1, -1, 0);
    glTexCoord2d(1, 0); glVertex3f(1, 1, 0);
    glTexCoord2d(0, 0); glVertex3f(-1, 1, 0);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}
