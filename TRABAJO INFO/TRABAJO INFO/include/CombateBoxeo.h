//CombateBoxeo.h

#pragma once
#include "Boxeador.h"
#include "Boxeador_Normal.h"
#include "Boxeador_Kickboxing.h"

class CombateBoxeo {
private:
    // pueden ser cualquier tipo de boxeador
    Boxeador* jugador1;
    Boxeador* jugador2;
    bool terminado;

    bool esIA;         // true = Juega la máquina, false = Juega Jugador 2
    float cooldownIA = 0.0f;

    void actualizarIA();
    // el "árbitro" procesa el daño
    void procesarGolpe(Boxeador* atacante, Boxeador* victima);

public:
    // El constructor recibe a los dos luchadores ya creados
    // El constructor que usará ALEJANDRA para elegir el tipo de boxeador
    CombateBoxeo(Boxeador* p1, Boxeador* p2, bool contraIA);

    // Funciones principales del combate
    void iniciarPelea();    // Aquí sonará la campana de inicio
    void actualizar();      // Aquí se comprueban las imágenes y teclas
    void finalizarPelea();  // Aquí sonará el K.O. o victoria


    // Getters para saber si el combate sigue o quién ha ganado
    bool estaTerminado();

    void detectarEntrada(char teclaPresionada);
};