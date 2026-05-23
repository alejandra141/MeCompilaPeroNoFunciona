#pragma once
#include "Cuadrado.h"
#include "ETSIDI.h"

class Tablero {
private:
 
    Cuadrado fondo{ {-10, -10, 0}, {10, 10, 0}, {135,206,235} };          // azul cielo
    Cuadrado tablero_{ {-9, -9, 0.1}, {9, 9, 0.1}, {34,139,34} }; // verde

    // CASILLAS (3x3)
    Cuadrado c1{ {-1, -1}, {1, 1}, {255,255,255} };

    Cuadrado c2{ {-1.5,  1.5}, { 1.5, 4.5}, {255,255,255} };
    Cuadrado c3{ { 1.5,  1.5}, { 4.5, 4.5}, {255,255,255} };

    Cuadrado c4{ {-4.5, -1.5}, {-1.5, 1.5}, {255,255,255} };
    Cuadrado c5{ {-1.5, -1.5}, { 1.5, 1.5}, {255,255,255} };
    Cuadrado c6{ { 1.5, -1.5}, { 4.5, 1.5}, {255,255,255} };

    Cuadrado c7{ {-4.5, -4.5}, {-1.5,-1.5}, {255,255,255} };
    Cuadrado c8{ {-1.5, -4.5}, { 1.5,-1.5}, {255,255,255} };
    Cuadrado c9{ { 1.5, -4.5}, { 4.5,-1.5}, {255,255,255} };
   


public:
	void cargarTexturasTablero();
    void dibuja() const;
};
