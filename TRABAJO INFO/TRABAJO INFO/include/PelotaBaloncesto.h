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
    float getVelX() const { return velX; }
    float getVelY() const { return velY; }
    float getVelZ() const { return velZ; }

    void setVel(float vx, float vy, float vz) {
        velX = vx;
        velY = vy;
        velZ = vz;
    }
};