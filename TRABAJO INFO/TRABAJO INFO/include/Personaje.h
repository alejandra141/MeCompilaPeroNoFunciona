#pragma once
#include <string>
#include <vector>
#include <utility>
#include "TexturasJugadores.h"
#include "ETSIDI.h"
#include "Linea.h"

class Personaje {
private:
    Linea posicion;
    std::string nombre;
    std::string tipo;
    std::string pais;
    int numJugador;
    int fila, columna;
    int vida, ataque, defensa;
    bool vivo;
    bool esquivando;   // ← nuevo
    TexturasJugadores sprite;

public:
    Personaje(std::string nombre, std::string tipo, std::string pais,
        int vida, int ataque, int defensa, int numJugador);

    virtual void cargarTextura() = 0;
    void setCasilla(int f, int c);
    void setPosicion(const Linea& p);
    void dibuja() const;



    int getNumJugador() const { return numJugador; }
    std::string getPais() const;
    TexturasJugadores& getSprite() { return sprite; }

    int  getFila()    const;
    int  getColumna() const;
    bool estaVivo()   const;
    int  getVida()    const;
    int  getFuerza()  const;   
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

    virtual std::vector<std::pair<int, int>> movimientosPosibles() = 0;
    virtual ~Personaje() {}
};