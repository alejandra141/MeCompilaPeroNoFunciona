#include "PelotaBaloncesto.h"

PelotaBaloncesto::PelotaBaloncesto(float x, float y, float z,
    float velX, float velY, float velZ)
    : x(x), y(y), z(z), velX(velX), velY(velY), velZ(velZ), activa(true) {
}

void PelotaBaloncesto::mueve(float dt) {
    if (!activa) return;
    velY += GRAVEDAD * dt;   // gravedad
    x += velX * dt;
    y += velY * dt;
    z += velZ * dt;

    // desactivar si sale del mundo por abajo
    if (y < -5.0f) activa = false;
}