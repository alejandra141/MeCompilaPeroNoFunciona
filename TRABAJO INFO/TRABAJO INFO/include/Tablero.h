#pragma once
#include "Cuadrado.h"
#include "ETSIDI.h"
#include "Personaje.h"  
#include "Jugador.h"    

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


    Personaje* casillas[9][9];  // punteros a los personajes en el tablero (es para colocar los personajes)


public:
    void dibuja() const;



//lo siguiente es para inicializar los personajes
    Tablero();
 
    void colocar(Personaje* p, int fila, int col);
    void eliminarPersonaje(Personaje* p);
    void inicializarJ1(Jugador& j1);
    void inicializarJ2(Jugador& j2);
    Personaje* getEn(int f, int c) const;
    Linea centroCasilla(int fila, int col) const;


};
