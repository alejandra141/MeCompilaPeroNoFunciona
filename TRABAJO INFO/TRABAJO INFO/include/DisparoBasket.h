#pragma once
#include "PelotaBaloncesto.h"
#include <vector>

struct Punto3D { float x, y, z; };

class DisparoBasket {
private:
    PelotaBaloncesto       pelota;
    bool                   conEstela;
    std::vector<Punto3D>   puntosEstela;
    unsigned int texID;

public:
    DisparoBasket(float x, float y, float z,
        float velX, float velY, float velZ,
        bool conEstela = false);

    void actualizar(float dt);
    void dibujar(bool conEstela) const;
    void desactivar();
    bool estaActivo()  const;
    bool colisionaConAro(float aroX, float aroY, float aroZ, float radio) const;
};