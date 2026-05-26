#include "CombateBaloncesto.h"
#include <iostream>
#include "GL/freeglut.h"
#include "ETSIDI.h"

#include "CombateBaloncesto.h"
#include <iostream>
#include "GL/freeglut.h"
#include "ETSIDI.h"


//CONSTRUCTOR
CombateBaloncesto::CombateBaloncesto(Basketboller* j1, Basketboller* j2)
    : canasta(Linea{ 0, -25, -4 }),
    j1(j1), j2(j2),
    estelaJ1(j1->getVelocidad() >= UMBRAL_ESTELA),
    estelaJ2(j2->getVelocidad() >= UMBRAL_ESTELA),
    puntosJ1(0), puntosJ2(0),
    potenciaJ1(0.0f), potenciaJ2(0.0f),
    cargandoJ1(false), cargandoJ2(false),
    anguloJ1(0.0f), anguloJ2(0.0f),         // <- añadir
    teclaIzqJ1(false), teclaDerJ1(false),   // <- añadir
    teclaIzqJ2(false), teclaDerJ2(false)    // <- añadir
{
}

//DESTRUCTOR

CombateBaloncesto::~CombateBaloncesto() {
    delete j1;
    delete j2;
}





void CombateBaloncesto::mueve(double dt)
{
    float t = 0.2f;
    canasta.mueve(dt);

    // ángulos de apuntado
    if (teclaIzqJ1) { anguloJ1 -= VEL_ANGULO * dt; if (anguloJ1 < -ANGULO_MAX) anguloJ1 = -ANGULO_MAX; }
    if (teclaDerJ1) { anguloJ1 += VEL_ANGULO * dt; if (anguloJ1 > ANGULO_MAX) anguloJ1 = ANGULO_MAX; }
    if (teclaIzqJ2) { anguloJ2 -= VEL_ANGULO * dt; if (anguloJ2 < -ANGULO_MAX) anguloJ2 = -ANGULO_MAX; }
    if (teclaDerJ2) { anguloJ2 += VEL_ANGULO * dt; if (anguloJ2 > ANGULO_MAX) anguloJ2 = ANGULO_MAX; }

    if (cargandoJ1) { potenciaJ1 += VELOCIDAD_CARGA * dt; if (potenciaJ1 > POTENCIA_MAX) potenciaJ1 = POTENCIA_MAX; }
    if (cargandoJ2) { potenciaJ2 += VELOCIDAD_CARGA * dt; if (potenciaJ2 > POTENCIA_MAX) potenciaJ2 = POTENCIA_MAX; }



    disparosJ1.actualizar((float)dt);
    disparosJ2.actualizar((float)dt);

    comprobarColisiones();

    disparosJ1.limpiarInactivos();
    disparosJ2.limpiarInactivos();
}



void CombateBaloncesto::dibujar() {
    glDisable(GL_LIGHTING);      
    glEnable(GL_TEXTURE_2D);    

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
    // disparos
    disparosJ1.dibujar(estelaJ1);
    disparosJ2.dibujar(estelaJ2);

    // barra de potencia J1 (izquierda, abajo)
    if (cargandoJ1) {
        float porcentaje = potenciaJ1 / POTENCIA_MAX;

        glDisable(GL_LIGHTING);      
        glDisable(GL_TEXTURE_2D);
        // fondo gris
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        glVertex3f(-18.0f, -18.5f, -4.5f);
        glVertex3f(-2.0f, -18.5f, -4.5f);
        glVertex3f(-2.0f, -17.5f, -4.5f);
        glVertex3f(-18.0f, -17.5f, -4.5f);
        glEnd();

        // relleno verde → rojo
        glColor3f(porcentaje, 1.0f - porcentaje, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(-18.0f, -18.5f, -4.4f);
        glVertex3f(-18.0f + 16.0f * porcentaje, -18.5f, -4.4f);
        glVertex3f(-18.0f + 16.0f * porcentaje, -17.5f, -4.4f);
        glVertex3f(-18.0f, -17.5f, -4.4f);
        glEnd();

        glEnable(GL_LIGHTING);
    }

    // barra de potencia J2 (derecha, abajo)
    if (cargandoJ2) {
        float porcentaje = potenciaJ2 / POTENCIA_MAX;

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        // fondo gris
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        glVertex3f(2.0f, -18.5f, -4.5f);
        glVertex3f(18.0f, -18.5f, -4.5f);
        glVertex3f(18.0f, -17.5f, -4.5f);
        glVertex3f(2.0f, -17.5f, -4.5f);
        glEnd();

        // relleno verde → rojo
        glColor3f(porcentaje, 1.0f - porcentaje, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(2.0f, -18.5f, -4.4f);
        glVertex3f(2.0f + 16.0f * porcentaje, -18.5f, -4.4f);
        glVertex3f(2.0f + 16.0f * porcentaje, -17.5f, -4.4f);
        glVertex3f(2.0f, -17.5f, -4.4f);
        glEnd();

        glEnable(GL_LIGHTING);
    }

    // línea de apuntado solo para jugadores con estela
    if (estelaJ1)
        dibujarLineaApuntado(j1->getPosX(), j1->getPosY(), j1->getPosZ(), anguloJ1);
    if (estelaJ2)
        dibujarLineaApuntado(j2->getPosX(), j2->getPosY(), j2->getPosZ(), anguloJ2);

}

void CombateBaloncesto::tecla(unsigned char key) {
    switch (key) {
    case ' ':           if (!cargandoJ1) { cargandoJ1 = true; potenciaJ1 = 0.0f; } break;
    case 13:            if (!cargandoJ2) { cargandoJ2 = true; potenciaJ2 = 0.0f; } break;
    case 'a': case 'A': teclaIzqJ2 = true;  break;
    case 'd': case 'D': teclaDerJ2 = true;  break;
    }
}




void CombateBaloncesto::teclaSuelta(unsigned char key) {
    switch (key) {
    case ' ':           if (cargandoJ1) { disparar(1, potenciaJ1); cargandoJ1 = false; potenciaJ1 = 0.0f; } break;
    case 13:            if (cargandoJ2) { disparar(2, potenciaJ2); cargandoJ2 = false; potenciaJ2 = 0.0f; } break;
    case 'a': case 'A': teclaIzqJ2 = false; break;
    case 'd': case 'D': teclaDerJ2 = false; break;
    }
}


void CombateBaloncesto::teclaEspecial(int key) {
    std::cout << "teclaEspecial: " << key << std::endl;
    if (key == GLUT_KEY_LEFT)  teclaIzqJ1 = true;
    if (key == GLUT_KEY_RIGHT) teclaDerJ1 = true;
}

void CombateBaloncesto::teclaEspecialSuelta(int key) {
    if (key == GLUT_KEY_LEFT)  teclaIzqJ1 = false;
    if (key == GLUT_KEY_RIGHT) teclaDerJ1 = false;
}



void CombateBaloncesto::disparar(int jugador, float potencia) {
    float angulo = (jugador == 1) ? anguloJ1 : anguloJ2;
    float rad = angulo * 3.14159f / 180.0f;
    float velX = potencia * 3.0f * std::sin(rad);
    float velY = potencia * 3.0f * std::cos(rad);
    float velZ = 0.0f;

    if (jugador == 1)
        disparosJ1.agregar(j1->getPosX(), j1->getPosY(), j1->getPosZ(), velX, velY, velZ, estelaJ1);
    else
        disparosJ2.agregar(j2->getPosX(), j2->getPosY(), j2->getPosZ(), velX, velY, velZ, estelaJ2);
}


void CombateBaloncesto::comprobarColisiones() {
    float aroX = canasta.getPosX();
    float aroY = canasta.getPosY();
    float aroZ = canasta.getPosZ();
    float radio = canasta.getRadio();

    if (disparosJ1.hayColisionConAro(aroX, aroY, aroZ, radio)) {
        puntosJ1++;
        std::cout << "¡CANASTA J1! -> " << puntosJ1 << std::endl;
    }
    if (disparosJ2.hayColisionConAro(aroX, aroY, aroZ, radio)) {
        puntosJ2++;
        std::cout << "¡CANASTA J2! -> " << puntosJ2 << std::endl;
    }
}

void CombateBaloncesto::dibujarLineaApuntado(float x, float y, float z, float angulo) const {
    float rad = angulo * 3.14159f / 180.0f;
    float dirX = std::sin(rad);
    float dirY = std::cos(rad);

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(4.0f);

    int   nPuntos = 8;
    float paso = 1.5f;
    glBegin(GL_POINTS);
    for (int i = 1; i <= nPuntos; i++) {
        float alpha = 1.0f - (float)i / (float)nPuntos;
        glColor4f(1.0f, 0.8f, 0.0f, alpha);
        glVertex3f(x + dirX * paso * i,
            y + dirY * paso * i,
            z);
    }
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}