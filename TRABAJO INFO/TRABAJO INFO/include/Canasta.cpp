#include "Canasta.h"
#include <iostream>    

Canasta::Canasta(const Linea& p) {
    pos = p;

    ancho = 60.0f;
    alto = 50.0f;

    vel = { 10.0f, 0.0f, 0.0f };   // velocidad horizontal

    texID = ETSIDI::getTexture("elementos/canasta_1.png").id;
}

void Canasta::setPos(const Linea& p) {
    pos = p;
}

void Canasta::mueve(float t) {
    std::cout << "Moviendo canasta. X = " << pos.x << std::endl;
    pos.x += vel.x * t;

    if (pos.x > 15) vel.x = -vel.x;
    if (pos.x < -15) vel.x = -vel.x;
}

void Canasta::dibuja() {

  
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texID);
    glColor3f(1, 1, 1);

    glBegin(GL_POLYGON);

    glTexCoord2d(0, 1); glVertex3f(pos.x - ancho / 2, pos.y, pos.z);
    glTexCoord2d(1, 1); glVertex3f(pos.x + ancho / 2, pos.y, pos.z);
    glTexCoord2d(1, 0); glVertex3f(pos.x + ancho / 2, pos.y + alto, pos.z);
    glTexCoord2d(0, 0); glVertex3f(pos.x - ancho / 2, pos.y + alto, pos.z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

}

