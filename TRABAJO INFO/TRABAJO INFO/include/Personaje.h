#pragma once
#include <string>
#include <vector>
#include <utility>
#include "TexturasJugadores.h"
#include "ETSIDI.h"
#include "Linea.h"

class Tablero; // cuidadillo esto lo quito amaya

class Personaje {
protected:
    
	int radioMovimiento = 1; // para asignar el movimiento de los personajes

    Linea posicion;
    std::string nombre;
    std::string tipo;
    std::string pais;
    int numJugador;
    int fila, columna;
    int vida, ataque, defensa;
    bool vivo;
    bool esquivando;   
    TexturasJugadores sprite;

    //Acciones de victoria
    bool encarcelada = false;

    int vidaMax; // para que el personaje se pueda curar solo hasta su vida máxima, no más


    int cicloEncarcelamiento = -1;//esto es lo del encarcelamiento del fisio

public:
    Personaje(std::string nombre, std::string tipo, std::string pais,
        int vida, int ataque, int defensa, int numJugador);

    virtual void cargarTextura() = 0;
    void setCasilla(int f, int c);
    void setPosicion(const Linea& p);
    void dibuja() const;

    //getters

    int getNumJugador() const { return numJugador; }
    std::string getPais() const;
    TexturasJugadores& getSprite() { return sprite; }

    int  getFila()    const;
    int  getColumna() const;
    bool estaVivo()   const;
    int  getVida()    const;
    int  getFuerza()  const;  

    int getAtaque()  const { return ataque; }
    int getDefensa() const { return defensa; }
    int getVidaMax() const { return vidaMax; }

    float getPosX() const { return posicion.x; }
    float getPosY() const { return posicion.y; }
    float getPosZ() const { return posicion.z; }

    std::string getTipo()   const;
   
    std::string getNombre() const;

    void recibirDanio(int d);
    void sanarVida(int cantidad);

    // Métodos de combate — todos los personajes los tienen
    // cada subclase puede sobreescribirlos para tener ventaja en su combate
    virtual void realizarPunetazo() { esquivando = false; }
    virtual void realizarPatada() { esquivando = false; }
    virtual void esquivar() { esquivando = true; }
    virtual void actualizarBalanceo() {}


    // virtual std::vector<std::pair<int, int>> movimientosPosibles() = 0;
    virtual std::vector<std::pair<int, int>> movimientosPosibles() {
        return std::vector<std::pair<int, int>>();
    }

    //MARTA
    
    // vale esto lo he metido aquí por que vamos a hacer que movimientos herede de personajes 
    // y los personajes de movimientos como si fuera una doble herencia así para que todo sea más fácil
    virtual bool esMovimientoValido(int destFila, int destColumna, Tablero* tablero)=0;
    virtual ~Personaje() {}

    //MARTA

    //Acciones de victoria
    bool estaEncarcelada() const { return encarcelada; }
    void encarcelar() { encarcelada = true; }
    void libertar() { encarcelada = false; }

    //función para revivir a la peña
    void revivir() { vivo = true; vida = vidaMax / 2; }

    //cosas para el encarcelamiento del fisio 
    int getCicloEncarcelamiento() const { return cicloEncarcelamiento; }
    void encarcelar(int cicloActual) { encarcelada = true; cicloEncarcelamiento = cicloActual; }


    //esto es un metodo de boxeo 
    virtual void darPaso(int direccion) {
        posicion.x += direccion * 1.0f;
        sprite.setPosicion(posicion.x, posicion.y);
    }

};