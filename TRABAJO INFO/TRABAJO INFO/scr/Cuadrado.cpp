#include <GL/freeglut.h>
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
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p1.x, p2.y);
    glEnd();
}



