#pragma once
#include "Vector2D.h"

class Bolo
{
private:

	vector2D p1;
	vector2D p2;
	vector2D posicion;

	bool derribado{};

	float anchoMitad{ 0.8f };
	float alto{ 2.5f };

public:

	Bolo(float x, float y)
		: posicion(x, y), derribado(false)
	{
		p1 = { posicion.x - anchoMitad, posicion.y };
		p2 = { posicion.x + anchoMitad, posicion.y + alto };

	}

	// Getters
	vector2D getP1() const { return p1; }
	vector2D getP2() const { return p2; }
	vector2D getPosicion() const { return posicion; }
    bool isDerribado() const { return derribado; }

	// Setters
	void setP1(vector2D newP1) { p1 = newP1; }
	void setP2(vector2D newP2) { p2 = newP2; }
	void setDerribado(bool newDerribado) { derribado = newDerribado; }

	//Métodos
	void derribar() { derribado = true; }

	void dibuja();

};

