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
    glDisable(GL_DEPTH_TEST);
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
    glEnable(GL_DEPTH_TEST);    

}
	

//LO SIGUIENTE ES PARA LA INICIALIZACION DE LOS PERSONAJES
// Constructor
Tablero::Tablero() {
    for (int f = 0; f < 9; f++)
        for (int c = 0; c < 9; c++)
            casillas[f][c] = nullptr;
}

Linea Tablero::centroCasilla(int fila, int col) const {
    Linea c;
    c.x = -9 + col * 2 + 1;   // centro X
    c.y = -9 + fila * 2 + 1;  // centro Y
    c.z = 0.3f;               // profundidad para que se vea sobre el tablero
    return c;
}


//  Colocar un personaje en una casilla 
void Tablero::colocar(Personaje* p, int fila, int col) {
    Linea c = centroCasilla(fila, col);
    p->setPosicion(c);   // si tu personaje acepta Linea
    casillas[fila][col] = p;
}


//  Eliminar personaje del tablero (al morir) 
void Tablero::eliminarPersonaje(Personaje* p) {
    casillas[p->getFila()][p->getColumna()] = nullptr;
}


//  Posiciones iniciales Jugador 1 (fila 8 = arriba) 
void Tablero::inicializarJ1(Jugador& j1) {
    auto& p = j1.getPiezas();

    colocar(p[0], 0, 8);   // A8 → ahora 8A
    colocar(p[1], 6, 8);   // G8 → ahora 8G
    colocar(p[2], 8, 8);   // I8 → ahora 8I

    colocar(p[3], 0, 7);   // A7 → ahora 7A
    colocar(p[4], 2, 8);   // C8 → ahora 8C
    colocar(p[5], 8, 7);   // I7 → ahora 7I

    colocar(p[6], 3, 8);   // D8 → ahora 8D
    colocar(p[7], 5, 8);   // F8 → ahora 8F
    colocar(p[8], 4, 8);   // E8 → ahora 8E

    colocar(p[9], 1, 7);   // B7 → ahora 7B
    colocar(p[10], 2, 7);  // C7 → ahora 7C
    colocar(p[11], 3, 7);  // D7 → ahora 7D
    colocar(p[12], 4, 7);  // E7 → ahora 7E
    colocar(p[13], 5, 7);  // F7 → ahora 7F
    colocar(p[14], 6, 7);  // G7 → ahora 7G
    colocar(p[15], 7, 7);  // H7 → ahora 7H

    colocar(p[16], 1, 8);  // B8 → ahora 8B
    colocar(p[17], 7, 8);  // H8 → ahora 8H
}

//  Posiciones iniciales Jugador 1 (espejo, fila 0 = abajo) 
void Tablero::inicializarJ2(Jugador& j2) {
    auto& p = j2.getPiezas();

    colocar(p[0], 0, 0);   // A1 → ahora 1A
    colocar(p[1], 6, 0);   // G1 → ahora 1G
    colocar(p[2], 8, 0);   // I1 → ahora 1I

    colocar(p[3], 0, 1);   // A2 → ahora 2A
    colocar(p[4], 2, 0);   // C1 → ahora 1C
    colocar(p[5], 8, 1);   // I2 → ahora 2I

    colocar(p[6], 3, 0);   // D1 → ahora 1D
    colocar(p[7], 5, 0);   // F1 → ahora 1F
    colocar(p[8], 4, 0);   // E1 → ahora 1E

    colocar(p[9], 1, 1);   // B2 → ahora 2B
    colocar(p[10], 2, 1);  // C2 → ahora 2C
    colocar(p[11], 3, 1);  // D2 → ahora 2D
    colocar(p[12], 4, 1);  // E2 → ahora 2E
    colocar(p[13], 5, 1);  // F2 → ahora 2F
    colocar(p[14], 6, 1);  // G2 → ahora 2G
    colocar(p[15], 7, 1);  // H2 → ahora 2H

    colocar(p[16], 1, 0);  // B1 → ahora 1B
    colocar(p[17], 7, 0);  // H1 → ahora 1H
}
