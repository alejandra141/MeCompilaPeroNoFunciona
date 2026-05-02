#include "freeglut.h"
#include "Linea.h"
#include "Cuadrado.h"
#include "Tablero.h"

void Tablero::dibuja() const {
	borde.dibuja(); 
	tablero.dibuja();
	casilla1.dibuja(); 
	casilla2.dibuja(); 
	casilla3.dibuja(); 
	casilla4.dibuja();
	casilla5.dibuja(); 
	casilla6.dibuja(); 
	casilla7.dibuja();

	casilla8.dibuja(); 
	casilla9.dibuja(); 
	casilla10.dibuja(); 
}
