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
}

void EstadoTablero::tecla(unsigned char key) {
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


