#pragma once
#include "Cuadrado.h"

class Tablero {
private:
    // Fondo y tablero
    Cuadrado fondo{ {-5, -5}, {5, 5}, {135,206,235} };
    Cuadrado tablero_{ {-4.6f, -4.6f}, {4.6f, 4.6f}, {34,139,34} };
    Cuadrado borde{ {-5, -5}, {5, 5}, {0,0,0} };

    // Fila 1
    Cuadrado casilla1{ {-4.6f, -3.55f}, {-3.55f, -2.55f}, {0,0,0} };
    Cuadrado casilla2{ {-3.55f, -3.55f}, {-2.55f, -2.55f}, {255,255,255} };
    Cuadrado casilla3{ {-2.55f, -3.55f}, {-1.55f, -2.55f}, {0,0,0} };
    
  

    // Fila 2
    Cuadrado casilla8{ {-4.6f, -2.55f}, {-3.55f, -1.55f}, {255,255,255} };
    Cuadrado casilla9{ {-3.55f, -2.55f}, {-2.55f, -1.55f}, {0,0,0} };
    Cuadrado casilla10{ {-2.55f, -2.55f}, {-1.55f, -1.55f}, {255,255,255} };

public:
    void dibuja() const;
};
