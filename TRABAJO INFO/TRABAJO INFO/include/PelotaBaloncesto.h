#pragma once

class PelotaBaloncesto {
private:
    float x, y, z;
    float velX, velY, velZ;
    bool  activa;

    static constexpr float GRAVEDAD = -4.0f;

public:
    PelotaBaloncesto(float x, float y, float z,
        float velX, float velY, float velZ);

    void  mueve(float dt);
    void  desactivar() { activa = false; }
    bool  estaActiva() const { return activa; }
    float getPosX()    const { return x; }
    float getPosY()    const { return y; }
    float getPosZ()    const { return z; }
};