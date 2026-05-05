#include <GL/freeglut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);

    glutCreateWindow("ARCHEON WII SPORTS");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
