

//EstadoTablero.cpp
#include "EstadoFinJuego.h"
#include "EstadoTablero.h"
#include "FlujoJuego.h"
#include "EstadoCombate.h"
#include <iostream>
#include <chrono>
#include <thread>

extern Tablero tablero;

EstadoTablero::EstadoTablero(FlujoJuego* f,
    const std::string& pJ1,
    const std::string& pJ2)
    : flujo(f), paisJ1(pJ1), paisJ2(pJ2)
{
    j1 = flujo->getJugador1();   // puntero al jugador real
    j2 = flujo->getJugador2();   // puntero al jugador real
}

void EstadoTablero::mueve(double dt) {
    // Si hay un combate pendiente, ahora sí cambiamos de estado de forma segura
    if (estadoPendiente != nullptr) {
        EstadoJuego* siguiente = estadoPendiente;
        estadoPendiente = nullptr;
        flujo->cambiarEstado(siguiente);
        return;
    }

    Jugador* ganador = tablero.verificarGanador(*j1, *j2);

    if (ganador != nullptr) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        flujo->cambiarEstado(
            new EstadoFinJuego(flujo, ganador->getId())
        );
    }
}
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

        
        //vamos a poner aquí los mínimos por que no los quiero copiar 30 veces

        float yMin = 10.8f;
        float yMax = 12.0f;
        float xMin = -7.5f;
        float xMax = 7.5f;

        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);                           
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        //para el color del recuadro
        if (piezaHover->getNumJugador() == 1)
            glColor4f(0.0f, 0.0f, 0.08f, 0.85f);  // azulón J1
        else
            glColor4f(0.08f, 0.0f, 0.0f, 0.85f);


        //ahora tiene que dejarse de solapar con el tablero el recuadro de arriba
        glBegin(GL_QUADS);
        glVertex2f(xMin, yMin);
        glVertex2f(xMax, yMin);
        glVertex2f(xMax, yMax);
        glVertex2f(xMin, yMax);
        glEnd();


        //para que los dos bandos salgan con colores diferentes
        if (piezaHover->getNumJugador() == 1)
            ETSIDI::setTextColor(0.2f, 0.6f, 1.0f);

        else
            ETSIDI::setTextColor(1.0f, 0.3f, 0.3f);

        if (piezaHover->getNumJugador() == 1)
            glColor4f(0.2f, 0.5f, 1.0f, 1.0f);   // borde azul J1
        else
            glColor4f(1.0f, 0.3f, 0.3f, 1.0f);   // borde rojo J2

        //aquí dibujamos el cuadrado antes que las letras para que no se superponga nada
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-9.0f, yMin);
        glVertex2f(9.0f, yMin);
        glVertex2f(9.0f, yMax);
        glVertex2f(-9.0f, yMax);

        glEnd();
        glDisable(GL_BLEND);

        std::string stats = piezaHover->getNombre() + "   |   " +
            "HP: " + std::to_string(piezaHover->getVida()) + "   " +
            "ATK: " + std::to_string(piezaHover->getAtaque()) + "   " +
            "DEF: " + std::to_string(piezaHover->getDefensa());

        ETSIDI::setFont("fuentes/Bitwise.ttf", 10);//la letra pequeña para que quepa

        ETSIDI::printxy(stats.c_str(), -6.8f, 11.2f);


        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
    }

    //tenemos que ponerle al fisio un panel de hechizos por que no se entiende nada de nada al lanzarlos


    Fisio* fisioJ1 = nullptr;
    Fisio* fisioJ2 = nullptr;
    for (Personaje* p : j1->getPiezas())
        if (p->getTipo() == "fisio" && p->estaVivo())
        {
            fisioJ1 = dynamic_cast<Fisio*>(p); break;
        }
    for (Personaje* p : j2->getPiezas())
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
        float xMin = esJ1 ? 9.8f : -15.0f;
        float xMax = esJ1 ? 15.0f : -9.8f;
        float xTexto = esJ1 ? 10.3f : -14.5f;
        float xCentro = (xMin + xMax) / 2.0f;
        float xEstado = xTexto + 3.0f;

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

        if (esJ1) ETSIDI::setTextColor(0.3f, 0.6f, 1.0f);//colorines
        else      ETSIDI::setTextColor(1.0f, 0.4f, 0.4f);

        std::string titulo = esJ1 ? "J1-FISIO" : "J2-FISIO";
        ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
        ETSIDI::printxy(titulo.c_str(), xTexto, 8.5f);//impresión

        ETSIDI::setFont("fuentes/Bitwise.ttf", 10);

        // Los 7 hechizos

        float yBase = 7.3f;
        float paso = 2.0f;
        float offsetEstado = 1.1f;//vamos a poner un offset por que se me está superponiendo el texto 

        for (int i = 0; i < 7; i++) {
            float y = yBase - i * paso;

            bool seleccionado = esTurnoEste && modoHechizo && (hechizoPendiente == i + 1);

            // Nombre
            if (seleccionado) ETSIDI::setTextColor(1.0f, 1.0f, 0.0f);
            else if (usados[i]) ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
            else ETSIDI::setTextColor(0.9f, 0.9f, 0.9f);

            ETSIDI::printxy(nombres7[i].c_str(), xTexto, y);


            // ponemos ok entre corchetes así como en un videojuego
            if (usados[i]) ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
            else ETSIDI::setTextColor(0.1f, 0.9f, 0.1f);

            std::string estado = usados[i] ? "[--]" : "[OK]";

            //ETSIDI::printxy(estado.c_str(), xTexto, y - 0.7f);

            //ETSIDI::printxy(estado.c_str(), xTexto, y - offsetEstado);//aquí el offse

            ETSIDI::printxy(estado.c_str(), xEstado, y);


        }

        //quiero poner los turnos por aquí

        std::string turnoTxt;

        if (esTurnoEste) {
             turnoTxt = "¡Es tu turno!";
             ETSIDI::setTextColor(0.7f, 0.0f, 1.0f);
             ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
        }
        else {
            turnoTxt = "Turno rival";
            ETSIDI::setTextColor(0.5f, 0.5f, 0.5f);
            ETSIDI::setFont("fuentes/Bitwise.ttf", 10);
        }

		ETSIDI::printxy(turnoTxt.c_str(), xTexto, -7.5f);

        // Instrucción abajo
        if (esTurnoEste && modoHechizo && hechizoPendiente > 0) {

            std::string inst = "Apunta+SPC";
            ETSIDI::setTextColor(1.0f, 1.0f, 0.0f);
            ETSIDI::printxy(inst.c_str(), xTexto, -8.5f);
        }
        else if (esTurnoEste) {

            std::string inst = "[H]=hechizo";
            ETSIDI::setTextColor(0.5f, 0.5f, 0.5f);
            ETSIDI::printxy(inst.c_str(), xTexto, -8.5f);
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
    Jugador* jugadorActual = (gestionTurnos.getTurnoActual() == BUENOS) ? j1 : j2;
    for (Personaje* p : jugadorActual->getPiezas()) {
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


            //ESTE ES EL SHIFT TIME QUE NO NECESITA OBJETIVOS EN EL TABLERO
            if (hechizoPendiente == 3) {
                bool exito = fisioActivo->lanzarShiftTime(tablero);
                if (exito) {
                    gestionTurnos.cambiarTurno(); // ← ya estaba, está bien
                    std::cout << "[SHIFT TIME] ¡Ciclo invertido!" << std::endl;
                }
                modoHechizo = false;
                hechizoPendiente = 0;
            }

            glutPostRedisplay();
            return;
        }
    }


    // se pulsa espacio para seleccionar pieza o confirmar destino
   // se pulsa espacio para seleccionar pieza o confirmar destino
    if (key == ' ') {
        int f = cursorFila;
        int c = cursorCol;

        // HECHIZOS: tienen su propio flujo, no dependen de modoDestino
        if (modoHechizo && hechizoPendiente > 0 && fisioActivo != nullptr) {
            Personaje* objetivo = tablero.getPersonajeEn(f, c);

            bool necesitaObjetivo = (hechizoPendiente == 2 || hechizoPendiente == 5 ||
                hechizoPendiente == 7);
            if (necesitaObjetivo && objetivo == nullptr) {
                std::cout << "[HECHIZO] No hay pieza en esa casilla." << std::endl;
                glutPostRedisplay();
                return;
            }

            bool exito = false;
            switch (hechizoPendiente) {

            case 1: // Teleport
                if (primerObjetivo == nullptr) {
                    if (objetivo && objetivo->getNumJugador() == fisioActivo->getNumJugador()) {
                        primerObjetivo = objetivo;
                        std::cout << "[TELEPORT] Ahora elige casilla vacía." << std::endl;
                    }
                    else {
                        std::cout << "[TELEPORT] Elige una pieza aliada." << std::endl;
                    }
                }
                else {
                    if (tablero.hayPiezaEn(f, c)) {
                        std::cout << "[TELEPORT] La casilla debe estar vacía." << std::endl;
                    }
                    else {
                        exito = fisioActivo->lanzarTeleport(primerObjetivo, f, c, tablero);
                        if (exito) std::cout << "[TELEPORT] ¡Teletransportado!" << std::endl;
                        primerObjetivo = nullptr;
                        modoHechizo = false; hechizoPendiente = 0;
                    }
                }
                break;

            case 2: // Heal
                exito = fisioActivo->lanzarHeal(objetivo);
                if (exito) std::cout << "[HEAL] ¡Curado!" << std::endl;
                else       std::cout << "[HEAL] Fallido." << std::endl;
                modoHechizo = false; hechizoPendiente = 0;
                break;

            case 4: // Exchange
                if (primerObjetivo == nullptr) {
                    if (objetivo != nullptr) {
                        primerObjetivo = objetivo;
                        std::cout << "[EXCHANGE] Elige segunda pieza." << std::endl;
                    }
                    else {
                        std::cout << "[EXCHANGE] No hay pieza ahí." << std::endl;
                    }
                }
                else {
                    if (objetivo == nullptr) {
                        std::cout << "[EXCHANGE] Segunda casilla vacía." << std::endl;
                    }
                    else {
                        exito = fisioActivo->lanzarExchange(primerObjetivo, objetivo, tablero);
                        if (exito) std::cout << "[EXCHANGE] ¡Intercambiadas!" << std::endl;
                        primerObjetivo = nullptr;
                        modoHechizo = false; hechizoPendiente = 0;
                    }
                }
                break;

            case 5: // Summon
                exito = fisioActivo->lanzarSummon(objetivo, tablero);
                if (exito) {
                    Jugador* rival = (gestionTurnos.getTurnoActual() == BUENOS) ? j2 : j1;
                    rival->eliminarPieza(objetivo);
                    std::cout << "[SUMMON] ¡Enemigo eliminado!" << std::endl;
                }
                else {
                    std::cout << "[SUMMON] Fallido." << std::endl;
                }
                modoHechizo = false; hechizoPendiente = 0;
                break;

            case 6: // Revive
            {
                Jugador* jugActual = (gestionTurnos.getTurnoActual() == BUENOS) ? j1 : j2;
                Personaje* muerta = nullptr;
                for (Personaje* p : jugActual->getPiezas())
                    if (!p->estaVivo()) { muerta = p; break; }

                if (muerta == nullptr) {
                    std::cout << "[REVIVE] No hay piezas muertas." << std::endl;
                }
                else {
                    exito = fisioActivo->lanzarRevive(muerta, tablero);
                    if (exito) std::cout << "[REVIVE] ¡Resucitada!" << std::endl;
                    else       std::cout << "[REVIVE] Fallido (sin hueco)." << std::endl;
                }
                modoHechizo = false; hechizoPendiente = 0;
                break;
            }

            case 7: // Imprison
                exito = fisioActivo->lanzarImprison(objetivo, gestionTurnos.getNumeroCiclo());
                if (exito) std::cout << "[IMPRISON] ¡Encarcelado!" << std::endl;
                else       std::cout << "[IMPRISON] Fallido." << std::endl;
                modoHechizo = false; hechizoPendiente = 0;
                break;
            }

            if (exito) {
                gestionTurnos.cambiarTurno();
                int cicloActual = gestionTurnos.getNumeroCiclo();
                for (Personaje* p : j1->getPiezas())
                    if (p->estaEncarcelada() && cicloActual >= p->getCicloEncarcelamiento() + 2)
                        p->libertar();
                for (Personaje* p : j2->getPiezas())
                    if (p->estaEncarcelada() && cicloActual >= p->getCicloEncarcelamiento() + 2)
                        p->libertar();
            }

            piezaSeleccionada = nullptr;
            modoDestino = false;
            glutPostRedisplay();
            return;  // salimos, no procesamos movimiento normal
        }

        // MOVIMIENTO NORMAL — solo si no estamos en modo hechizo
        if (!modoDestino) {
            if (tablero.hayPiezaEn(f, c)) {
                Personaje* piezaAux = tablero.getPersonajeEn(f, c);
                bool esTurnoCorrecto =
                    (gestionTurnos.getTurnoActual() == BUENOS && piezaAux->getNumJugador() == 1) ||
                    (gestionTurnos.getTurnoActual() == MALOS && piezaAux->getNumJugador() == 2);
                if (esTurnoCorrecto) {
                    piezaSeleccionada = piezaAux;
                    modoDestino = true;
                }
            }
        }
        else {
            if (piezaSeleccionada != nullptr) {
                if (tablero.hayPiezaEn(f, c)) {
                    Personaje* piezaBajo = tablero.getPersonajeEn(f, c);
                    bool esPiezaPropia =
                        (gestionTurnos.getTurnoActual() == BUENOS && piezaBajo->getNumJugador() == 1) ||
                        (gestionTurnos.getTurnoActual() == MALOS && piezaBajo->getNumJugador() == 2);
                    if (esPiezaPropia && piezaBajo != piezaSeleccionada) {
                        piezaSeleccionada = piezaBajo;
                        glutPostRedisplay();
                        return;
                    }
                }

                if (piezaSeleccionada->esMovimientoValido(f, c, &tablero)) {
                    if (tablero.hayPiezaEn(f, c)) {
                        comprobarColision(piezaSeleccionada, f, c);
                    }
                    else {
                        tablero.eliminarPersonaje(piezaSeleccionada);
                        tablero.colocar(piezaSeleccionada, f, c);
                        gestionTurnos.cambiarTurno();
                        int cicloActual = gestionTurnos.getNumeroCiclo();
                        auto LiberarSiToca = [&](Jugador* j) {
                            for (Personaje* p : j->getPiezas())
                                if (p->estaEncarcelada() && cicloActual >= p->getCicloEncarcelamiento() + 2)
                                    p->libertar();
                            };
                        LiberarSiToca(j1);
                        LiberarSiToca(j2);
                    }
                    piezaSeleccionada = nullptr;
                    modoDestino = false;
                }
            }
        }

        glutPostRedisplay();
    }


}


void EstadoTablero::comprobarColision(Personaje* atacante, int filaDestino, int colDestino) {
    Personaje* defensor = tablero.getPersonajeEn(filaDestino, colDestino);

    if (defensor == nullptr) return;
    if (atacante == nullptr) return;
    if (defensor->getNumJugador() == atacante->getNumJugador()) return;

    // Decidir tipo de combate según color de casilla
    int colorCasilla = tablero.getCelda(filaDestino, colDestino);

    // Si el ciclo está invertido, invertimos también la lectura del color
    if (tablero.getCicloInvertido()) {
        if (colorCasilla == 0) colorCasilla = 1;
        else if (colorCasilla == 1) colorCasilla = 0;
    }

    int tipoCombate = 1; // por defecto baloncesto

    if (colorCasilla == 0) {
        // Casilla NEGRA → deporte del bando Oscuridad (J2)
        // Buscamos qué tipo es el personaje de J2 en este combate
        Personaje* piezaOscuridad = (atacante->getNumJugador() == 2) ? atacante : defensor;
        tipoCombate = getTipoCombatePorPersonaje(piezaOscuridad);
    }
    else if (colorCasilla == 1) {
        // Casilla BLANCA → deporte del bando Luz (J1)
        Personaje* piezaLuz = (atacante->getNumJugador() == 1) ? atacante : defensor;
        tipoCombate = getTipoCombatePorPersonaje(piezaLuz);
    }
    else {
        // Casilla MORADA o PODER → aleatorio entre los tres deportes
        tipoCombate = (rand() % 3) + 1;
    }

    estadoPendiente = new EstadoCombate(
        flujo, tipoCombate, paisJ1, paisJ2,
        atacante, defensor, filaDestino, colDestino
    );
}



int EstadoTablero::getTipoCombatePorPersonaje(Personaje* p) {
    std::string tipo = p->getTipo();

    if (tipo == "bolo_cranker" || tipo == "bolo_stronker")
        return 2; // bolos

    if (tipo == "boxeador_normal" || tipo == "boxeador_kickboxing")
        return 3; // boxeo

    if (tipo == "jugador_baloncesto")
        return 1; // baloncesto

    // fisio u otro → aleatorio
    return (rand() % 3) + 1;
}