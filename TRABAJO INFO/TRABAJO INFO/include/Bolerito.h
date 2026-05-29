#pragma once
#include <string>

using std::string;

class Bolerito
{
protected:
    string nombre;
    bool esEspecialista;  // si es Bolos_Cranker o Bolos_Stroker
    float velocidadPuntero;
    float potenciaMax;
    float longitudEstela;


public:

    Bolerito(const string& nombre, bool esEspecialista)
        : nombre(nombre), esEspecialista(esEspecialista)
    {
        velocidadPuntero = esEspecialista ? 1.5f : 3.0f;
        potenciaMax = esEspecialista ? 12.0f : 8.0f;
        longitudEstela = esEspecialista ? 6.0f : 4.0f;
    }

    // Destructor virtual para permitir la herencia
    virtual ~Bolerito() = default;


    //Gettets
    string getNombre()          const { return nombre; }
    bool getEsEspecialista()  const { return esEspecialista; }
    float getVelocidadPuntero()const { return velocidadPuntero; }
    float getPotenciaMax()     const { return potenciaMax; }
    float getLongitudEstela()  const { return longitudEstela; }

};