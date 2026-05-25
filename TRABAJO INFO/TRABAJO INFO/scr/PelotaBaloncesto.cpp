#include "PelotaBaloncesto.h"
#include <cmath>

PelotaBaloncesto::PelotaBaloncesto(float px, float py, float pz,
    float vx, float vy, float vz)
    : x(px), y(py), z(pz), dx(vx), dy(vy), dz(vz), velocidad(20.0f)
{
}

void PelotaBaloncesto::mueve(float dt) {
    x += dx * velocidad * dt;
    y += dy * velocidad * dt;
    z += dz * velocidad * dt;
}

void PelotaBaloncesto::dibuja() const {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(1, 0.5f, 0);
    glutSolidSphere(0.5, 16, 16);
    glPopMatrix();
}

bool PelotaBaloncesto::fuera() const {
    return (z < -60 || z > 10 || x < -30 || x > 30 || y < -30 || y > 30);
}
