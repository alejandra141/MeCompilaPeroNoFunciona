#include "GL/freeglut.h"
#include "math.h"
#include "Tablero.h"
#include <iostream>
#include "Turnos.h"

using std::cout;
using std::endl;

#define MOUSE_LEFT_BUTTON 0
#define MOUSE_RIGHT_BUTTON 1

Tablero tablero;
Turnos turno;

// DECLARACIÓN DE CALLBACKS
void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("MiJuego");

    // DESACTIVAR TODO LO 3D
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);

   

    // CALLBACKS
    glutDisplayFunc(OnDraw);
    glutTimerFunc(25, OnTimer, 0);
    glutKeyboardFunc(OnKeyboardDown);
    glutMouseFunc(OnMouseClick);

    glutMainLoop();
    return 0;
}

void OnDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5, 5, -5, 5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    tablero.dibuja();

    glutSwapBuffers();
}





void OnKeyboardDown(unsigned char key, int x, int y)
{
}

void OnTimer(int value)
{
    glutTimerFunc(100, OnTimer, 0);
    glutPostRedisplay();
}

void OnMouseClick(int b, int state, int x, int y)
{
    bool down = (state == GLUT_DOWN);
    int button = -1;

    if (b == GLUT_LEFT_BUTTON)
        button = MOUSE_LEFT_BUTTON;
    else if (b == GLUT_RIGHT_BUTTON)
        button = MOUSE_RIGHT_BUTTON;

    if (button == -1)
        return;

    int modifiers = glutGetModifiers();
    bool ctrlKey = (modifiers & GLUT_ACTIVE_CTRL) != 0;
    bool sKey = (modifiers & GLUT_ACTIVE_SHIFT) != 0;

    glutPostRedisplay();
}
