#include "CombateBaloncesto.h"
#include <iostream>
#include "GL/freeglut.h"
#include "ETSIDI.h"

CombateBaloncesto::CombateBaloncesto()
    : canasta(2, -20, -4)   // posición inicial de la canasta
{
}

void CombateBaloncesto::actualizar() {
    // Lógica del combate de baloncesto
}

void CombateBaloncesto::dibujar() {
    glDisable(GL_LIGHTING);      // que la luz no afecte al fondo
    glEnable(GL_TEXTURE_2D);     // activar texturas

    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("fondos/Fondo_baloncesto.png").id);
    glColor3f(1, 1, 1);          

    glBegin(GL_POLYGON);

    // plano sobre el que se pone la imagen (para ajustar la imagen se usa esto)
    glTexCoord2d(0, 1); glVertex3f(-20, -20, -5);
    glTexCoord2d(1, 1); glVertex3f(20, -20, -5);
    glTexCoord2d(1, 0); glVertex3f(20, 15, -5);
    glTexCoord2d(0, 0); glVertex3f(-20, 15, -5);

    glEnd();


    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);


    canasta.dibuja();

}

void CombateBaloncesto::tecla(unsigned char key) {
    // Teclas del combate de baloncesto
}
