#include "Cuadrado.h"
#include <GL/freeglut.h>
#include <stdio.h>  

void Cuadrado::dibuja() const {
   

    glColor3ub(color.r, color.v, color.a);

    glBegin(GL_POLYGON);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p1.y, p2.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p1.x, p2.y, p1.z);
    glEnd();
  
}

