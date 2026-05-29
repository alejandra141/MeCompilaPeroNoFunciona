
//Jugador.h

#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "Bolos_Cranker.h"
#include "Bolos_Stronker.h"
#include "Jugador_Baloncesto.h"
#include "Boxeador_Normal.h"
#include "Boxeador_Kickboxing.h"
#include "Fisio.h"

class Jugador {
private:
    int id;
    std::string pais;
    std::vector<Personaje*> piezas;



public:
    Jugador(int id);
    ~Jugador();

    void setPais(const std::string& p);
    std::string getPais() const;
    int getId() const;

    void agregarPieza(Personaje* p);
    void eliminarPieza(Personaje* p);
    std::vector<Personaje*>& getPiezas();
    bool sinPiezas() const;

    void inicializarPiezas();

    //Para acciones de victoria
    bool tienePieza(Personaje* p) const;  //Miramos si hay pieza en casilla (para fin de juego)

};

