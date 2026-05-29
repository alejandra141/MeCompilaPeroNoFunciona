#include "Jugador.h"

Jugador::Jugador(int id) : id(id) {}


void Jugador::setPais(const std::string& p) { pais = p; }
std::string Jugador::getPais() const { return pais; }
int Jugador::getId() const { return id; }

void Jugador::agregarPieza(Personaje* p) { piezas.push_back(p); }

void Jugador::eliminarPieza(Personaje* p) {
    piezas.erase(std::remove(piezas.begin(), piezas.end(), p), piezas.end());
   
}
Jugador::~Jugador() {
    // si no necesitas liberar nada, déjalo vacío
}

std::vector<Personaje*>& Jugador::getPiezas() { return piezas; }
bool Jugador::sinPiezas() const { return piezas.empty(); }

void Jugador::inicializarPiezas() {
    piezas.push_back(new BoloCranker(pais, id));       // [0]
    piezas.push_back(new BoloCranker(pais, id));       // [1]
    piezas.push_back(new BoloCranker(pais, id));       // [2]
    piezas.push_back(new BoloStronker(pais, id));       // [3]
    piezas.push_back(new BoloStronker(pais, id));       // [4]
    piezas.push_back(new BoloStronker(pais, id));       // [5]
    piezas.push_back(new JugadorBaloncesto(pais, id));  // [6]
    piezas.push_back(new JugadorBaloncesto(pais, id));  // [7]
    piezas.push_back(new Fisio(pais, id));              // [8]
    piezas.push_back(new BoxeadorNormal(pais, id));     // [9]
    piezas.push_back(new BoxeadorNormal(pais, id));     // [10]
    piezas.push_back(new BoxeadorNormal(pais, id));     // [11]
    piezas.push_back(new BoxeadorNormal(pais, id));     // [12]
    piezas.push_back(new BoxeadorNormal(pais, id));     // [13]
    piezas.push_back(new BoxeadorNormal(pais, id));     // [14]
    piezas.push_back(new BoxeadorNormal(pais, id));     // [15]
    piezas.push_back(new BoxeadorKickboxing(pais, id)); // [16]
    piezas.push_back(new BoxeadorKickboxing(pais, id)); // [17]

    for (auto p : piezas) p->cargarTextura();
}

//Acciones de victoria
bool Jugador::tienePieza(Personaje* p) const {
    return std::find(piezas.begin(), piezas.end(), p) != piezas.end();
}