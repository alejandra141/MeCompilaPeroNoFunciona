
//Boxeador.h

#pragma once
#include <string>

class Boxeador {
protected:
    int vida;
    int fuerza;
    int defensa;
    float velocidad;
    float agilidad;
    int estela;
    bool estaEsquivando = false; // variable de estado Esquivar

    float posX, posY;       // Posición actual
    float baseYa;           // Altura original (suelo)
    float tiempoBalanceo = 0; // Contador para el rebote
    int numJugador;         // Para diferenciar entre jugador 1 y 2 (si es necesario)

public:
    // Constructor parametrizado para asumir el rol de J1 o J2 directamente
    Boxeador();
    virtual ~Boxeador() {} // Destructor virtual 

    // Funciones comunes que desarrollamos en el .cpp
    void recibirDanio(int danio);
    void realizarPunetazo();
    void realizarPatada();
    void esquivar();
    void actualizarBalanceo();

    void inicializar(int numJug); //pone las estadisticas y valores de los jugadores

    void darPaso(int direccion); // 1 = Derecha, -1 = Izquierda
    //void dibuja(); 

    // Métodos para consultar estado
   // bool getEsquivando() { return estaEsquivando; }

    int getVida();
    int getFuerza();
    bool estaVivo();

    // Getters necesarios para calcular colisiones externas
    float getX() const { return posX; }
    float getY() const { return posY; }
    //float getAncho() const { return ancho; }
    //float getAlto() const { return alto; }

};


