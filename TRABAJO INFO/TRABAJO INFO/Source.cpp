#include "GL/freeglut.h"
#include "math.h"
#include <iostream>
#include "FlujoJuego.h"
#include "Tablero.h"
#include <chrono>
#include <EstadoSeleccionPais.h>
using namespace std::chrono;


Tablero tablero;
FlujoJuego flujo;

// CALLBACKS
void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void OnKeyboardUp(unsigned char key, int x, int y); //este es el que he añadido el 25 de mayo
void OnKeyboardSpecialDown(int key, int x, int y);
void OnKeyboardSpecialUp(int key, int x, int y);



int main(int argc, char* argv[])
{
    
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("MiJuego");

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);

    glutDisplayFunc(OnDraw);
    glutTimerFunc(25, OnTimer, 0);
    glutKeyboardFunc(OnKeyboardDown);
    glutMouseFunc(OnMouseClick);
    glutKeyboardUpFunc(OnKeyboardUp);
    glutSpecialFunc(OnKeyboardSpecialDown);
    glutSpecialUpFunc(OnKeyboardSpecialUp);

    glutMainLoop();
    return 0;
}

void OnDraw(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    //  PROYECCIÓN 3D 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 200.0);

    //  CÁMARA 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 20,   // cámara delante del tablero
        0, 0, 0,    // mira al centro
        0, 1, 0);   // arriba
   

    //  DIBUJO DEL JUEGO 
    flujo.dibujar();   

    glutSwapBuffers();
}

//este es para cuando pulsas una tecla
void OnKeyboardDown(unsigned char key, int x, int y)
{
    flujo.tecla(key);  // ← Cambia de pantalla si pulsas 1,2,3
}

//esto es para cuando sueltas una tecla
void OnKeyboardUp(unsigned char key, int x, int y)
{
    flujo.teclaSuelta(key);
}

void OnKeyboardSpecialDown(int key, int x, int y) {
    flujo.teclaEspecial(key);
}
void OnKeyboardSpecialUp(int key, int x, int y) {
    flujo.teclaEspecialSuelta(key);
}


void OnTimer(int value)
{
    static auto last = high_resolution_clock::now();
    auto now = high_resolution_clock::now();
    duration<double> elapsed = now - last;
    double dt = elapsed.count();
    last = now;

    flujo.mueve(dt);   // ← le pasamos el dt real

    glutPostRedisplay();
    glutTimerFunc(25, OnTimer, 0);
}



void OnMouseClick(int button, int state, int x, int y) {

}

