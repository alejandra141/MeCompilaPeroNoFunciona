#include "Tablero.h"
#include <iostream> 
#include "ETSIDI.h"


Tablero tablero;

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

            int valorCelda = celdas[fila][col];

            // ESTO ES PARA INVERTIR LOS COLORES DE LAS CELDAS
            if (cicloInvertido) {
                if (valorCelda == 0) valorCelda = 1;
                else if (valorCelda == 1) valorCelda = 0;
            }

            Color colorActual;
            switch (valorCelda) {
            case 0: colorActual = NEGRO; break;
            case 1: colorActual = BLANCO; break;
            case 2: colorActual = MORADO; break;
            case 3: colorActual = PODER; break;
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

    if (p == nullptr) return;
    Linea c = centroCasilla(fila, col);
    p->setPosicion(c);
    p->setCasilla(fila, col);
    casillas[fila][col] = p;

}


//  Eliminar personaje del tablero (al morir) 
void Tablero::eliminarPersonaje(Personaje* p) {
    //casillas[p->getFila()][p->getColumna()] = nullptr;

    //NUEVO MODO
    if (p == nullptr) return;

    int f = p->getFila();
    int c = p->getColumna();

    //  límites tablero
    if (f >= 0 && f < 9 && c >= 0 && c < 9) {
        casillas[f][c] = nullptr;
    }

}


//  Posiciones iniciales Jugador 1 (fila 8 = arriba) 
void Tablero::inicializarJ1(Jugador& j1) {
    auto& p = j1.getPiezas();

    colocar(p[0], 0, 8);   // A8 : ahora 8A
    colocar(p[1], 6, 8);   // G8 : ahora 8G
    colocar(p[2], 8, 8);   // I8 : ahora 8I

    colocar(p[3], 0, 7);   // A7 : ahora 7A
    colocar(p[4], 2, 8);   // C8 : ahora 8C
    colocar(p[5], 8, 7);   // I7 : ahora 7I

    colocar(p[6], 3, 8);   // D8 : ahora 8D
    colocar(p[7], 5, 8);   // F8 : ahora 8F
    colocar(p[8], 4, 8);   // E8 : ahora 8E

    colocar(p[9], 1, 7);   // B7 : ahora 7B
    colocar(p[10], 2, 7);  // C7 : ahora 7C
    colocar(p[11], 3, 7);  // D7 : ahora 7D
    colocar(p[12], 4, 7);  // E7 : ahora 7E
    colocar(p[13], 5, 7);  // F7 : ahora 7F
    colocar(p[14], 6, 7);  // G7 : ahora 7G
    colocar(p[15], 7, 7);  // H7 : ahora 7H

    colocar(p[16], 1, 8);  // B8 : ahora 8B
    colocar(p[17], 7, 8);  // H8 : ahora 8H
}

//  Posiciones iniciales Jugador 1 (espejo, fila 0 = abajo) 
void Tablero::inicializarJ2(Jugador& j2) {
    auto& p = j2.getPiezas();

    colocar(p[0], 0, 0);   // A1 : ahora 1A
    colocar(p[1], 6, 0);   // G1 : ahora 1G
    colocar(p[2], 8, 0);   // I1 : ahora 1I

    colocar(p[3], 0, 1);   // A2 : ahora 2A
    colocar(p[4], 2, 0);   // C1 : ahora 1C
    colocar(p[5], 8, 1);   // I2 : ahora 2I

    colocar(p[6], 3, 0);   // D1 : ahora 1D
    colocar(p[7], 5, 0);   // F1 : ahora 1F
    colocar(p[8], 4, 0);   // E1 : ahora 1E

    colocar(p[9], 1, 1);   // B2 : ahora 2B
    colocar(p[10], 2, 1);  // C2 : ahora 2C
    colocar(p[11], 3, 1);  // D2 : ahora 2D
    colocar(p[12], 4, 1);  // E2 : ahora 2E
    colocar(p[13], 5, 1);  // F2 : ahora 2F
    colocar(p[14], 6, 1);  // G2 : ahora 2G
    colocar(p[15], 7, 1);  // H2 : ahora 2H

    colocar(p[16], 1, 0);  // B1 : ahora 1B
    colocar(p[17], 7, 0);  // H1 : ahora 1H
}


// devuelve true si la casilla contiene un personaje, false si está vacía
bool Tablero::hayPiezaEn(int fila, int col) const {
    // límites de la matriz (0-8)
    if (fila < 0 || fila >= 9 || col < 0 || col >= 9) return false;

    return (casillas[fila][col] != nullptr);
}

// devuelve el número de jugador (1 o 2) dueño de la pieza, o 0 si está vacía
int Tablero::getBandoPiezaEn(int fila, int col) const {
    if (fila < 0 || fila >= 9 || col < 0 || col >= 9) return 0;

    if (casillas[fila][col] != nullptr) {
        return casillas[fila][col]->getNumJugador();
    }
    return 0; // casilla vacía
}

Personaje* Tablero::getPersonajeEn(int fila, int col) const {
    if (fila < 0 || fila >= 9 || col < 0 || col >= 9) return nullptr;
    return casillas[fila][col];
}

//Acciones de victoria
//Piezas en las cinco posicones de poder 
bool Tablero::controlaCincoPuntos(Jugador& j) const {
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            if (getCelda(i, k) == 3) {      // mira a ver si hay pieza
                Personaje* p = getCasilla(i, k); // de quien es la pieza
                if (p == nullptr) return false;//no hay nadie
                if (!j.tienePieza(p)) return false;//es del rival
            }
        }
    }
    return true;
}

//la segunda condicion es que se quede sin piezas, ya en Jugador.h: sinPiezas()

//solo una pieza encarcelada
bool Tablero::rivalConUnaPiezaEncarcelada(Jugador& rival) {
    const auto& piezas = rival.getPiezas();
    int encarceladas = 0;
    for (const Personaje* p : piezas) {
        if (p->estaEncarcelada()) encarceladas++;
    }
    // Solo tiene 1 pieza y está encarcelada
    return (piezas.size() == 1 && encarceladas == 1);
}

// Ver quien ganó
Jugador* Tablero::verificarGanador(Tablero& t, Jugador& j1, Jugador& j2) {
    // Revisamos j1
    if (t.controlaCincoPuntos(j1) ||
        j2.sinPiezas() ||
        rivalConUnaPiezaEncarcelada(j2))
        return &j1;

    // Revisamos j2
    if (t.controlaCincoPuntos(j2) ||
        j1.sinPiezas() ||
        rivalConUnaPiezaEncarcelada(j1))
        return &j2;

    return nullptr; // Nadie ganó aún
}