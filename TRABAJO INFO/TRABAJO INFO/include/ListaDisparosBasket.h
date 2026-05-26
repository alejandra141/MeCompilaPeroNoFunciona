#pragma once
#include "DisparoBasket.h"
#include <vector>

class ListaDisparos {
private:
    std::vector<DisparoBasket   > disparos;

public:
    void agregar(float x, float y, float z,
        float velX, float velY, float velZ,
        bool conEstela = false);

    void actualizar(float dt);
    void limpiarInactivos();
    void dibujar(bool conEstela) const;
    bool hayColisionConAro(float aroX, float aroY, float aroZ, float radio);
};