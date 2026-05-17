#include "Cuadrado.h"
#include <GL/freeglut.h>
#include <stdio.h>  

void Cuadrado::dibuja() const {
    

    glColor3ub(color.r, color.v, color.a);

    glBegin(GL_POLYGON);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p1.x, p2.y);
    glEnd();
}

