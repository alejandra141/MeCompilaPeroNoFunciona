#include "freeglut.h"
#include "Cuadrado.h"
#include "Color.h"


Cuadrado::Cuadrado(const Linea& Punto1, const Linea& Punto2, const Color c) {
	p1 = Punto1;
	p2 = Punto2;
	color = c; 
}
void Cuadrado::setcolor (const Color& c) {
	color = c; 
}
void Cuadrado::dibuja() const {
	glColor3ub(color.r, color.v, color.a); 
	glBegin(GL_POLYGON);
	glVertex3f(p1.x, p1.y, p1.z); 
	glVertex3f(p2.x, p1.y, p1.z); 
	glVertex3f(p2.x, p1.y, p2.z);
	glVertex3f(p1.x, p1.y, p2.z);
	glEnd();
}


