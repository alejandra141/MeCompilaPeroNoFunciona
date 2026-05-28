#include "EstadoTablero.h"
#include "FlujoJuego.h"
#include "EstadoCombate.h"

extern Tablero tablero;

EstadoTablero::EstadoTablero(FlujoJuego* f,
    const std::string& paisJ1,
    const std::string& paisJ2)
    : flujo(f), j1(1), j2(2)
{
    j1.setPais(paisJ1);
    j2.setPais(paisJ2);
    j1.inicializarPiezas();
    j2.inicializarPiezas();
    tablero.inicializarJ1(j1);
    tablero.inicializarJ2(j2);
}

void EstadoTablero::mueve(double dt) {}

void EstadoTablero::dibujar() {
    tablero.dibuja();


    // calcula centro geométrico de la casilla actual del cursor
    Linea centro = tablero.centroCasilla(cursorFila, cursorCol);

    // pintamos recuadro del cursos para que se vea donde estamos
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // tamaño del recuadro
    float radio = 0.9f;

    // color del cursor: ROJO si ya elegiste pieza y buscas destino
    // BLANCO o MORADO si buscas pieza, depende del bando
    /*
    if (modoDestino) {
        glColor4ub(255, 0, 0, 100); // Rojo 
    }
    else {
        if (gestionTurnos.getTurnoActual() == BUENOS) {
            glColor4ub(255, 255, 255, 120); // Blanco 
        }
        else {
            glColor4ub(147, 112, 219, 120); // Morado 
        }
    }
    */

    //NUEVO IF

    if (modoDestino) {
        glColor4ub(0, 150, 255, 100); // Azul eléctrico (buscando destino)
    }
    else {
        glColor4ub(255, 128, 0, 100); // Naranja vibrante (buscando personaje)
    }

    // dibujamos el cuadrado relleno del cursor 
    glBegin(GL_POLYGON);
    glVertex3f(centro.x - radio, centro.y - radio, centro.z + 0.05f);
    glVertex3f(centro.x + radio, centro.y - radio, centro.z + 0.05f);
    glVertex3f(centro.x + radio, centro.y + radio, centro.z + 0.05f);
    glVertex3f(centro.x - radio, centro.y + radio, centro.z + 0.05f);
    glEnd();


    glLineWidth(3.0f);
    if (modoDestino) glColor3ub(255, 0, 0); // borde rojo 
    else glColor3ub(255, 255, 255);       // borde blanco 

    glBegin(GL_LINE_LOOP);
    glVertex3f(centro.x - radio, centro.y - radio, centro.z + 0.06f);
    glVertex3f(centro.x + radio, centro.y - radio, centro.z + 0.06f);
    glVertex3f(centro.x + radio, centro.y + radio, centro.z + 0.06f);
    glVertex3f(centro.x - radio, centro.y + radio, centro.z + 0.06f);
    glEnd();


    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);

}


void EstadoTablero::teclaEspecial(int key) {

    //mejorado para que no se salga de la matriz 9x9
    if (key == GLUT_KEY_UP) {
        if (cursorFila < 8) cursorFila++;
    }
    if (key == GLUT_KEY_DOWN) {
        if (cursorFila > 0) cursorFila--;
    }
    if (key == GLUT_KEY_LEFT) {
        if (cursorCol > 0) cursorCol--;
    }
    if (key == GLUT_KEY_RIGHT) {
        if (cursorCol < 8) cursorCol++;
    }

    glutPostRedisplay();

}


void EstadoTablero::tecla(unsigned char key) {


    // se pulsa espacio para seleccionar pieza o confirmar destino
    if (key == ' ') {

        // Como en las inicializaciones se usa colocar(pieza, columna, fila),
        // cruzamos las variables aquí para que la matriz lógica lo entienda bien
        int fLogica = cursorCol;
        int cLogica = cursorFila;

        if (!modoDestino) {
            //  seleccionar una pieza en la posición actual del cursor
            if (tablero.hayPiezaEn(cursorFila, cursorCol)) {
                Personaje* piezaAux = tablero.getPersonajeEn(fLogica, cLogica);

                // comprobamos si la pieza pertenece al jugador del turno actual
                bool esTurnoCorrecto = false;
                if (gestionTurnos.getTurnoActual() == BUENOS && piezaAux->getNumJugador() == 1) {
                    esTurnoCorrecto = true; // Turno del J1
                }
                else if (gestionTurnos.getTurnoActual() == MALOS && piezaAux->getNumJugador() == 2) {
                    esTurnoCorrecto = true; // Turno del J2
                }

                // solo si es su turno, le dejamos "agarrar" la pieza
                if (esTurnoCorrecto) {
                    piezaSeleccionada = piezaAux;
                    modoDestino = true;

                }
            }
        }
        else {
            // ya teníamos una pieza, ahora confirmamos el destino
            if (piezaSeleccionada != nullptr) {

                if (piezaSeleccionada->esMovimientoValido(fLogica, cLogica, &tablero)) {

                    if (tablero.hayPiezaEn(fLogica, cLogica)) {
                        // Si hay un enemigo -> saltamos al combate
                        comprobarColision(piezaSeleccionada, fLogica, cLogica);
                    }
                    else {
                        tablero.eliminarPersonaje(piezaSeleccionada);
                        tablero.colocar(piezaSeleccionada, fLogica, cLogica);

                        // cambio de turno
                        gestionTurnos.cambiarTurno();
                    }

                    // reseteamos el cursor
                    piezaSeleccionada = nullptr;
                    modoDestino = false;
                }
            }
        }
        glutPostRedisplay();

    }



    if (key == '1') flujo->cambiarEstado(new EstadoCombate(flujo, 1, j1.getPais(), j2.getPais()));
    if (key == '2') flujo->cambiarEstado(new EstadoCombate(flujo, 2, j1.getPais(), j2.getPais()));
    if (key == '3') flujo->cambiarEstado(new EstadoCombate(flujo, 3, j1.getPais(), j2.getPais()));
}

void EstadoTablero::comprobarColision(Personaje* atacante, int filaDestino, int colDestino) {
    int bandoEnemigo = tablero.getBandoPiezaEn(filaDestino, colDestino);

    // si no hay enemigo, no pasa nada
    if (bandoEnemigo == 0 || bandoEnemigo == atacante->getNumJugador()) return;

    // si hay enemigo elegimos combate según el tipo de atacante
    int tipoCombate = 1; // por defecto baloncesto 

    // a ver aquí he puesto que según sea tal personaje haga su combate

    std::string tipo = atacante->getTipo();
    if (tipo == "boxeador_normal" || tipo == "boxeador_kickboxing")
        tipoCombate = 3; // CombateBoxeo
    else if (tipo == "bolo_cranker" || tipo == "bolo_stroker")
        tipoCombate = 2; // CombateBolos
    else
        tipoCombate = 1; // CombateBaloncesto

    flujo->cambiarEstado(new EstadoCombate(flujo, tipoCombate, paisJ1, paisJ2));
}


