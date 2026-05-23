#pragma once
#include "Cuadrado.h"
#include "ETSIDI.h"

class Tablero {
private:
    Cuadrado fondo{ {-10, -10, 0}, {10, 10, 0}, {135,206,235} };
    Cuadrado tablero_{ {-9, -9, 0.1}, {9, 9, 0.1}, {34,139,34} };

    const Color NEGRO = { 0, 0, 0 };
    const Color BLANCO = { 255, 255, 255 };
    const Color MORADO = { 128, 0, 128 };

    int celdas[9][9] = {
        {0, 1, 0, 2, 2, 2, 1, 0, 1},
        {1, 0, 2, 1, 2, 0, 2, 1, 0},
        {0, 2, 1, 0, 2, 1, 0, 2, 1},
        {2, 1, 0, 1, 2, 0, 1, 0, 2},
        {1, 2, 2, 2, 2, 2, 2, 2, 0},
        {2, 1, 0, 1, 2, 0, 1, 0, 2},
        {0, 2, 1, 0, 2, 1, 0, 2, 1},
        {1, 0, 2, 1, 2, 0, 2, 1, 0},
        {0, 1, 0, 2, 2, 2, 1, 0, 1}
    };

public:
    void dibuja() const;
};
