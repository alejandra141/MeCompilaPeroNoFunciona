
//CombateBaloncesto.h

#pragma once
#include "Combates.h"
#include "Canasta.h"
#include "Basketboller.h"
#include "ListaDisparosBasket.h"

class CombateBaloncesto : public Combates {
private:
    Canasta        canasta;
    Basketboller* j1;
    Basketboller* j2;
    ListaDisparos  disparosJ1;
    ListaDisparos  disparosJ2;
    bool           estelaJ1;
    bool           estelaJ2;
    int            puntosJ1;
    int            puntosJ2;
    float          potenciaJ1;
    float          potenciaJ2;
    bool           cargandoJ1;
    bool           cargandoJ2;
    float          anguloJ1;
    float          anguloJ2;
    bool           teclaIzqJ1;
    bool           teclaDerJ1;
    bool           teclaIzqJ2;
    bool           teclaDerJ2;

    int ganador = 0; //0 = nadie, 1 = J1, 2 = J2 ESTO ES APRA ANUNCIAR EL GANADOR
    enum Estado { JUGANDO, FIN };
    Estado estado = JUGANDO;

    static constexpr float POTENCIA_MAX = 15.0f;
    static constexpr float VELOCIDAD_CARGA = 8.0f;
    static constexpr int   UMBRAL_ESTELA = 7;
    static constexpr float VEL_ANGULO = 60.0f;
    static constexpr float ANGULO_MAX = 60.0f;

    void disparar(int jugador, float potencia);
    void comprobarColisiones();
    void dibujarLineaApuntado(float x, float y, float z, float angulo) const;

public:
    CombateBaloncesto(Basketboller* j1, Basketboller* j2);
    ~CombateBaloncesto();

    void mueve(double dt)                  override;
    void dibujar()                         override;
    void tecla(unsigned char key)          override;
    void teclaSuelta(unsigned char key)    override;
    void teclaEspecial(int key)            override;
    void teclaEspecialSuelta(int key)      override;
    bool haTerminado() const { return estado == FIN; }  //para que el EstadoCombate sepa cuándo volver al tablero cuando se llega a 5 puntos (Alejandra intentar hacer igual*)
    int getGanador() const { return ganador; }  //PARA ANUNCIAR GANADOR COMBATE
};

