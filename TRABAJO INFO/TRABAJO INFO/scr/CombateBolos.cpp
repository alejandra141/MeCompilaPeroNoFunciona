#include "CombateBolos.h"
#include "GL/freeglut.h"
#include "ETSIDI.h"
#include <iostream>
#include "bolo.h"

void CombateBolos::mueve(double dt) {
    // Lógica del combate de bolos
}


void CombateBolos::tecla(unsigned char key) {
    // Teclas del combate de bolos  
}


CombateBolos::CombateBolos() {
    crearBolos();
}


void CombateBolos::dibujar() {


    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    //POR AQUI PINTAMOS UNA BOLERITA DE FONDO
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("fondos/fondo bolos.png").id);

    glColor3f(1, 1, 1);

    glBegin(GL_POLYGON);
    glTexCoord2d(0, 1); glVertex3f(-20, -20, -5);
    glTexCoord2d(1, 1); glVertex3f(20, -20, -5);
    glTexCoord2d(1, 0); glVertex3f(20, 15, -5);
    glTexCoord2d(0, 0); glVertex3f(-20, 15, -5);
    glEnd();

    //POR AQUÍ PINTAMOS UNOS BOLOS
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("elementos/bolo.png").id);

    glEnable(GL_BLEND);                                
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glColor4f(1, 1, 1, 1);


    for (auto& b : bolos) {
        b.dibuja();
    }

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

 

}



void CombateBolos::crearBolos() {

    bolos.clear();


    // fila 1 (arriba)
    bolos.push_back(Bolo(0, -2));

    // fila 2
    bolos.push_back(Bolo(-1.5, -4));
    bolos.push_back(Bolo(1.5, -4));

    // fila 3
    bolos.push_back(Bolo(-3, -6));
    bolos.push_back(Bolo(0, -6));
    bolos.push_back(Bolo(3, -6));

    // fila 4 (abajo centrado)
    bolos.push_back(Bolo(0, -8));


}