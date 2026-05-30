#pragma once
#include "Combates.h"
#include "Boxeador.h"
#include "Personaje.h"
#include "Boxeador_Normal.h"
#include "Boxeador_Kickboxing.h"

class CombateBoxeo : public Combates {
private:
    // pueden ser cualquier tipo de boxeador
    Personaje* jugador1;
    Personaje* jugador2;
    bool terminado;

    bool esIA;         // true = Juega la máquina, false = Juega Jugador 2
    float cooldownIA = 0.0f;

    //void actualizarIA(); por ahora lo vamos a hacer sin IA
    // el "árbitro" procesa el daño
    void procesarGolpe(Personaje* atacante, Personaje* victima);
 

	enum Estado { INSTRUCCIONES, JUGANDO, FIN }; //SOY LORENA ESTO ES PARA FINALIZAR EL COMBATE Y ANUNCIAR EL GANADOR  
    Estado estado = INSTRUCCIONES;
    int ganador = 0;

    float posXj1, posYj1;
    float posXj2, posYj2;

    //le he añadido más ventajes
    float tiempoEsquivaJ1 = 0.0f;
    float tiempoEsquivaJ2 = 0.0f;

public:
    // El constructor recibe a los dos luchadores ya creados
    // El constructor que usará ALEJANDRA para elegir el tipo de boxeador
    CombateBoxeo(Personaje* p1, Personaje* p2, bool contraIA = false);

    // Funciones principales del combate
    void iniciarPelea();    // Aquí sonará la campana de inicio
    void mueve(double dt);      // Aquí se comprueban las imágenes y teclas
    void finalizarPelea();  // Aquí sonará el K.O. o victoria


    // Getters para saber si el combate sigue o quién ha ganado
    bool estaTerminado();

    void detectarEntrada(char teclaPresionada);


    void dibujar() override;
    void tecla(unsigned char key) override;

	bool haTerminado() const override { return estado == FIN; } // PARA EL FIN DEL COMBATE Y VOLVER A TABLERO
    int getGanador() const override { return ganador; }
};

