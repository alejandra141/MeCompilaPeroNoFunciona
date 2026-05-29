


//CombateBolos.cpp

#include "CombateBolos.h"
#include "GL/freeglut.h"
#include "ETSIDI.h"
#include <iostream>
#include "bolo.h"
#include <string>


CombateBolos::CombateBolos(Personaje* j1, Personaje* j2)
    : jugador1(j1), jugador2(j2),
    bolosDerribadosJ1(0), bolosDerribadosJ2(0),
    anguloJ1(0), dirJ1(1), anguloJ2(0), dirJ2(1),
    potenciaJ1(0), potenciaJ2(0),
    cargandoJ1(false), cargandoJ2(false),
    lanzandoJ1(false), lanzandoJ2(false),
    tiempoFinJuego(0), estado(JUGANDO), ganador(0)
{
    // si son especialistas en bolos tienen ventaja en la estela de apuntado
    if (jugador1 != nullptr) {
        std::string t1 = jugador1->getTipo();
        j1esEspecialista = (t1 == "bolo_cranker" || t1 == "bolo_stroker");
    }
    if (jugador2 != nullptr) {
        std::string t2 = jugador2->getTipo();
        j2esEspecialista = (t2 == "bolo_cranker" || t2 == "bolo_stroker");
    }

    crearBolos();
}

void CombateBolos::comprobarColisiones() {

    // estas son las colisiones de los bolos del J1, que son los bolos 0-5
    if (bolaJ1.activa) {
        for (int i = 0; i < 6; i++) {
            if (!bolos[i].isDerribado()) {
                float dx = bolaJ1.posicion.x - bolos[i].getPosicion().x;
                float dy = bolaJ1.posicion.y - bolos[i].getPosicion().y;
                if (sqrt(dx * dx + dy * dy) < 1.5f) {
                    bolos[i].derribar();
                    bolosDerribadosJ1++;
                    tiempoEfectoJ1 = 1.5f;
                }
            }
        }
        if (bolaJ1.posicion.y > 8.0f)
            bolaJ1.resetear();
    }

    // estas son las colisiones de los bolos del J2, que son los bolos 6-11
    if (bolaJ2.activa) {
        for (int i = 6; i < 12; i++) {
            if (!bolos[i].isDerribado()) {
                float dx = bolaJ2.posicion.x - bolos[i].getPosicion().x;
                float dy = bolaJ2.posicion.y - bolos[i].getPosicion().y;
                if (sqrt(dx * dx + dy * dy) < 1.5f) {
                    bolos[i].derribar();
                    bolosDerribadosJ2++;
                    tiempoEfectoJ2 = 1.5f;
                }
            }
        }
        if (bolaJ2.posicion.y > 8.0f)
            bolaJ2.resetear();
    }

    // Bajar temporizadores
    // (esto se hace en mueve con el dt)


    if (bolosDerribadosJ1 >= 6 && estado == JUGANDO) {
        estado = FIN;
        ganador = 1;
    }

    if (bolosDerribadosJ2 >= 6 && estado == JUGANDO) {
        estado = FIN;
        ganador = 2;
    }
}


void CombateBolos::mueve(double dt) {


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

    // si salen de pantalla reseteamos
   // if (bolaJ1.activa && bolaJ1.posicion.y > 10.0f)
   //     bolaJ1.resetear();
    //if (bolaJ2.activa && bolaJ2.posicion.y > 10.0f)
    //    bolaJ2.resetear();

    comprobarColisiones();
    if (tiempoEfectoJ1 > 0) tiempoEfectoJ1 -= (float)dt;
    if (tiempoEfectoJ2 > 0) tiempoEfectoJ2 -= (float)dt;




}


void CombateBolos::tecla(unsigned char key) {

    //tenemos que poner que la potencia se cargue solo si la bola no está activa
    if (key == 'w' && !bolaJ1.activa) cargandoJ1 = true;
    if (key == 'i' && !bolaJ2.activa) cargandoJ2 = true;

}

//he creado esta clase para que se pueda cargar la potencia bien cuando sueltas la tecla
void CombateBolos::teclaSuelta(unsigned char key) {

    if (key == 'w' && !bolaJ1.activa) {
        cargandoJ1 = false;

        if (potenciaJ1 > 0) {  //hay que poner esto para solo lanzar si hay potencia en la barra
            float velX = sin(anguloJ1) * potenciaJ1 * 1.5f;
            float velY = potenciaJ1 * 3.0f;
            bolaJ1.lanzar(-5.0f, -9.0f, velX, velY);
            ETSIDI::play("sonidos/Bowling/Sample_0009.wav");
        }
        potenciaJ1 = 0; // reseteamos la potencia para que no se quede cargada después de lanzar

    }


    if (key == 'i' && !bolaJ2.activa) {
        cargandoJ2 = false;

        if (potenciaJ2 > 0) {  //hay que poner esto para solo lanzar si hay potencia en la barra
            float velX = sin(anguloJ2) * potenciaJ2 * 1.5f;
            float velY = potenciaJ2 * 3.0f;
            bolaJ2.lanzar(5.0f, -9.0f, velX, velY);
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


    // RENDERIZADO DE LOS SPRITES PNG REALES EN LA BOLERA

    float baseY_Personajes = -7.5f;

    // DIBUJA SPRITE JUGADOR 1 (izquierda)

    if (jugador1 != nullptr) {
        glPushMatrix();
        // (X = -5.0) izquierda
        glTranslatef(-5.0f, baseY_Personajes, 0.0f);
        glScalef(0.7f, 0.7f, 1.0f);

        jugador1->getSprite().setPosicion(0.0f, 0.0f);

        // llamamos a su método que ya sabe activar el Blend, la textura y recortar el fondo
        jugador1->dibuja();
        glPopMatrix();
    }

    // DIBUJA SPRITE JUGADOR 2 (derecha)

    if (jugador2 != nullptr) {
        glPushMatrix();
        // (X = 5.0) derecha
        glTranslatef(5.0f, baseY_Personajes, 0.0f);
        glScalef(0.7f, 0.7f, 1.0f);

        jugador2->getSprite().setPosicion(0.0f, 0.0f);

        jugador2->dibuja();
        glPopMatrix();
    }


    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //AQUI VAMOS A PINTAR LAS BARRITAS DE POTENCIA, QUE SE VAYAN LLENANDO SEGÚN LA POTENCIA QUE SE VAYA CARGANDO

    glDisable(GL_DEPTH_TEST);
    glColor3f(0.3f, 0.3f, 0.3f);

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

    glEnable(GL_DEPTH_TEST);   // ← reactiva al final


    // VAMOS A PINTAR LAS ESTELAS DE APUNTAR POR AQUÍ


       // ESTO ES EL PUNTERO DE J1
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

    // A VER ESTO ES EL PUNTERO DE J2
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
    glVertex2f(-14.0f, 4.0f);
    glVertex2f(-8.0f, 4.0f);
    glVertex2f(-8.0f, 6.5f);
    glVertex2f(-14.0f, 6.5f);
    glEnd();

    // Texto
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2f(-13.5f, 5.0f);
    std::string txtJ1 = "J1: " + std::to_string(bolosDerribadosJ1) + " / 6";
    for (char c : txtJ1)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);


    // MARCADOR J2
    // Fondo oscuro
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(8.0f, 4.0f);
    glVertex2f(14.0f, 4.0f);
    glVertex2f(14.0f, 6.5f);
    glVertex2f(8.0f, 6.5f);
    glEnd();

    // Texto
    glColor3f(0.0f, 1.0f, 1.0f);
    glRasterPos2f(8.5f, 5.0f);
    std::string txtJ2 = "J2: " + std::to_string(bolosDerribadosJ2) + " / 6";
    for (char c : txtJ2)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);


    // ponemos todo normal de nuevo
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);



    // vamos a poner 

    //SOY LORENA ESTO ES PARA QUE ANUNCIA EL GANADOR Y PULSANDO C VUELVES AL TABLERO 
    if (estado == FIN) {

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        ETSIDI::setTextColor(1, 1, 0);

        if (ganador == 1)
            ETSIDI::printxy("GANADOR: JUGADOR 1", -7, 5);
        else if (ganador == 2)
            ETSIDI::printxy("GANADOR: JUGADOR 2", -7, 5);

        ETSIDI::setTextColor(1, 0, 0);
        ETSIDI::printxy("Pulsa C para volver", -7, 3);
    }

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






