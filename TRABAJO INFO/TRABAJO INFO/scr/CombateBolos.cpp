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
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("fondos/Bolera_2.png").id);

    glColor3f(1, 1, 1);

    glBegin(GL_POLYGON);
    glTexCoord2d(0, 1); glVertex3f(-25, -20, -5);
    glTexCoord2d(1, 1); glVertex3f(25, -20, -5);
    glTexCoord2d(1, 0); glVertex3f(25, 16, -5);
    glTexCoord2d(0, 0); glVertex3f(-25, 16, -5);
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

    float cx1 = -5.0f;
    float cx2 = 5.0f;
    float cy = -1.0f;  // más abajo
    float sepX = 1.6f;
    float sepY = 2.4f;

    bolos.push_back(Bolo(cx1 - sepX, cy));
    bolos.push_back(Bolo(cx1, cy));
    bolos.push_back(Bolo(cx1 + sepX, cy));
    bolos.push_back(Bolo(cx1 - sepX / 2, cy + sepY));
    bolos.push_back(Bolo(cx1 + sepX / 2, cy + sepY));
    bolos.push_back(Bolo(cx1, cy + sepY * 2));

    // ── CARRIL DERECHO (J2) ──
    bolos.push_back(Bolo(cx2 - sepX, cy));
    bolos.push_back(Bolo(cx2, cy));
    bolos.push_back(Bolo(cx2 + sepX, cy));
    bolos.push_back(Bolo(cx2 - sepX / 2, cy + sepY));
    bolos.push_back(Bolo(cx2 + sepX / 2, cy + sepY));
    bolos.push_back(Bolo(cx2, cy + sepY * 2));

}
