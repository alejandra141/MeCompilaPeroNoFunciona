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

void OnKeyboardSpecialDown(int key, int x, int y) {
    flujo.teclaEspecial(key);
}
void OnKeyboardSpecialUp(int key, int x, int y) {
    flujo.teclaEspecialSuelta(key);
}

void OnMouseClick(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    // Convertir píxeles a coordenadas OpenGL
    // fov=60, Z cámara=20, plano Z=0
    float alturaVisible = 2.0f * tan(30.0f * 3.14159f / 180.0f) * 20.0f;
    float anchoVisible = alturaVisible * (800.0f / 600.0f);
    float mx = ((float)x / 800.0f - 0.5f) * anchoVisible;
    float my = (0.5f - (float)y / 600.0f) * alturaVisible;

    // Solo reenviar si estamos en selección
    EstadoSeleccionPais* sel = dynamic_cast<EstadoSeleccionPais*>(flujo.getEstado());
    //if (sel) sel->click(mx, my);
}

