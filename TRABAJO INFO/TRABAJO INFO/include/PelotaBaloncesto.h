#pragma once
#include "GL/freeglut.h"

class PelotaBaloncesto {
private:
    float x, y, z;
    float dx, dy, dz;
    float velocidad;

public:
    PelotaBaloncesto(float px = 0, float py = 0, float pz = 0,
        float vx = 0, float vy = 0, float vz = -1);

    void mueve(float dt);
    void dibuja() const;
    bool fuera() const;
};
