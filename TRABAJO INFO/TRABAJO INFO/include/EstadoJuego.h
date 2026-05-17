#pragma once
class EstadoJuego {
public:
    virtual void actualizar() = 0;
    virtual void dibujar() = 0;
    virtual void tecla(unsigned char key) = 0;
    virtual ~EstadoJuego() {}
};
