

#include "Personaje.h"
#include <GL/freeglut.h>

Personaje::Personaje(bandos b, float px, float py, const char* rutaTextura)
    : bando(b), posicion(px, py),
    vida(100), fuerza(10), defensa(5),
    velocidad(1.0f), agilidad(1.0f), estela(1)
{
    p1 = { px, py };
    p2 = { px + 3.0f, py + 3.0f };

    tex.cargar(rutaTextura);
}


void Personaje::dibuja() const {
    tex.activar();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(p1.x, p1.y);
    glTexCoord2f(1, 0); glVertex2f(p2.x, p1.y);
    glTexCoord2f(1, 1); glVertex2f(p2.x, p2.y);
    glTexCoord2f(0, 1); glVertex2f(p1.x, p2.y);
    glEnd();
}

