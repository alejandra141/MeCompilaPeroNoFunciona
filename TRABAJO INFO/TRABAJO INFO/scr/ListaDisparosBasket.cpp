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
bool ListaDisparos::hayCanasta(float cx, float cy, float anchoZona, float altoZona) {
    for (auto& d : disparos) {
        if (!d.estaActivo()) continue;

        bool dentroX = d.getX() > (cx - anchoZona / 2) && d.getX() < (cx + anchoZona / 2);
        bool dentroY = d.getY() > (cy - altoZona) && d.getY() < cy;

        bool entraPorDebajo = d.getVy() > 0;

        if (dentroX && dentroY && entraPorDebajo) {
            d.desactivar();
            return true;
        }
    }
    return false;
}


bool ListaDisparos::reboteConTablero(float yLinea) {
    bool rebote = false;

    for (auto& d : disparos) {
        if (!d.estaActivo()) continue;

        // Si la pelota sube y toca la línea del tablero
        if (d.getY() >= yLinea && d.getVy() > 0) {

            // Rebote vertical simple
            d.setVel(d.getVx(), -d.getVy(), d.getVz());
            rebote = true;
        }
    }
    return rebote;
}

void ListaDisparos::reboteEntrePelotas() {
    for (int i = 0; i < disparos.size(); i++) {
        for (int j = i + 1; j < disparos.size(); j++) {

            if (!disparos[i].estaActivo() || !disparos[j].estaActivo()) continue;

            float dx = disparos[j].getX() - disparos[i].getX();
            float dy = disparos[j].getY() - disparos[i].getY();
            float dz = disparos[j].getZ() - disparos[i].getZ();
            float dist = sqrt(dx * dx + dy * dy + dz * dz);

            if (dist < 1.0f) { // radio aproximado
                float vx1 = disparos[i].getVx();
                float vy1 = disparos[i].getVy();
                float vz1 = disparos[i].getVz();

                disparos[i].setVel(disparos[j].getVx(), disparos[j].getVy(), disparos[j].getVz());
                disparos[j].setVel(vx1, vy1, vz1);
            }
        }
    }
}