#include "EstadoTablero.h"
#include "FlujoJuego.h"
#include "EstadoCombate.h"
#include <iostream>

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
    glVertex3f((float)(centro.x - radio), (float)(centro.y - radio), (float)(centro.z + 0.05f));
    glVertex3f((float)(centro.x + radio), (float)(centro.y - radio), (float)(centro.z + 0.05f));
    glVertex3f((float)(centro.x + radio), (float)(centro.y + radio), (float)(centro.z + 0.05f));
    glVertex3f((float)(centro.x - radio), (float)(centro.y + radio), (float)(centro.z + 0.05f));
    glEnd();


    glLineWidth(3.0f);
    if (modoDestino) glColor3ub(255, 0, 0); // borde rojo 
    else glColor3ub(255, 255, 255);       // borde blanco 

    glBegin(GL_LINE_LOOP);
    glVertex3f((float)(centro.x - radio), (float)(centro.y - radio), (float)(centro.z + 0.06f));
    glVertex3f((float)(centro.x + radio), (float)(centro.y - radio), (float)(centro.z + 0.06f));
    glVertex3f((float)(centro.x + radio), (float)(centro.y + radio), (float)(centro.z + 0.06f));
    glVertex3f((float)(centro.x - radio), (float)(centro.y + radio), (float)(centro.z + 0.06f));
    glEnd();


    glDisable(GL_BLEND);


    // para poner las estadísticas de la pieza bajo el cursor, al parecer en lenguaje videojuegos se llama hover

    piezaHover = tablero.getPersonajeEn(cursorFila, cursorCol);
    if (piezaHover != nullptr) {
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f, 0.0f, 0.0f, 0.75f);
        glBegin(GL_QUADS);
        glVertex2f(-9.0f, 9.0f);
        glVertex2f(9.0f, 9.0f);
        glVertex2f(9.0f, 10.2f);
        glVertex2f(-9.0f, 10.2f);
        glEnd();
        if (piezaHover->getNumJugador() == 1) glColor4f(0.2f, 0.6f, 1.0f, 1.0f);
        else                                   glColor4f(1.0f, 0.3f, 0.3f, 1.0f);
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-9.0f, 9.0f);
        glVertex2f(9.0f, 9.0f);
        glVertex2f(9.0f, 10.2f);
        glVertex2f(-9.0f, 10.2f);
        glEnd();
        glDisable(GL_BLEND);

        std::string stats = piezaHover->getNombre() + "   |   " +
            "HP: " + std::to_string(piezaHover->getVida()) + "   " +
            "ATK: " + std::to_string(piezaHover->getAtaque()) + "   " +
            "DEF: " + std::to_string(piezaHover->getDefensa());
        glColor3f(1.0f, 1.0f, 0.0f);
        glRasterPos3f(-8.5f, 9.4f, 0.5f);
        for (char c : stats)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
    }

    //tenemos que ponerle al fisio un panel de hechizos por que no se entiende nada de nada al lanzarlos


    Fisio* fisioJ1 = nullptr;
    Fisio* fisioJ2 = nullptr;
    for (Personaje* p : j1.getPiezas())
        if (p->getTipo() == "fisio" && p->estaVivo())
        {
            fisioJ1 = dynamic_cast<Fisio*>(p); break;
        }
    for (Personaje* p : j2.getPiezas())
        if (p->getTipo() == "fisio" && p->estaVivo())
        {
            fisioJ2 = dynamic_cast<Fisio*>(p); break;
        }

    std::string nombres7[7] = {
        "1.Teleport", "2.Heal", "3.ShiftTime",
        "4.Exchange", "5.Summon", "6.Revive", "7.Imprison"
    };

    // Pintamos cada panel — primero J1 (izquierda), luego J2 (derecha)
    for (int bando = 1; bando <= 2; bando++) {
        Fisio* fisio = (bando == 1) ? fisioJ1 : fisioJ2;
        if (fisio == nullptr) continue;

        bool esJ1 = (bando == 1);
        float xMin = esJ1 ? -15.0f : 9.8f;
        float xMax = esJ1 ? -9.8f : 15.0f;
        float xTexto = esJ1 ? -14.5f : 10.3f;
        float xCentro = (xMin + xMax) / 2.0f;


        //les he puesto los nombres en inglés que son los que salen en el moodle

        bool usados[7] = {
            fisio->usadoTeleport, fisio->usadoHeal,    fisio->usadoShiftTime,
            fisio->usadoExchange, fisio->usadoSummon,  fisio->usadoRevive,
            fisio->usadoImprison
        };

        bool esTurnoEste = (esJ1 && gestionTurnos.getTurnoActual() == BUENOS)
            || (!esJ1 && gestionTurnos.getTurnoActual() == MALOS);

        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Fondo
        glColor4f(0.0f, 0.0f, 0.08f, 0.85f);
        glBegin(GL_QUADS);
        glVertex2f(xMin, -9.0f);
        glVertex2f(xMax, -9.0f);
        glVertex2f(xMax, 9.0f);
        glVertex2f(xMin, 9.0f);
        glEnd();

        // Borde
        if (esJ1) glColor4f(0.2f, 0.5f, 1.0f, 1.0f);
        else      glColor4f(1.0f, 0.3f, 0.3f, 1.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xMin, -9.0f);
        glVertex2f(xMax, -9.0f);
        glVertex2f(xMax, 9.0f);
        glVertex2f(xMin, 9.0f);
        glEnd();
        glDisable(GL_BLEND);

        // Título
        if (esJ1) glColor3f(0.3f, 0.6f, 1.0f);
        else      glColor3f(1.0f, 0.4f, 0.4f);
        glRasterPos3f(xTexto, 8.5f, 0.5f);
        std::string titulo = esJ1 ? "J1-FISIO" : "J2-FISIO";
        for (char c : titulo)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

        // Los 7 hechizos
        float yBase = 7.3f;
        float paso = 2.0f;
        for (int i = 0; i < 7; i++) {
            float y = yBase - i * paso;
            bool seleccionado = esTurnoEste && modoHechizo && (hechizoPendiente == i + 1);

            // Nombre
            if (seleccionado) glColor3f(1.0f, 1.0f, 0.0f);
            else if (usados[i])    glColor3f(0.4f, 0.4f, 0.4f);
            else                   glColor3f(0.9f, 0.9f, 0.9f);
            glRasterPos3f(xTexto, y, 0.5f);
            for (char c : nombres7[i])
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

            // [OK] / [--]
            if (usados[i]) glColor3f(0.4f, 0.4f, 0.4f);
            else           glColor3f(0.1f, 0.9f, 0.1f);
            glRasterPos3f(xTexto, y - 0.7f, 0.5f);
            std::string estado = usados[i] ? "[--]" : "[OK]";
            for (char c : estado)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }

        // Instrucción abajo
        if (esTurnoEste && modoHechizo && hechizoPendiente > 0) {
            glColor3f(1.0f, 1.0f, 0.0f);
            glRasterPos3f(xTexto, -8.5f, 0.5f);
            std::string inst = "Apunta+SPC";
            for (char c : inst)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
        else if (esTurnoEste) {
            glColor3f(0.5f, 0.5f, 0.5f);
            glRasterPos3f(xTexto, -8.5f, 0.5f);
            std::string inst = "[H]=hechizo";
            for (char c : inst)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }


        //ESTO NO SE BORRAAAAA
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);

    }
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


    //BUENO POR AQUÍ LOS HECHIZOS DEL FISIO CON LA TECLA H
    
	// Primero localizamos al Fisio y que no esté muerto, porque si no no se puede lanzar hechizos

    Fisio* fisioActivo = nullptr;
    Jugador& jugadorActual = (gestionTurnos.getTurnoActual() == BUENOS) ? j1 : j2;
    for (Personaje* p : jugadorActual.getPiezas()) {
        if (p->getTipo() == "fisio" && p->estaVivo()) {
            fisioActivo = dynamic_cast<Fisio*>(p);
            break;
        }
    }

    // H lanza los hechizos
    if (key == 'h' || key == 'H') {
        if (fisioActivo != nullptr) {
            modoHechizo = !modoHechizo;
            hechizoPendiente = 0;
            primerObjetivo = nullptr;
            std::cout << (modoHechizo ? "[HECHIZO] Elige hechizo 1-7" : "[HECHIZO] Cancelado") << std::endl;
        }
        glutPostRedisplay();
        return; // no procesar más teclas
    }

    // Si estamos en modo hechizo, 1 al 7 selecciona el hechizo
    if (modoHechizo && fisioActivo != nullptr) {
        if (key >= '1' && key <= '7') {
            hechizoPendiente = key - '0';
            std::cout << "[HECHIZO] Hechizo " << hechizoPendiente << " seleccionado. Apunta con cursor y pulsa ESPACIO." << std::endl;
            glutPostRedisplay();
            return;
        }
    }


    // se pulsa espacio para seleccionar pieza o confirmar destino
    if (key == ' ') {

        // Como en las inicializaciones se usa colocar(pieza, columna, fila),
        // cruzamos las variables aquí para que la matriz lógica lo entienda bien
     
            int fLogica = cursorFila;
            int cLogica = cursorCol;




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


					// PARA LOS HECHIZOS DEL FISIO MADRE MÍA ESTO ES UNA LOCURA PERO FUNCIONARÁ, LO PROMETO
                    if (modoHechizo && hechizoPendiente > 0 && fisioActivo != nullptr) {
                        Personaje* objetivo = tablero.getPersonajeEn(fLogica, cLogica);

                        bool exito = false;
                        switch (hechizoPendiente) {
                        case 1: // Teleport — elige aliado primero, luego destino
                            if (primerObjetivo == nullptr) {
                                if (objetivo && objetivo->getNumJugador() == fisioActivo->getNumJugador()) {
                                    primerObjetivo = objetivo;
                                    std::cout << "[TELEPORT] Ahora elige la casilla destino (vacía)." << std::endl;
                                }
                            }
                            else {
                                exito = fisioActivo->lanzarTeleport(primerObjetivo, fLogica, cLogica, tablero);
                                if (exito) std::cout << "[TELEPORT] Lanzado!" << std::endl;
                                primerObjetivo = nullptr;
                                modoHechizo = false; hechizoPendiente = 0;
                            }
                            break;

                        case 2: // Heal
                            exito = fisioActivo->lanzarHeal(objetivo);
                            if (exito) std::cout << "[HEAL] Curado!" << std::endl;
                            modoHechizo = false; hechizoPendiente = 0;
                            break;

                        case 3: // Shift Time — no necesita objetivo, ejecuta ya
                            exito = fisioActivo->lanzarShiftTime(tablero);
                            if (exito) std::cout << "[SHIFT TIME] Ciclo invertido!" << std::endl;
                            modoHechizo = false; hechizoPendiente = 0;
                            break;

                        case 4: // Exchange — necesita dos piezas
                            if (primerObjetivo == nullptr) {
                                if (objetivo != nullptr) {
                                    primerObjetivo = objetivo;
                                    std::cout << "[EXCHANGE] Elige la segunda pieza." << std::endl;
                                }
                            }
                            else {
                                exito = fisioActivo->lanzarExchange(primerObjetivo, objetivo, tablero);
                                if (exito) std::cout << "[EXCHANGE] Intercambiadas!" << std::endl;
                                primerObjetivo = nullptr;
                                modoHechizo = false; hechizoPendiente = 0;
                            }
                            break;

                        case 5: // Summon Elemental
                            exito = fisioActivo->lanzarSummon(objetivo, tablero);
                            if (exito) {
                                // Eliminar la pieza del jugador rival
                                Jugador& rival = (gestionTurnos.getTurnoActual() == BUENOS) ? j2 : j1;
                                rival.eliminarPieza(objetivo);
                                std::cout << "[SUMMON] Elemental invocado, enemigo eliminado!" << std::endl;
                            }
                            modoHechizo = false; hechizoPendiente = 0;
                            break;

                        case 6: // Revive
                            exito = fisioActivo->lanzarRevive(objetivo, tablero);
                            if (exito) std::cout << "[REVIVE] Pieza resucitada!" << std::endl;
                            modoHechizo = false; hechizoPendiente = 0;
                            break;

                        case 7: // Imprison
                            exito = fisioActivo->lanzarImprison(objetivo);
                            if (exito) std::cout << "[IMPRISON] Enemigo encarcelado!" << std::endl;
                            modoHechizo = false; hechizoPendiente = 0;
                            break;
                        }

                        if (!exito && hechizoPendiente != 1 && hechizoPendiente != 4) {
                            std::cout << "[HECHIZO] Fallido (ya usado o objetivo inválido)." << std::endl;
                        }

                        piezaSeleccionada = nullptr;
                        modoDestino = false;
                        glutPostRedisplay();
                        return;
                    }



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


