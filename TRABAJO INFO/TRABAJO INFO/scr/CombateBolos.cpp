
#include "CombateBolos.h"
#include "GL/freeglut.h"
#include "ETSIDI.h"
#include <iostream>
#include "bolo.h"
#include <string>


CombateBolos::CombateBolos(Personaje* j1, Personaje* j2)
    : jugador1(j1), jugador2(j2),
    bolosDerribadosJ1(0), bolosDerribadosJ2(0),
    posXj1(-5.0f), posYj1(-9.0f),
    posXj2(5.0f), posYj2(-9.0f),
    anguloJ1(0), dirJ1(1), anguloJ2(0), dirJ2(1),
    potenciaJ1(0), potenciaJ2(0),
    cargandoJ1(false), cargandoJ2(false),
    lanzandoJ1(false), lanzandoJ2(false),
    tiempoFinJuego(0), estado(INSTRUCCIONES), ganador(0)
{
    //se que esto no esta muy bien pero es que habia mucho lag y es para cargar las texturas antes y que se quite el lag
    ETSIDI::getTexture("elementos/bola bolos.png");
    ETSIDI::getTexture("elementos/bolo.png");
    ETSIDI::getTexture("fondos/Bolera_2.png");

    // especialistas
    if (jugador1 != nullptr) {
        std::string t1 = jugador1->getTipo();
        j1esEspecialista = (t1 == "bolo_cranker" || t1 == "bolo_stronker");
    }
    if (jugador2 != nullptr) {
        std::string t2 = jugador2->getTipo();
        j2esEspecialista = (t2 == "bolo_cranker" || t2 == "bolo_stronker");
    }

    crearBolos();
}

void CombateBolos::iniciarCombate() {

    ETSIDI::play("sonidos/genericos/entrada_combate.wav");
}

void CombateBolos::comprobarColisiones() {

    //  JUGADOR 1 para comprobar colisiones y restar visa si falla
    if (bolaJ1.activa) {

        for (int i = 0; i < 6; i++) {
            if (!bolos[i].isDerribado()) {

                float dx = bolaJ1.posicion.x - bolos[i].getPosicion().x;
                float dy = bolaJ1.posicion.y - bolos[i].getPosicion().y;

                if (sqrt(dx * dx + dy * dy) < 1.5f) {

                    bolos[i].derribar();
                    bolosDerribadosJ1++;
                    tiempoEfectoJ1 = 1.5f;

                    j1DerriboEnEsteLanzamiento = true;

                    // se cae 1 solo bolo
                    ETSIDI::play("sonidos/bolos/caida_bolo.wav");

                }
            }
        }

        // cuando la bola sale
        if (bolaJ1.posicion.y > 8.0f) {

            if (!j1DerriboEnEsteLanzamiento && jugador1 != nullptr)
                jugador1->recibirDanio(5);

            j1DerriboEnEsteLanzamiento = false;
            bolaJ1.resetear();
        }
    }


    // JUGADOR 2 
    if (bolaJ2.activa) {

        for (int i = 6; i < 12; i++) {
            if (!bolos[i].isDerribado()) {

                float dx = bolaJ2.posicion.x - bolos[i].getPosicion().x;
                float dy = bolaJ2.posicion.y - bolos[i].getPosicion().y;

                if (sqrt(dx * dx + dy * dy) < 1.5f) {

                    bolos[i].derribar();
                    bolosDerribadosJ2++;
                    tiempoEfectoJ2 = 1.5f;

                    j2DerriboEnEsteLanzamiento = true;

                    // se cae 1 solo bolo
                    ETSIDI::play("sonidos/bolos/caida_bolo.wav");

                }
            }
        }

        if (bolaJ2.posicion.y > 8.0f) {

            if (!j2DerriboEnEsteLanzamiento && jugador2 != nullptr)
                jugador2->recibirDanio(5);

            j2DerriboEnEsteLanzamiento = false;
            bolaJ2.resetear();
        }
    }

    // para finalizar el  juego
    if ((bolosDerribadosJ1 >= 6 || bolosDerribadosJ2 >= 6) && estado == JUGANDO) {
        estado = FIN;

        if (bolosDerribadosJ1 >= 6) {
            ganador = 1;
        }
        else if (bolosDerribadosJ2 >= 6) {
            ganador = 2;
        }

        // cuando uno de los dos gane sonara el publico aplaudiendo
        ETSIDI::play("sonidos/genericos/CrowdCheer.wav");
    }

}

void CombateBolos::mueve(double dt) {

    // si estamos leyendo las instrucciones, congelamos el movimiento 
    if (estado == INSTRUCCIONES) return;

    if (dt > 0.016) dt = 0.016;

    // vale esto es para el apuntador, que se mueve de un lado al otro
    float velocidad = 2.0f;

    anguloJ1 += dirJ1 * velocidad * (float)dt;
    if (anguloJ1 > 1.0f) dirJ1 = -1;
    if (anguloJ1 < -1.0f) dirJ1 = 1;

    anguloJ2 += dirJ2 * velocidad * (float)dt;
    if (anguloJ2 > 1.0f) dirJ2 = -1;
    if (anguloJ2 < -1.0f) dirJ2 = 1;


    //AQUÍ VAMOS A PONER QUE SE CARGUE LA POTENCIA Y ESO
    float maxPotencia = 10.0f;
    float velocidadCarga = 15.0f;

    if (cargandoJ1 && potenciaJ1 < maxPotencia)
        potenciaJ1 += velocidadCarga * (float)dt;

    if (cargandoJ2 && potenciaJ2 < maxPotencia)
        potenciaJ2 += velocidadCarga * (float)dt; // hay que poner un cast aquí dt es double vel es float

    // ESTO ES PARA MOVER LAS BOLAS DE BOLOS

    bolaJ1.mueve((float)dt);
    bolaJ2.mueve((float)dt);

    comprobarColisiones();
    if (tiempoEfectoJ1 > 0) tiempoEfectoJ1 -= (float)dt;
    if (tiempoEfectoJ2 > 0) tiempoEfectoJ2 -= (float)dt;

}


void CombateBolos::tecla(unsigned char key) {

    if (estado == INSTRUCCIONES) {
        if (key == ' ' || key == 13) { // al pulsar Espacio o Enter, arranca el combate
            iniciarCombate(); // suena la campana de inicio
            estado = JUGANDO;
        }
        return; // bloquea la carga de potencia mientras leen las instrucciones
    }

    //tenemos que poner que la potencia se cargue solo si la bola no está activa
    if (key == 'w' && !bolaJ1.activa) cargandoJ1 = true;
    if (key == 'i' && !bolaJ2.activa) cargandoJ2 = true;

}

//he creado esta clase para que se pueda cargar la potencia bien cuando sueltas la tecla
void CombateBolos::teclaSuelta(unsigned char key) {

    if (key == 'w' && !bolaJ1.activa) {
        cargandoJ1 = false;

        if (potenciaJ1 > 0) {  //hay que poner esto para solo lanzar si hay potencia en la barra

            float factorCurvaJ1 = j1esEspecialista ? 2.5f : 1.5f;// le vamos a poner bola curva jajajjaja
            float velX = sin(anguloJ1) * potenciaJ1 * factorCurvaJ1;

            float velY = potenciaJ1 * 3.0f;
            bolaJ1.lanzar(posXj1, posYj1, velX, velY);
            ETSIDI::play("sonidos/Bowling/Sample_0009.wav");
        }
        potenciaJ1 = 0; // reseteamos la potencia para que no se quede cargada después de lanzar

    }


    if (key == 'i' && !bolaJ2.activa) {
        cargandoJ2 = false;

        if (potenciaJ2 > 0) {  //hay que poner esto para solo lanzar si hay potencia en la barra

            float factorCurvaJ2 = j2esEspecialista ? 2.5f : 1.5f;// le vamos a poner bola curva jajajaj
            float velX = sin(anguloJ2) * potenciaJ2 * factorCurvaJ2;

            float velY = potenciaJ2 * 3.0f;
            bolaJ2.lanzar(posXj2, posYj2, velX, velY);
            ETSIDI::play("sonidos/Bowling/Sample_0009.wav");
        }
        potenciaJ2 = 0;
    }
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


    for (auto& b : bolos) {
        b.dibuja();
    }

    //zona de pintura de bolas
    bolaJ1.dibuja();
    bolaJ2.dibuja();


    //RENDERIZADO DE LOS SPRITES PNG REALES EN LA BOLERA
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    //el offset para poder dibujarles bien 

    // Offset J1
    float offJ1 = 0.0f;
    std::string tipoJ1 = jugador1->getTipo();
    if (tipoJ1 == "boxeador_kickboxing")  offJ1 = 0.5f;
    else if (tipoJ1 == "boxeador_normal") offJ1 = 0.0f;
    else if (tipoJ1 == "bolo_cranker")    offJ1 = 1.0f;
    else if (tipoJ1 == "bolo_stronker")   offJ1 = 1.0f;
    else if (tipoJ1 == "jugador_baloncesto") offJ1 = 5.0f;
    else if (tipoJ1 == "fisio")           offJ1 = 0.5f;

    // Offset J2
    float offJ2 = 0.0f;
    std::string tipoJ2 = jugador2->getTipo();
    if (tipoJ2 == "boxeador_kickboxing")  offJ2 = 0.5f;
    else if (tipoJ2 == "boxeador_normal") offJ2 = 0.0f;
    else if (tipoJ2 == "bolo_cranker")    offJ2 = 1.0f;
    else if (tipoJ2 == "bolo_stronker")   offJ2 = 1.0f;
    else if (tipoJ2 == "jugador_baloncesto") offJ2 = 5.0f;
    else if (tipoJ2 == "fisio")           offJ2 = 0.5f;

    float anchoPlayer = 3.5f;
    float altoPlayer = 9.0f;

    //a ver el de baloncesto es enorme vamos a forzar que se haga más pequeño

    if (jugador1->getTipo() == "jugador_baloncesto") {

        anchoPlayer = 2.5f;
        altoPlayer = 7.0f;

    }

    //DIBUJAR JUGADOR 1
    if (jugador1 != nullptr && jugador1->getSprite().getTexID() != 0) {
        glBindTexture(GL_TEXTURE_2D, jugador1->getSprite().getTexID());
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 1); glVertex3f(posXj1 - anchoPlayer, -16.0f + offJ1, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(posXj1 + anchoPlayer, -16.0f + offJ1, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(posXj1 + anchoPlayer, -16.0f + offJ1 + altoPlayer, 0.0f);
        glTexCoord2d(0, 0); glVertex3f(posXj1 - anchoPlayer, -16.0f + offJ1 + altoPlayer, 0.0f);
        glEnd();
    }

    anchoPlayer = 3.5f;
    altoPlayer = 9.0f;


    if (jugador2->getTipo() == "jugador_baloncesto") {

        anchoPlayer = 2.5f;
        altoPlayer = 7.0f;

    }

    //DIBUJAR JUGADOR 2
    if (jugador2 != nullptr && jugador2->getSprite().getTexID() != 0) {
        glBindTexture(GL_TEXTURE_2D, jugador2->getSprite().getTexID());
        glBegin(GL_POLYGON);
        glTexCoord2d(1, 1); glVertex3f(posXj2 - anchoPlayer, -16.0f+offJ2, 0.0f);
        glTexCoord2d(0, 1); glVertex3f(posXj2 + anchoPlayer, -16.0f+offJ2, 0.0f);
        glTexCoord2d(0, 0); glVertex3f(posXj2 + anchoPlayer, -16.0f + offJ2 + altoPlayer, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(posXj2 - anchoPlayer, -16.0f + offJ2 + altoPlayer, 0.0f);
        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // INSTRUCCIONES 

    if (estado == INSTRUCCIONES) {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // RECUADRO NEGRO TRANSLÚCIDO EN EL MEDIO
        glColor4ub(0, 0, 0, 220);
        glBegin(GL_QUADS);
        glVertex2f(-12.0f, -6.0f);
        glVertex2f(12.0f, -6.0f);
        glVertex2f(12.0f, 7.0f);
        glVertex2f(-12.0f, 7.0f);
        glEnd();

        // BORDE BLANCO
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
        ETSIDI::setFont("fuentes/Bitwise.ttf", 24);
        ETSIDI::setTextColor(1, 1, 0); // amarillo
        ETSIDI::printxy("COMBATE BOLOS CONTROLES", -9.5f, 5.2f);

        ETSIDI::setFont("fuentes/Bitwise.ttf", 14);

        //CONTROLES GENERALES
        ETSIDI::setTextColor(1, 1, 1); // blanco
        ETSIDI::printxy("CONTROLES GENERALES", -7.5f, 4.0f);
        ETSIDI::printxy("- Apuntado: Automatico", -9.0f, 2.0f);
        ETSIDI::printxy("- Lanzar: Soltar tecla", -9.0f, 1.0f);

        // CONTROLES JUGADOR 1 
        ETSIDI::setTextColor(0.2f, 0.6f, 1.0f); // azul
        ETSIDI::printxy("JUGADOR 1 (IZQUIERDA)", -11.0f, -1.0f);
        ETSIDI::setTextColor(1, 1, 1);
        ETSIDI::printxy("- Mantener Potencia: W", -11.0f, -2.0f);

        // CONTROLES JUGADOR 2 
        ETSIDI::setTextColor(1.0f, 0.4f, 0.7f); // rosa
        ETSIDI::printxy("JUGADOR 2 (DERECHA)", 1.5f, -1.0f);
        ETSIDI::setTextColor(1, 1, 1);
        ETSIDI::printxy("- Mantener Potencia: I", 1.5f, -2.0f);

        // SALIDA
        ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
        ETSIDI::setTextColor(1, 0, 0); //rojo
        ETSIDI::printxy("PULSA ENTER/ESPACIO PARA EMPEZAR LA PELEA", -10.5f, -4.0f);

    }


    //AQUI VAMOS A PINTAR LAS BARRITAS DE POTENCIA, QUE SE VAYAN LLENANDO SEGÚN LA POTENCIA QUE SE VAYA CARGANDO

    if (estado == JUGANDO || estado == FIN) {
        glShadeModel(GL_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);
        glColor3f(0.3f, 0.3f, 0.3f);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);




        // Fondo gris J1
        glColor3f(0.3f, 0.3f, 0.3f);
        float barraX1 = -12.0f;
        float barraBaseY = -5.0f;
        float barraAlto = 8.0f;
        float barraAncho = 1.0f;
        glBegin(GL_QUADS);
        glVertex2f(barraX1, barraBaseY);
        glVertex2f(barraX1 + barraAncho, barraBaseY);
        glVertex2f(barraX1 + barraAncho, barraBaseY + barraAlto);
        glVertex2f(barraX1, barraBaseY + barraAlto);
        glEnd();

        // Relleno J1
        float altoRelleno = (potenciaJ1 / 10.0f) * barraAlto;

        glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f);  // El verde tiene que ir abajito que es poca potencia
        glVertex2f(barraX1, barraBaseY);
        glVertex2f(barraX1 + barraAncho, barraBaseY);
        glColor3f(1.0f, 0.0f, 0.0f);  // El rojo tiene que ir arribita que es mucha potencia
        glVertex2f(barraX1 + barraAncho, barraBaseY + altoRelleno);
        glVertex2f(barraX1, barraBaseY + altoRelleno);
        glEnd();


        // Fondo gris J2
        glColor3f(0.3f, 0.3f, 0.3f);
        float barraX2 = 11.5f;
        glBegin(GL_QUADS);
        glVertex2f(barraX2, barraBaseY);
        glVertex2f(barraX2 + barraAncho, barraBaseY);
        glVertex2f(barraX2 + barraAncho, barraBaseY + barraAlto);
        glVertex2f(barraX2, barraBaseY + barraAlto);
        glEnd();


        // Relleno J2
        float altoRelleno2 = (potenciaJ2 / 10.0f) * barraAlto;
        glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f); //bueno esto es lo del verde tmb
        glVertex2f(barraX2, barraBaseY);
        glVertex2f(barraX2 + barraAncho, barraBaseY);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(barraX2 + barraAncho, barraBaseY + altoRelleno2);
        glVertex2f(barraX2, barraBaseY + altoRelleno2);
        glEnd();

        glEnable(GL_DEPTH_TEST);


        // VAMOS A PINTAR LAS ESTELAS DE APUNTAR POR AQUÍ


        // ESTO ES EL PUNTERO DE J1
        float cx1 = posXj1;
        float baseY = posYj1;
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

        // A VER ESTO ES EL PUNTERO DE J2
        float cx2 = posXj2;
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


        // vamos a dibujar un marcador bien chulo por aquí jujujuju


        // A VER EL MARACDOR SE VE BIEN MAL PONEMOS POR AQUÍ UN FONDO PARA QUE SE VEA MEJOR

        // estas lineas se supone que hay que ponerlas para que se pinte por debajo el fondo 
        glDisable(GL_DEPTH_TEST); // por aquí anda la clave del éxito
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // MARCADOR J1
        // Fondo oscuro
        glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(-14.0f, 9.0f);
        glVertex2f(-10.0f, 9.0f);
        glVertex2f(-10.0f, 10.5f);
        glVertex2f(-14.0f, 10.5f);

        glEnd();

        // Texto
        glColor3ub(50, 150, 255); //azul
        glRasterPos2f(-13.5f, 9.5f);
        std::string txtJ1 = "J1: " + std::to_string(bolosDerribadosJ1) + " / 6";
        for (char c : txtJ1)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);


        // MARCADOR J2
        // Fondo oscuro
        glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(10.0f, 9.0f);
        glVertex2f(14.0f, 9.0f);
        glVertex2f(14.0f, 10.5f);
        glVertex2f(10.0f, 10.5f);

        glEnd();

        // Texto
        glColor3ub(255, 100, 180); //rosa
        glRasterPos2f(10.5f, 9.5f);
        std::string txtJ2 = "J2: " + std::to_string(bolosDerribadosJ2) + " / 6";
        for (char c : txtJ2)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);


        // ponemos todo normal de nuevo
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

    }

    /// PANTALLA FIN DE JUEGO
    if (estado == FIN) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);

        // RECUADRO NEGRO TRANSLÚCIDO
        glColor4ub(0, 0, 0, 230);
        glBegin(GL_QUADS);
        glVertex2f(-10.0f, -4.0f);
        glVertex2f(10.0f, -4.0f);
        glVertex2f(10.0f, 5.0f);
        glVertex2f(-10.0f, 5.0f);
        glEnd();

        // BORDE  SEGÚN EL GANADOR 
        glLineWidth(3.0f);
        if (ganador == 1) {
            glColor3ub(50, 150, 255); // borde Azul para Jugador 1
        }
        else {
            glColor3ub(255, 100, 180); // borde Rosa para Jugador 2
        }

        glBegin(GL_LINE_LOOP);
        glVertex2f(-10.0f, -4.0f);
        glVertex2f(10.0f, -4.0f);
        glVertex2f(10.0f, 5.0f);
        glVertex2f(-10.0f, 5.0f);
        glEnd();
        glDisable(GL_BLEND);


        ETSIDI::setFont("fuentes/Bitwise.ttf", 22);
        ETSIDI::setTextColor(1.0f, 1.0f, 1.0f); //blanco
        ETSIDI::printxy("FIN DE PARTIDA", -5.0f, 2.5f);

        //  GANADOR CON SU COLOR ASIGNADO
        ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
        if (ganador == 1) {
            ETSIDI::setTextColor(0.2f, 0.6f, 1.0f); // azul
            ETSIDI::printxy("GANADOR: JUGADOR 1", -5.2f, 0.8f);
        }
        else if (ganador == 2) {
            ETSIDI::setTextColor(1.0f, 0.4f, 0.7f); // rosa
            ETSIDI::printxy("GANADOR: JUGADOR 2", -5.2f, 0.8f);
        }

        //  SALIDA 
        ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
        ETSIDI::setTextColor(1.0f, 0.0f, 0.0f); //rojo
        ETSIDI::printxy("Pulsa C para volver al tablero", -6.0f, -2.0f);
    }

    glEnable(GL_LIGHTING);

}

void CombateBolos::crearBolos() {

    bolos.clear();

    float cx1 = -5.0f;
    float cx2 = 5.0f;
    float cy = -1.0f;
    float sepX = 1.6f;
    float sepY = 2.4f;

    // CARRIL IZQUIERDO (J1)
    bolos.push_back(Bolo(cx1 - sepX, cy));
    bolos.push_back(Bolo(cx1, cy));
    bolos.push_back(Bolo(cx1 + sepX, cy));
    bolos.push_back(Bolo(cx1 - sepX / 2, cy + sepY));
    bolos.push_back(Bolo(cx1 + sepX / 2, cy + sepY));
    bolos.push_back(Bolo(cx1, cy + sepY * 2));

    // CARRIL DERECHO (J2)
    bolos.push_back(Bolo(cx2 - sepX, cy));
    bolos.push_back(Bolo(cx2, cy));
    bolos.push_back(Bolo(cx2 + sepX, cy));
    bolos.push_back(Bolo(cx2 - sepX / 2, cy + sepY));
    bolos.push_back(Bolo(cx2 + sepX / 2, cy + sepY));
    bolos.push_back(Bolo(cx2, cy + sepY * 2));

}

