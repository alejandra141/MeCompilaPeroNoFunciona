#include "CombateBolos.h"
#include "GL/freeglut.h"
#include "ETSIDI.h"
#include <iostream>
#include "bolo.h"

void CombateBolos::mueve(double dt) {
    

    // vale esto es para el apuntador, que se mueve de un lado al otro
    float velocidad = 2.0f;

    anguloJ1 += dirJ1 * velocidad * dt;
    if (anguloJ1 > 1.0f) dirJ1 = -1;
    if (anguloJ1 < -1.0f) dirJ1 = 1;

    anguloJ2 += dirJ2 * velocidad * dt;
    if (anguloJ2 > 1.0f) dirJ2 = -1;
    if (anguloJ2 < -1.0f) dirJ2 = 1;

}


void CombateBolos::tecla(unsigned char key) {
    // Teclas del combate de bolos  
}


CombateBolos::CombateBolos() : bolosDerribadosJ1(0), bolosDerribadosJ2(0), //esto es para hacer pruebas
j1esEspecialista(false), j2esEspecialista(true), anguloJ1(0), dirJ1(1),
anguloJ2(0), dirJ2(1) {
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
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

 // VAMOS A PINTAR LAS ESTELAS DE APUNTAR POR AQUÍ


    // ── PUNTERO J1 (amarillo → verde neón) ──
    float cx1 = -5.0f;
    float baseY = -9.0f;
    float longitud = j1esEspecialista ? 6.0f : 4.0f;
    float puntaX1 = cx1 + sin(anguloJ1) * longitud;
    float puntaY1 = baseY + longitud;

    glBegin(GL_TRIANGLES);
    glColor4f(1.0f, 1.0f, 0.0f, 0.9f);
    glVertex2f(cx1 - 0.2f, baseY);
    glColor4f(1.0f, 0.5f, 0.0f, 0.9f);
    glVertex2f(cx1 + 0.2f, baseY);
    glColor4f(0.0f, 1.0f, 0.2f, 0.9f);
    glVertex2f(puntaX1, puntaY1);
    glEnd();

    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(cx1 - 0.2f, baseY);
    glVertex2f(cx1 + 0.2f, baseY);
    glVertex2f(puntaX1, puntaY1);
    glEnd();

    // ── PUNTERO J2 (cyan → magenta) ──
    float cx2 = 5.0f;
    float longitud2 = j2esEspecialista ? 6.0f : 4.0f;
    float puntaX2 = cx2 + sin(anguloJ2) * longitud2;
    float puntaY2 = baseY + longitud2;

    glBegin(GL_TRIANGLES);
    glColor4f(0.0f, 1.0f, 1.0f, 0.9f);
    glVertex2f(cx2 - 0.2f, baseY);
    glColor4f(1.0f, 0.0f, 1.0f, 0.9f);
    glVertex2f(cx2 + 0.2f, baseY);
    glColor4f(1.0f, 1.0f, 0.0f, 0.9f);
    glVertex2f(puntaX2, puntaY2);
    glEnd();

    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(cx2 - 0.2f, baseY);
    glVertex2f(cx2 + 0.2f, baseY);
    glVertex2f(puntaX2, puntaY2);
    glEnd();

    // ── FIN ──
    glDisable(GL_BLEND);
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
