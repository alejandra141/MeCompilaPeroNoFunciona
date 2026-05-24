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



    // PARA PERSONAJES
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    for (int f = 0; f < 9; f++)
        for (int c = 0; c < 9; c++)
            if (casillas[f][c] != nullptr)
                casillas[f][c]->dibuja();

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

}
	

//LO SIGUIENTE ES PARA LA INICIALIZACION DE LOS PERSONAJES
// Constructor
Tablero::Tablero() {
    for (int f = 0; f < 9; f++)
        for (int c = 0; c < 9; c++)
            casillas[f][c] = nullptr;
}

//  Colocar un personaje en una casilla 
void Tablero::colocar(Personaje* p, int fila, int col) {
    casillas[fila][col] = p;
    p->setPosicion(fila, col);   // calcula su x,y OpenGL internamente
}

//  Eliminar personaje del tablero (al morir) 
void Tablero::eliminarPersonaje(Personaje* p) {
    casillas[p->getFila()][p->getColumna()] = nullptr;
}


//  Posiciones iniciales Jugador 2 (fila 8 = arriba) 
void Tablero::inicializarJ2(Jugador& j2) {
    auto& p = j2.getPiezas();
    colocar(p[0], 8, 0);   // BoloCrancker  A8
    colocar(p[1], 8, 6);   // BoloCrancker  G8
    colocar(p[2], 8, 8);   // BoloCrancker  I8
    colocar(p[3], 7, 0);   // BoloStronker  A7
    colocar(p[4], 8, 2);   // BoloStronker  C8
    colocar(p[5], 7, 8);   // BoloStronker  I7
    colocar(p[6], 8, 3);   // Baloncesto    D8
    colocar(p[7], 8, 5);   // Baloncesto    F8
    colocar(p[8], 8, 4);   // Fisio         E8
    colocar(p[9], 7, 1);   // BoxNormal     B7
    colocar(p[10], 7, 2);   // BoxNormal     C7
    colocar(p[11], 7, 3);   // BoxNormal     D7
    colocar(p[12], 7, 4);   // BoxNormal     E7
    colocar(p[13], 7, 5);   // BoxNormal     F7
    colocar(p[14], 7, 6);   // BoxNormal     G7
    colocar(p[15], 7, 7);   // BoxNormal     H7
    colocar(p[16], 8, 1);   // BoxKick       B8
    colocar(p[17], 8, 7);   // BoxKick       H8
}

//  Posiciones iniciales Jugador 1 (espejo, fila 0 = abajo) 
void Tablero::inicializarJ1(Jugador& j1) {
    auto& p = j1.getPiezas();
    colocar(p[0], 0, 0);   // BoloCrancker  A1
    colocar(p[1], 0, 6);   // BoloCrancker  G1
    colocar(p[2], 0, 8);   // BoloCrancker  I1
    colocar(p[3], 1, 0);   // BoloStronker  A2
    colocar(p[4], 0, 2);   // BoloStronker  C1
    colocar(p[5], 1, 8);   // BoloStronker  I2
    colocar(p[6], 0, 3);   // Baloncesto    D1
    colocar(p[7], 0, 5);   // Baloncesto    F1
    colocar(p[8], 0, 4);   // Fisio         E1
    colocar(p[9], 1, 1);   // BoxNormal     B2
    colocar(p[10], 1, 2);   // BoxNormal     C2
    colocar(p[11], 1, 3);   // BoxNormal     D2
    colocar(p[12], 1, 4);   // BoxNormal     E2
    colocar(p[13], 1, 5);   // BoxNormal     F2
    colocar(p[14], 1, 6);   // BoxNormal     G2
    colocar(p[15], 1, 7);   // BoxNormal     H2
    colocar(p[16], 0, 1);   // BoxKick       B1
    colocar(p[17], 0, 7);   // BoxKick       H1
}