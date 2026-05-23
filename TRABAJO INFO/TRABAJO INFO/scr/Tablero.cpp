#include "Tablero.h"
#include <iostream> 
#include "ETSIDI.h"




void Tablero::dibuja() const {
    // FONDO 
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    fondo.dibuja(); 

    // TABLERO 
    tablero_.dibuja();

    float lado = 2.0f;
    for (int fila = 0; fila < 9; fila++) {
        for (int col = 0; col < 9; col++) {

            float x1 = -9.0f + (col * lado);
            float y1 = -9.0f + (fila * lado);
            float x2 = x1 + lado;
            float y2 = y1 + lado;

            Color colorActual;
            switch (celdas[fila][col]) {
            case 0: colorActual = NEGRO; break;
            case 1: colorActual = BLANCO; break;
            case 2: colorActual = MORADO; break;
            default: colorActual = NEGRO;
            }
            Cuadrado celda({ x1, y1, 0.2f }, { x2, y2, 0.2f }, colorActual);
            celda.dibuja(); 
        }
    }
    glEnable(GL_LIGHTING);


    // PERSONAJE 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("Personajes/Fisio/buenos/Fisio_buenos.png").id);

    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);

    glBegin(GL_POLYGON);

    glTexCoord2d(0, 1); glVertex3f(-3, 0, 5);
    glTexCoord2d(1, 1); glVertex3f(3, 0, 5);
    glTexCoord2d(1, 0); glVertex3f(3, 3, 5);
    glTexCoord2d(0, 0); glVertex3f(-3, 3, 5);

    glEnd();

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);



}
	

