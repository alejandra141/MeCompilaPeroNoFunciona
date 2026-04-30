#pragma once
#include "Cuadrado.h"

class Tablero {
private: 
	Cuadrado tablero{ { -5,0,-5 }, {5,0,5}, {135,206,235} }; 

public: 
	void dibuja() const;
};
