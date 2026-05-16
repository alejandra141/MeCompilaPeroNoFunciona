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

public:
    Boxeador(); // Constructor base
    virtual ~Boxeador() {} // Destructor virtual 

    // Funciones comunes que desarrollamos en el .cpp
    void recibirDanio(int danio);
    void realizarPunetazo();
    void realizarPatada();
    void esquivar();

    void actualizarBalanceo();

    // Métodos para consultar estado
   // bool getEsquivando() { return estaEsquivando; }

    int getVida();
    int getFuerza();
    bool estaVivo();
};
