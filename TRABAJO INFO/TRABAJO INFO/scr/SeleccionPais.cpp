#include "SeleccionPais.h"
#include <iostream>

SelectorPais::SelectorPais() : jugadorActual(1), ratonX(0), ratonY(0)
{
    // 5 países, alineados y visibles en tu ventana
    botones = {
        {"Espana",     "espana",     0, -8.0f, -2.0f, 3.0f, 3.0f},
        {"Francia",    "francia",    0, -4.0f, -2.0f, 3.0f, 3.0f},
        {"USA",        "usa",        0,  0.0f, -2.0f, 3.0f, 3.0f},
        {"Italia",     "italia",     0,  4.0f, -2.0f, 3.0f, 3.0f},
        {"Inglaterra", "inglaterra", 0,  8.0f, -2.0f, 3.0f, 3.0f},
    };
}

bool SelectorPais::update(float mx, float my, bool click)
{
    ratonX = mx;
    ratonY = my;

    if (!click)
        return false;

    for (auto& b : botones)
    {
        if (mx >= b.x && mx <= b.x + b.w &&
            my >= b.y && my <= b.y + b.h)
        {
            if (jugadorActual == 1)
            {
                paisJ1 = b.carpeta;
                jugadorActual = 2;
            }
            else
            {
                paisJ2 = b.carpeta;
                return true;
            }
        }
    }

    return false;
}

void SelectorPais::dibuja() const
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);

    for (auto& b : botones)
    {
        glColor3f(0.2f, 0.2f, 0.8f);
        glBegin(GL_POLYGON);
        glVertex2f(b.x, b.y);
        glVertex2f(b.x + b.w, b.y);
        glVertex2f(b.x + b.w, b.y + b.h);
        glVertex2f(b.x, b.y + b.h);
        glEnd();

        ETSIDI::setTextColor(1, 1, 1);
        ETSIDI::printxy(b.nombre.c_str(), b.x, b.y + b.h + 0.5f);
    }

    // Punto rojo para depurar
    glColor3f(1, 0, 0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(ratonX, ratonY);
    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glEnable(GL_LIGHTING);
}

std::string SelectorPais::getPaisJ1() const { return paisJ1; }
std::string SelectorPais::getPaisJ2() const { return paisJ2; }
int SelectorPais::getJugadorActual() const { return jugadorActual; }
