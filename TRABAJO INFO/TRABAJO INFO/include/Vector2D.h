
#pragma once
struct vector2D
{
	double x{};
	double y{};
	double modulo() const; //modulo del vector
	double argumento() const; //argumento del vector
	vector2D unitario() const; //devuelve un vector unitario
	vector2D operator - (const vector2D&) const; //resta de vectores
	vector2D operator + (const vector2D&) const;
	double operator *(const vector2D&) const; // producto escalar
	vector2D operator *(double) const; // producto por un escalar


};
