#include "GL/freeglut.h"
#include "math.h"
#include <iostream>
#include "FlujoJuego.h"

FlujoJuego flujo;

// CALLBACKS
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

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);

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

    flujo.dibujar();   // ← AHORA dibuja el estado actual (tablero o combate)

    glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x, int y)
{
    flujo.tecla(key);  // ← Cambia de pantalla si pulsas 1,2,3
}

void OnTimer(int value)
{
    flujo.actualizar();  // ← Actualiza el estado actual
    glutTimerFunc(100, OnTimer, 0);
    glutPostRedisplay();
}

void OnMouseClick(int b, int state, int x, int y)
{
    // si quieres usar ratón más adelante
}
