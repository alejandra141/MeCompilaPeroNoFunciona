#pragma once
#include "Color.h"
#include "Linea.h"

class Cuadrado {
private: 
	Linea p1, p2; 
	Color color; 

public: 
	Cuadrado(const Linea& Punto1, const Linea& Punto2, const Color c); 
	void dibuja() const; 
	void setcolor(const Color& c); 
};


