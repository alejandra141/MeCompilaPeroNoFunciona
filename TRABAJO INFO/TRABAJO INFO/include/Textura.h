#pragma once
#include <GL/freeglut.h>

class Textura {
private:
    GLuint id = 0;   // identificador de la textura

public:
    Textura() = default;
    ~Textura();

    bool cargar(const char* archivo);
    void activar() const;
};
#pragma once
