#include "CombateBolos.h"
#include "GL/freeglut.h"
#include "ETSIDI.h"
#include <iostream>
#include "bolo.h"

CombateBolos::CombateBolos() : bolosDerribadosJ1(0), bolosDerribadosJ2(0), //esto es para hacer pruebas
j1esEspecialista(false), j2esEspecialista(true), anguloJ1(0), dirJ1(1), anguloJ2(0), dirJ2(1), potenciaJ1(0), potenciaJ2(0),
cargandoJ1(false), cargandoJ2(false), lanzandoJ1(false), lanzandoJ2(false) {
    crearBolos();
}


void CombateBolos::mueve(double dt) {
    

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


	// SON PRUEBAS HAY QUE BORRARLAS EN UN FUTURO PERO AHORA MIS OJOS NO PUEDEN MÁS JAJAJAJA
    // if (cargandoJ1) {
    //     std::cout << "potenciaJ1: " << potenciaJ1 << std::endl;
    //}

}


void CombateBolos::tecla(unsigned char key) {

	//ESTAS TECLAS SON PARA QUE MIENTRAS SE MANTENGA PULSADA SE VAYA CARGANDO LA POTENCIA, Y CUANDO SE SUELTE SE DISPARA    
     if (key == 'w') cargandoJ1 = true; 
     if (key == 'i') cargandoJ2 = true; 
    
}

//he creado esta clase para que se pueda cargar la potencia bien cuando sueltas la tecla
void CombateBolos::teclaSuelta(unsigned char key) {

    if (key == 'w') {
        cargandoJ1 = false;
        lanzandoJ1 = true;
        potenciaJ1 = 0; // para resetear por que no consigo que vaya
    }

    if (key == 'i') {
        cargandoJ2 = false;
        lanzandoJ2 = true;
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


    //AQUI VAMOS A PINTAR LAS BARRITAS DE POTENCIA, QUE SE VAYAN LLENANDO SEGÚN LA POTENCIA QUE SE VAYA CARGANDO

    glDisable(GL_DEPTH_TEST);  // ← añade esto
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
