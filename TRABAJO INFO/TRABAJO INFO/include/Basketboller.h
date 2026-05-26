#pragma once
#include <string>

class Basketboller {
protected:
    std::string nombre;
    int         velocidad;
    float       posX, posY, posZ;

public:
    Basketboller(const std::string& nombre, int velocidad, float posX, float posY, float posZ);
    virtual ~Basketboller() = default;

    std::string getNombre()    const { return nombre; }
    int         getVelocidad() const { return velocidad; }
    float       getPosX()      const { return posX; }
    float       getPosY()      const { return posY; }
    float       getPosZ()      const { return posZ; }
};