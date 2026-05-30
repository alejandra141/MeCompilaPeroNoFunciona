#include "CombateBaloncesto.h"
#include <iostream>
#include "GL/freeglut.h"
#include "ETSIDI.h"



//CONSTRUCTOR
CombateBaloncesto::CombateBaloncesto(Personaje* j1, Personaje* j2)
    : canasta(Linea{ 0, -25, -4 }),
    j1(j1), j2(j2),
    posXj1(-8.0f), posYj1(-3.0f),
    posXj2(8.0f), posYj2(-3.0f),
    estelaJ1(j1->getTipo() == "jugador_baloncesto"),
    estelaJ2(j2->getTipo() == "jugador_baloncesto"),
    puntosJ1(0), puntosJ2(0),
    potenciaJ1(0.0f), potenciaJ2(0.0f),
    cargandoJ1(false), cargandoJ2(false),
    anguloJ1(0.0f), anguloJ2(0.0f),
    teclaIzqJ1(false), teclaDerJ1(false),
    teclaIzqJ2(false), teclaDerJ2(false)
{
}

//DESTRUCTOR

CombateBaloncesto::~CombateBaloncesto() {

}


void CombateBaloncesto::iniciarCombate() {

    ETSIDI::play("sonidos/baloncesto/entrada_combate.wav");
}


void CombateBaloncesto::mueve(double dt)
{
    // si estamos leyendo las instrucciones, congelamos el movimiento 
    if (estado == INSTRUCCIONES) return;

    float t = 0.2f;
    canasta.mueve(dt);

    // ángulos de apuntado
    if (teclaIzqJ1) { anguloJ1 -= VEL_ANGULO * dt; if (anguloJ1 < -ANGULO_MAX) anguloJ1 = -ANGULO_MAX; }
    if (teclaDerJ1) { anguloJ1 += VEL_ANGULO * dt; if (anguloJ1 > ANGULO_MAX) anguloJ1 = ANGULO_MAX; }
    if (teclaIzqJ2) { anguloJ2 -= VEL_ANGULO * dt; if (anguloJ2 < -ANGULO_MAX) anguloJ2 = -ANGULO_MAX; }
    if (teclaDerJ2) { anguloJ2 += VEL_ANGULO * dt; if (anguloJ2 > ANGULO_MAX) anguloJ2 = ANGULO_MAX; }

    if (cargandoJ1) { potenciaJ1 += VELOCIDAD_CARGA * dt; if (potenciaJ1 > POTENCIA_MAX) potenciaJ1 = POTENCIA_MAX; }
    if (cargandoJ2) { potenciaJ2 += VELOCIDAD_CARGA * dt; if (potenciaJ2 > POTENCIA_MAX) potenciaJ2 = POTENCIA_MAX; }


    int activasAntesJ1 = disparosJ1.contarActivas();
    int activasAntesJ2 = disparosJ2.contarActivas();
    int puntosAntesJ1 = puntosJ1;
    int puntosAntesJ2 = puntosJ2;

    disparosJ1.actualizar((float)dt);
    disparosJ2.actualizar((float)dt);


    float aroX = canasta.getPosX();
    float aroY = canasta.getPosY();

    // Rebote en la mitad del tablero
    disparosJ1.reboteConTablero(aroY + 1.0f, aroX, canasta.getAncho());
    disparosJ2.reboteConTablero(aroY + 1.0f, aroX, canasta.getAncho());

    // Canasta en la parte inferior del aro
    // si se encesta suena NiceShot
    if (disparosJ1.hayCanasta(aroX, aroY, 3.0f, 1.5f)) {
        puntosJ1++;
        std::cout << "CANASTA J1: " << puntosJ1 << std::endl;
        ETSIDI::play("sonidos/baloncesto/NiceShot.wav");
    }
    if (disparosJ2.hayCanasta(aroX, aroY, 3.0f, 1.5f)) {
        puntosJ2++;
        std::cout << "CANASTA J2: " << puntosJ2 << std::endl;
        ETSIDI::play("sonidos/baloncesto/NiceShot.wav");
    }

    int activasDespuesJ1 = disparosJ1.contarActivas();
    int activasDespuesJ2 = disparosJ2.contarActivas();

    // fallo de J1
    if (activasDespuesJ1 < activasAntesJ1 && puntosJ1 == puntosAntesJ1) {
        if (j1 != nullptr) j1->recibirDanio(5);
    }

    // fallo de J2
    if (activasDespuesJ2 < activasAntesJ2 && puntosJ2 == puntosAntesJ2) {
        if (j2 != nullptr) j2->recibirDanio(5);
    }

    disparosJ1.limpiarInactivos();
    disparosJ2.limpiarInactivos();

    comprobarColisiones();
}




void CombateBaloncesto::dibujar() {

    std::cout << "TexID J1: " << j1->getSprite().getTexID() << std::endl;
    std::cout << "TexID J2: " << j2->getSprite().getTexID() << std::endl;

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


    // INSTRUCCIONES

    if (estado == INSTRUCCIONES) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // RECUADRO NEGRO TRANSLÚCIDO EN EL MEDIO
        glColor4ub(0, 0, 0, 220); // Negro opaco
        glBegin(GL_QUADS);
        glVertex2f(-12.0f, -6.0f);
        glVertex2f(12.0f, -6.0f);
        glVertex2f(12.0f, 7.0f);
        glVertex2f(-12.0f, 7.0f);
        glEnd();

        // BORDE BLANCO DEL RECUADRO
        glLineWidth(3.0f);
        glColor3ub(255, 255, 255);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-12.0f, -6.0f);
        glVertex2f(12.0f, -6.0f);
        glVertex2f(12.0f, 7.0f);
        glVertex2f(-12.0f, 7.0f);
        glEnd();
        glDisable(GL_BLEND);

        // TEXTOS CON LAS INSTRUCCIONES
        ETSIDI::setFont("fuentes/Bitwise.ttf", 22);
        ETSIDI::setTextColor(1, 1, 0); // amarillo 
        ETSIDI::printxy("COMBATE BALONCESTO CONTROLES", -11.5f, 5.2f);

        ETSIDI::setFont("fuentes/Bitwise.ttf", 12);

        // CONTROLES JUGADOR 1 
        ETSIDI::setTextColor(0.2f, 0.6f, 1.0f); //azul
        ETSIDI::printxy("JUGADOR 1 (IZQUIERDA)", -11.5f, 3.2f);
        ETSIDI::setTextColor(1, 1, 1);
        ETSIDI::printxy("- Modificar Angulo: ", -11.5f, 2.0f);
        ETSIDI::printxy(" A/D", -8.5f, 1.0f);
        ETSIDI::printxy("- Mantener Potencia: ESPACIO", -11.5f, 0.0f);
        ETSIDI::printxy("- Tirar a canasta: soltar tecla", -11.5f, -1.0f);

        // CONTROLES JUGADOR 2 
        ETSIDI::setTextColor(1.0f, 0.4f, 0.7f); //rosa
        ETSIDI::printxy("JUGADOR 2 (DERECHA)", 1.0f, 3.2f);
        ETSIDI::setTextColor(1, 1, 1);
        ETSIDI::printxy("- Modificar Angulo: FLECHA IZQ", 1.0f, 2.0f);
        ETSIDI::printxy("FLECHA IZQ/FLECHA DERCH", 2.5f, 1.0f);
        ETSIDI::printxy("- Mantener Potencia: ENTER", 1.0f, 0.0f);
        ETSIDI::printxy("- Tirar a canasta: soltar tecla", 1.0f, -1.0f);

        // SALIDA
        ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
        ETSIDI::setTextColor(1, 0, 0); // rojo 
        ETSIDI::printxy("PULSA ENTER/ESPACIO PARA EMPEZAR LA PELEA", -11.0f, -4.0f);

        glEnable(GL_LIGHTING);
        return; // salimos de la función para que NO dibuje los personajes ni las vidas todavía
    }


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    //dibujar canasta
    canasta.dibuja();


    // RENDERIZADO DE LOS SPRITES PNG REALES EN LA CANCHA

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);


    // Offset J1
    float offJ1 = 0.0f;
    std::string tipoJ1 = j1->getTipo();
    if (tipoJ1 == "boxeador_kickboxing")  offJ1 = 0.5f;
    else if (tipoJ1 == "boxeador_normal") offJ1 = 0.0f;
    else if (tipoJ1 == "bolo_cranker")    offJ1 = 1.0f;
    else if (tipoJ1 == "bolo_stronker")   offJ1 = 1.0f;
    else if (tipoJ1 == "jugador_baloncesto") offJ1 = 5.0f;
    else if (tipoJ1 == "fisio")           offJ1 = 0.5f;

    // Offset J2
    float offJ2 = 0.0f;
    std::string tipoJ2 = j2->getTipo();
    if (tipoJ2 == "boxeador_kickboxing")  offJ2 = 0.5f;
    else if (tipoJ2 == "boxeador_normal") offJ2 = 0.0f;
    else if (tipoJ2 == "bolo_cranker")    offJ2 = 1.0f;
    else if (tipoJ2 == "bolo_stronker")   offJ2 = 1.0f;
    else if (tipoJ2 == "jugador_baloncesto") offJ2 = 5.0f;
    else if (tipoJ2 == "fisio")           offJ2 = 0.5f;

    float anchoPlayer = 4.5f;
    float altoPlayer = 11.0f;

    //a ver el de baloncesto es enorme vamos a forzar que se haga más pequeño

    if (j1->getTipo() == "jugador_baloncesto") {

        anchoPlayer = 2.5f;
        altoPlayer = 7.0f;

    }


    // DIBUJA SPRITE JUGADOR 1 (Izquierda)
    if (j1 != nullptr && j1->getSprite().getTexID() != 0) {
        glBindTexture(GL_TEXTURE_2D, j1->getSprite().getTexID());
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 1); glVertex3f(posXj1 - anchoPlayer, -14.0f + offJ1, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(posXj1 + anchoPlayer, -14.0f + offJ1, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(posXj1 + anchoPlayer, -14.0f + altoPlayer+offJ1, 0.0f);
        glTexCoord2d(0, 0); glVertex3f(posXj1 - anchoPlayer, -14.0f + altoPlayer+offJ1  , 0.0f);

        glEnd();
    }

    anchoPlayer = 4.5f;
    altoPlayer = 11.0f;

    //a ver el de baloncesto es enorme vamos a forzar que se haga más pequeño

    if (j2->getTipo() == "jugador_baloncesto") {

        anchoPlayer = 2.5f;
        altoPlayer = 7.0f;

    }

    // DIBUJA SPRITE JUGADOR 2 (Derecha) 
    if (j2 != nullptr && j2->getSprite().getTexID() != 0) {
        glBindTexture(GL_TEXTURE_2D, j2->getSprite().getTexID());
        glBegin(GL_POLYGON);
        glTexCoord2d(1, 1); glVertex3f(posXj2 - anchoPlayer, -14.0f + offJ2, 0.0f);
        glTexCoord2d(0, 1); glVertex3f(posXj2 + anchoPlayer, -14.0f + offJ2, 0.0f);
        glTexCoord2d(0, 0); glVertex3f(posXj2 + anchoPlayer, -14.0f + altoPlayer+offJ2, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(posXj2 - anchoPlayer, -14.0f + altoPlayer+offJ2, 0.0f);
        glEnd();
    }

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, 0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



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
        dibujarLineaApuntado(posXj1, posYj1, 0.0f, anguloJ1);
    if (estelaJ2)
        dibujarLineaApuntado(posXj2, posYj2, 0.0f, anguloJ2);

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

    //marcadores de vida
    ETSIDI::setTextColor(1, 0, 0); // vida
    ETSIDI::printxy(("Vida J1: " + std::to_string(j1->getVida())).c_str(), -15, 7.0);
    ETSIDI::printxy(("Vida J2: " + std::to_string(j2->getVida())).c_str(), 5.0, 7.0);

    glEnable(GL_LIGHTING);

}



void CombateBaloncesto::tecla(unsigned char key) {
    if (estado == INSTRUCCIONES) {
        if (key == ' ' || key == 13) { // al pulsar Espacio o Enter, arranca la pelea
            iniciarCombate(); // suena la campana de inicio
            estado = JUGANDO;
        }
        return; // bloqueamos ataques mientras se leen las instrucciones
    }

    switch (key) {
    case ' ':           if (!cargandoJ1) { cargandoJ1 = true; potenciaJ1 = 0.0f; } break;
    case 13:            if (!cargandoJ2) { cargandoJ2 = true; potenciaJ2 = 0.0f; } break;
    case 'a': case 'A': teclaIzqJ1 = true;  break;
    case 'd': case 'D': teclaDerJ1 = true;  break;

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

    if (jugador == 1)
        disparosJ1.agregar(posXj1, posYj1, 0.0f, velX, velY, 0.0f, estelaJ1);
    else
        disparosJ2.agregar(posXj2, posYj2, 0.0f, velX, velY, 0.0f, estelaJ2);
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


    if ((puntosJ1 >= 5 || puntosJ2 >= 5) && estado == JUGANDO) {
        estado = FIN;

        if (puntosJ1 >= 5) {
            ganador = 1;
        }
        else if (puntosJ2 >= 5) {
            ganador = 2;
        }

        // cuando uno de los dos gane sonara el publico aplaudiendo
        ETSIDI::play("sonidos/baloncesto/CrowdCheer.wav");
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


