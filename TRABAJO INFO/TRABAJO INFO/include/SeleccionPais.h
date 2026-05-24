
#pragma once
#include <string>
#include <vector>
#include <GL/freeglut.h>
#include "ETSIDI.h"

struct BotonPais {
    std::string nombre;
    std::string carpeta;
    unsigned int texID;
    float x, y, w, h;
};

class SelectorPais {
private:
    std::vector<BotonPais> botones;
    int jugadorActual;
    std::string paisJ1, paisJ2;

    // Para depurar el ratón
    float ratonX, ratonY;

public:
    SelectorPais();
    bool update(float mx, float my, bool click);
    void dibuja() const;

    std::string getPaisJ1() const;
    std::string getPaisJ2() const;
    int getJugadorActual() const;
};
