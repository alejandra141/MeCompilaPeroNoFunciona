#include "Canasta.h"

Canasta::Canasta(float px, float py, float pz) { //constructor con parámetros para la posición inicial de la canasta   guarda la posicion inicial  define el tamaño y guarda el ID de la txtura 

    x = px;
    y = py;
    z = pz;

    ancho = 35.0f;
    alto = 35.0f;

    texID = ETSIDI::getTexture("elementos/canasta.png").id;
}

void Canasta::setPos(float px, float py, float pz) {  //va a servir para mover la canasta a lo largo del juego, actualizando su posición según los parámetros dados
    x = px;
    y = py;
    z = pz;
}

void Canasta::mueve(float t) {
    
}

void Canasta::dibuja() {

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texID);
    glColor3f(1, 1, 1);

    glBegin(GL_POLYGON);

    glTexCoord2d(0, 1); glVertex3f(x - ancho / 2, y, z);
    glTexCoord2d(1, 1); glVertex3f(x + ancho / 2, y, z);
    glTexCoord2d(1, 0); glVertex3f(x + ancho / 2, y + alto, z);
    glTexCoord2d(0, 0); glVertex3f(x - ancho / 2, y + alto, z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}