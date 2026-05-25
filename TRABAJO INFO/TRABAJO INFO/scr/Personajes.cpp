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

void Personaje::setCasilla(int f, int c) {
    fila = f;
    columna = c;
}
void Personaje::setPosicion(const Linea& p) {
    posicion = p;
    sprite.setPosicion(p.x, p.y);   // ← esto SI quieres que el sprite se mueva
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