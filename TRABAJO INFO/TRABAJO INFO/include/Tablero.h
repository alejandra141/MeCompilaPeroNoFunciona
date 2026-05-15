#pragma once
#include "Cuadrado.h"
#include "Personaje.h"

class Tablero {
private:

    // Fondo y tablero
    Cuadrado fondo{ {-5, -5, 0}, {5, 5, 0}, {135,206,235} };
    Cuadrado tablero_{ {-4.6f, -4.6f, 0}, {4.6f, 4.6f, 0}, {34,139,34} };
    Cuadrado borde{ {-5, -5, 0}, {5, 5, 0}, {50,105,50} };

    // Fila 1
    Cuadrado casilla1{ {-4.6f, -3.55f, 0}, {-3.5f, -3.55f, 0}, {0,0,0} };
    Cuadrado casilla2{ {-3.5f, -3.55f, 0}, {-2.5f, -3.55f, 0}, {255,255,255} };
    Cuadrado casilla3{ {-2.5f, -3.55f, 0}, {-1.5f, -3.55f, 0}, {0,0,0} };
    Cuadrado casilla4{ {-1.5f, -3.55f, 0}, {-0.5f, -3.55f, 0}, {255,255,255} };
    Cuadrado casilla5{ {-0.5f, -3.55f, 0}, {0.5f, -3.55f, 0}, {0,0,0} };
    Cuadrado casilla6{ {0.5f, -3.55f, 0}, {1.5f, -3.55f, 0}, {255,255,255} };
    Cuadrado casilla7{ {1.5f, -3.55f, 0}, {2.5f, -3.55f, 0}, {0,0,0} };

    // Fila 2 (corregida igual)
    Cuadrado casilla8{ {-4.6f, -2.55f, 0}, {-3.5f, -2.55f, 0}, {255,255,255} };
    Cuadrado casilla9{ {-3.5f, -2.55f, 0}, {-2.5f, -2.55f, 0}, {0,0,0} };
    Cuadrado casilla10{ {-2.5f, -2.55f, 0}, {-1.5f, -2.55f, 0}, {255,255,255} };

    Personaje jugador1;

public:
    void dibuja() const;
};
