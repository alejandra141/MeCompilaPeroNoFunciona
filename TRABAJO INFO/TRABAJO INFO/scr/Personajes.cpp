#include "Personaje.h"

Personaje::Personaje(std::string nombre, std::string tipo, std::string pais,
    int vida, int ataque, int defensa, int numJugador)
    : nombre(nombre), tipo(tipo), pais(pais),
    vida(vida), ataque(ataque), defensa(defensa),
    numJugador(numJugador), fila(-1), columna(-1),
    vivo(true), esquivando(false) {
}

void Personaje::cargarTextura() {
    std::string ruta = "Personajes/" + pais +
        "/jugador" + std::to_string(numJugador) +
        "/" + tipo + ".png";
    sprite.setTextura(ETSIDI::getTexture(ruta.c_str()).id);
}

void Personaje::setPosicion(int f, int c) {
    fila = f; columna = c;
    float x = -9.0f + c * 2.0f + 1.0f;
    float y = -9.0f + f * 2.0f + 1.0f;
    sprite.setPosicion(x, y);
}

void Personaje::recibirDanio(int d) {
    if (!esquivando) {
        vida -= d;
        if (vida <= 0) { vida = 0; vivo = false; }
    }
    esquivando = false;
}

void Personaje::dibuja()     const { sprite.dibuja(); }
int  Personaje::getFila()    const { return fila; }
int  Personaje::getColumna() const { return columna; }
bool Personaje::estaVivo()   const { return vivo; }
int  Personaje::getVida()    const { return vida; }
int  Personaje::getFuerza()  const { return ataque; }
std::string Personaje::getTipo()   const { return tipo; }
std::string Personaje::getPais()   const { return pais; }
std::string Personaje::getNombre() const { return nombre; }
void Personaje::sanarVida(int cantidad) { vida += cantidad; }   