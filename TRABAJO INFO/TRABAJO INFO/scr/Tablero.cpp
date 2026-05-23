#include "Tablero.h"
#include <iostream> 
#include "ETSIDI.h"




void Tablero::dibuja() const {
    // --- FONDO (sin iluminación) ---
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    fondo.dibuja();   // ahora sí se verá con su color real


    // --- TABLERO (con iluminación) ---
  
    tablero_.dibuja();

    glEnable(GL_LIGHTING);
    // --- PERSONAJE (con transparencia y textura) ---
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
	

