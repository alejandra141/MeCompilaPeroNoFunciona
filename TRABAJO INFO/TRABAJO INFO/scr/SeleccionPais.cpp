#include "SeleccionPais.h"
#include "ETSIDI.h"
#include <GL/freeglut.h>

void SelectorPais::moverJ1(int dir) {
    if (confirmadoJ1) return;
    indiceJ1 += dir;
    if (indiceJ1 < 0) indiceJ1 = nombres.size() - 1;
    if (indiceJ1 >= nombres.size()) indiceJ1 = 0;
    ETSIDI::play("sonidos/bolos/Sample_0002.wav");
}

void SelectorPais::moverJ2(int dir) {
    if (confirmadoJ2) return;
    indiceJ2 += dir;
    if (indiceJ2 < 0) indiceJ2 = nombres.size() - 1;
    if (indiceJ2 >= nombres.size()) indiceJ2 = 0;
    ETSIDI::play("sonidos/bolos/Sample_0002.wav");
}

bool SelectorPais::confirmarJ1() {
    if (!confirmadoJ1) {
        paisJ1 = nombres[indiceJ1];
        confirmadoJ1 = true;
        ETSIDI::play("sonidos/bolos/Sample_0000.wav");
    }
    return confirmadoJ1;
}

bool SelectorPais::confirmarJ2() {
    if (!confirmadoJ2) {
        paisJ2 = nombres[indiceJ2];
        confirmadoJ2 = true;
        ETSIDI::play("sonidos/bolos/Sample_0000.wav");
    }
    return confirmadoJ2;
}

void SelectorPais::dibuja() const {



    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);


    // FONDO
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("fondos/menu_wii.png").id);
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 1); glVertex2f(-10, -10);
    glTexCoord2d(1, 1); glVertex2f(10, -10);
    glTexCoord2d(1, 0); glVertex2f(10, 10);
    glTexCoord2d(0, 0); glVertex2f(-10, 10);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    ETSIDI::setFont("fuentes/Bitwise.ttf", 30);

    // TITULOS
    ETSIDI::setTextColor(0.8f, 0.0f, 1.0f);
    ETSIDI::printxy("Jugador 1", 4, 8);
    ETSIDI::printxy("Jugador 2", -8, 8);

    //PREPARADOOOS!!
    ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
    ETSIDI::printxy(!confirmadoJ2 ? "ESPACIO para seleccionar" : "Listo!", -9, -6);
    ETSIDI::printxy(!confirmadoJ1 ? "ENTER para seleccionar" : "Listo!", 3, -6);

    ETSIDI::setFont("fuentes/Bitwise.ttf", 30);

    //  LISTA JUGADOR 1 
    for (int i = 0; i < nombres.size(); i++) {
        if (i == indiceJ1 && !confirmadoJ1)
            ETSIDI::setTextColor(0, 1, 0);
        else if (i == indiceJ1 && confirmadoJ1)
            ETSIDI::setTextColor(0, 0.5f, 0);
        else
            ETSIDI::setTextColor(0, 0, 1);

        ETSIDI::printxy(nombres[i].c_str(), 4, 5 - i * 2);
    }

    //  LISTA JUGADOR 2 
    for (int i = 0; i < nombres.size(); i++) {
        if (i == indiceJ2 && !confirmadoJ2)
            ETSIDI::setTextColor(0, 1, 0);
        else if (i == indiceJ2 && confirmadoJ2)
            ETSIDI::setTextColor(0, 0.5f, 0);
        else
            ETSIDI::setTextColor(0, 0, 1);

        ETSIDI::printxy(nombres[i].c_str(), -8, 5 - i * 2);
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glEnable(GL_LIGHTING);
}