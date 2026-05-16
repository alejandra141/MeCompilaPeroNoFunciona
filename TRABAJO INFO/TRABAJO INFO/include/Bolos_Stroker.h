#pragma once

class Bolos_Stroker : public Personaje {
public:
    Bolos_Stroker(bandos b, float px, float py)
        : Personaje(b, px, py, "Personajes/Espana/buenos/Bolos_Stroker_ESP.png")
    {
        // Estadísticas específicas del boxeador normal
        vida = 120;
        fuerza = 20;
        defensa = 12;
        velocidad = 1.1f;
        agilidad = 1.0f;
        estela = 1;
    }

    void dibuja()  {

    }
    void mueve() {

    }
    void habilidadEspecial()  {
        
    }
};
