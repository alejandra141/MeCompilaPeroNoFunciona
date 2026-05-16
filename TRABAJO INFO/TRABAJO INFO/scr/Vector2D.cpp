#include "Vector2D.h"
#include <cmath>

double vector2D::modulo() const
{
	return sqrt(x * x + y * y);
}

double vector2D::argumento() const {
	return atan2(y, x);
}

vector2D vector2D::unitario() const
{
	auto mod = modulo();
	if (mod > 0.00001) return { x / mod, y / mod };
	return { x,y };
}

vector2D vector2D::operator - (const vector2D& v) const
{
	return { x - v.x , y - v.y };
}
vector2D vector2D::operator+(const vector2D& v) const {
	return { x + v.x, y + v.y };
}


//  por un escalar
vector2D vector2D::operator*(double k) const {
	return { x * k, y * k };
}

// producto escalar 
double vector2D::operator*(const vector2D& v) const {
	return x * v.x + y * v.y;
}