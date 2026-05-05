#pragma once
#include <GL/freeglut.h>


using unchar = unsigned char;

struct Color { 
	unchar r; 
	unchar v; 
	unchar a;

void color() const {
	glColor3ub(r, v, a); 
}
};