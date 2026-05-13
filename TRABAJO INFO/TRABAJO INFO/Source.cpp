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
Turnos turno; // turno todavía está un poco en proceso 


//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void);		 //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	

void OnMouseClick(int button, int state, int x, int y); // para el ratón


int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	//habilitar luces y definir perspectiv
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick); //la función del ratón

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}
void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(0.0, 7.0, 15.0,  // posicion del ojo
		0.0, 0.0, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	//aqui es donde hay que poner el c�digo de dibujo

	tablero.dibuja();


	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{

}

void OnTimer(int value)
{


	//Obligatorio 
	glutTimerFunc(100, OnTimer, 0);
	glutPostRedisplay();

}

void OnMouseClick(int b, int state, int x, int y)
{
	bool down = (state == GLUT_DOWN);
	int button = -1;

	if (b == GLUT_LEFT_BUTTON) {
		button = MOUSE_LEFT_BUTTON;
	}
	else if (b == GLUT_RIGHT_BUTTON) {
		button = MOUSE_RIGHT_BUTTON;
		std::cout << "MOUSE_RIGHT_BUTTON" << std::endl;
	}

	// Ignorar otros botones
	if (button == -1)
		return;

	int modifiers = glutGetModifiers();

	bool ctrlKey = (modifiers & GLUT_ACTIVE_CTRL) != 0;
	bool sKey = (modifiers & GLUT_ACTIVE_SHIFT) != 0;

	//pantalla.MouseButton(x, y, button, down, sKey, ctrlKey);ESTO ES POR SI QUEREMOS QUE EN LA PANTALLA SALGAN INSTRUCCIONES

	glutPostRedisplay();
}

