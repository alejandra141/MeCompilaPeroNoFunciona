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

 
    float aroX = canasta.getPosX();
    float aroY = canasta.getPosY();

    // Rebote en la mitad del tablero
    disparosJ1.reboteConTablero(aroY + 1.0f, aroX, canasta.getAncho());
    disparosJ2.reboteConTablero(aroY + 1.0f, aroX, canasta.getAncho());

    // Canasta en la parte inferior del aro
    if (disparosJ1.hayCanasta(aroX, aroY, 3.0f, 1.5f)) { puntosJ1++; std::cout << "CANASTA J1: " << puntosJ1 << std::endl; }
    if (disparosJ2.hayCanasta(aroX, aroY, 3.0f, 1.5f)) { puntosJ2++; std::cout << "CANASTA J2: " << puntosJ2 << std::endl; }

    disparosJ1.limpiarInactivos();
    disparosJ2.limpiarInactivos();

    comprobarColisiones();
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

    //dibujar canasta
    canasta.dibuja();

    //zona de canasta en rojo
    float aroX = canasta.getPosX();
    float aroY = canasta.getPosY();
    float mitadZona = 3.0f / 2.0f;   
    float altoZona = 1.5f;          

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);   
    glVertex3f(aroX - mitadZona, aroY - altoZona, -1.0f);
    glVertex3f(aroX + mitadZona, aroY - altoZona, -1.0f);
    glVertex3f(aroX + mitadZona, aroY, -1.0f);
    glVertex3f(aroX - mitadZona, aroY, -1.0f);
    glEnd();
    glEnable(GL_LIGHTING);



    // disparos
    disparosJ1.dibujar(estelaJ1);
    disparosJ2.dibujar(estelaJ2);

    // barra de potencia J1 (izquierda, abajo)
    if (cargandoJ1) {
        float porcentaje = potenciaJ1 / POTENCIA_MAX;

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);

        // fondo gris
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_QUADS);
        glVertex3f(-15.0f, -8.5f, -1.0f);
        glVertex3f(1.0f, -8.5f, -1.0f);
        glVertex3f(1.0f, -7.5f, -1.0f);
        glVertex3f(-15.0f, -7.5f, -1.0f);
        glEnd();

        // relleno
        glColor3f(porcentaje, 1.0f - porcentaje, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-15.0f, -8.5f, -0.9f); //verde
        glVertex3f(-15.0f + 16.0f * porcentaje, -8.5f, -0.9f);
        glVertex3f(-15.0f + 16.0f * porcentaje, -7.5f, -0.9f);
        glVertex3f(-15.0f, -7.5f, -0.9f);//rojo
        glEnd();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }

    // barra de potencia J2 (derecha, abajo)
    if (cargandoJ2) {
        float porcentaje = potenciaJ2 / POTENCIA_MAX;

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);

        // fondo gris
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_QUADS);
        glVertex3f(2.0f, -8.5f, -1.0f);
        glVertex3f(18.0f, -8.5f, -1.0f);
        glVertex3f(18.0f, -7.5f, -1.0f);
        glVertex3f(2.0f, -7.5f, -1.0f);
        glEnd();

        // relleno
        glColor3f(porcentaje, 1.0f - porcentaje, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(2.0f, -8.5f, -0.9f);//verde
        glVertex3f(2.0f + 16.0f * porcentaje, -8.5f, -0.9f);
        glVertex3f(2.0f + 16.0f * porcentaje, -7.5f, -0.9f);
        glVertex3f(2.0f, -7.5f, -0.9f); //rojo
        glEnd();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }

    // línea de apuntado solo para jugadores con estela
    if (estelaJ1)
        dibujarLineaApuntado(j1->getPosX(), j1->getPosY(), j1->getPosZ(), anguloJ1);
    if (estelaJ2)
        dibujarLineaApuntado(j2->getPosX(), j2->getPosY(), j2->getPosZ(), anguloJ2);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    //Marcadores
    ETSIDI::setTextColor(1, 1, 0);
    ETSIDI::printxy(("J1: " + std::to_string(puntosJ1)).c_str(), -15, 9.0);
    ETSIDI::printxy(("J2: " + std::to_string(puntosJ2)).c_str(), 10.0, 9.0);

    if (estado == FIN) {
        ETSIDI::setTextColor(1, 0, 0);
        ETSIDI::printxy("FIN DE PARTIDA", -5, 5);
        ETSIDI::printxy("Pulsa C para volver", -5, 3);

        if (estado == FIN) {
            ETSIDI::setTextColor(1, 1, 0);

            if (ganador == 1)
                ETSIDI::printxy("GANADOR: JUGADOR 1", -5, 1);
            else if (ganador == 2)
                ETSIDI::printxy("GANADOR: JUGADOR 2", -5, 1);
        }
    }

    glEnable(GL_LIGHTING);

}

void CombateBaloncesto::tecla(unsigned char key) {
    switch (key) {
    case ' ':           if (!cargandoJ1) { cargandoJ1 = true; potenciaJ1 = 0.0f; } break;
    case 13:            if (!cargandoJ2) { cargandoJ2 = true; potenciaJ2 = 0.0f; } break;
    case 'a': case 'A': teclaIzqJ1 = true;  break;
    case 'd': case 'D': teclaDerJ1 = true;  break;

        if (estado == FIN && (key == 'c' || key == 'C')) {
            // aquí llamas a tu máquina de estados
        }
    }
}




void CombateBaloncesto::teclaSuelta(unsigned char key) {
    switch (key) {
    case ' ':
        if (cargandoJ1) {
            disparar(1, potenciaJ1);
            ETSIDI::play("sonidos/baloncesto/robar_balon.wav");   // ← SONIDO DE TIRO
            cargandoJ1 = false;
            potenciaJ1 = 0.0f;
        }
        break;

    case 13:
        if (cargandoJ2) {
            disparar(2, potenciaJ2);
            ETSIDI::play("sonidos/baloncesto/robar_balon.wav");   // ← SONIDO DE TIRO
            cargandoJ2 = false;
            potenciaJ2 = 0.0f;
        }
        break;
    case 'a': case 'A': teclaIzqJ1 = false; break;
    case 'd': case 'D': teclaDerJ1 = false; break;
    }
}


void CombateBaloncesto::teclaEspecial(int key) {
    std::cout << "teclaEspecial: " << key << std::endl;
    if (key == GLUT_KEY_LEFT)  teclaIzqJ2 = true;
    if (key == GLUT_KEY_RIGHT) teclaDerJ2 = true;
}

void CombateBaloncesto::teclaEspecialSuelta(int key) {
    if (key == GLUT_KEY_LEFT)  teclaIzqJ2 = false;
    if (key == GLUT_KEY_RIGHT) teclaDerJ2 = false;
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

    if (disparosJ1.hayCanasta(aroX, aroY, aroZ, radio)) {
        puntosJ1++;
        std::cout << "CANASTA J1 -> " << puntosJ1 << std::endl;
        ETSIDI::play("sonidos/baloncesto/canasta_fallida.wav");   // ← SONIDO DE CANASTA
    }
    if (disparosJ2.hayCanasta(aroX, aroY, aroZ, radio)) {
        puntosJ2++;
        std::cout << "CANASTA J2 -> " << puntosJ2 << std::endl;
        ETSIDI::play("sonidos/baloncesto/canasta_fallida.wav");   // ← SONIDO DE CANASTA

    }
    if (puntosJ1 >= 5 || puntosJ2 >= 5)
        estado = FIN;
    
    if (puntosJ1 >= 5) {
        ganador = 1;
        estado = FIN;
    }

    if (puntosJ2 >= 5) {
        ganador = 2;
        estado = FIN;
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