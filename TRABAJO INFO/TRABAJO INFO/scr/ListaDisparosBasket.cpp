#include "ListaDisparosBasket.h"
#include <algorithm>
#include "GL/freeglut.h"
#include <iostream>

void ListaDisparos::agregar(float x, float y, float z,
    float velX, float velY, float velZ,
    bool conEstela) {
    std::cout << "AGREGANDO disparo en " << x << " " << y << " " << z << std::endl;
    disparos.emplace_back(x, y, z, velX, velY, velZ, conEstela);
}

void ListaDisparos::actualizar(float dt) {
    for (auto& d : disparos)
        d.actualizar(dt);
}

void ListaDisparos::limpiarInactivos() {
    disparos.erase(
        std::remove_if(disparos.begin(), disparos.end(),
            [](const DisparoBasket& d) { return !d.estaActivo(); }),
        disparos.end()
    );
}

void ListaDisparos::dibujar(bool conEstela) const {
  
    for (const auto& d : disparos)
        d.dibujar(conEstela);
}

bool ListaDisparos::hayColisionConAro(float aroX, float aroY, float aroZ, float radio) {
    for (auto& d : disparos) {
        if (d.colisionaConAro(aroX, aroY, aroZ, radio)) {
            d.desactivar();
            return true;
        }
    }
    return false;
}