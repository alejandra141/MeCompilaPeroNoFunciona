#ifndef SELECTORPAIS_H
#define SELECTORPAIS_H

#include <vector>
#include <string>

class SelectorPais {
private:
    std::vector<std::string> nombres = {
        "Espana", "Francia", "USA", "Italia", "Inglaterra"
    };

    int indiceJ1 = 0;
    int indiceJ2 = 0;

    bool confirmadoJ1 = false;
    bool confirmadoJ2 = false;

    std::string paisJ1;
    std::string paisJ2;


public:

    //para que no salte directamente y se ponga el sombreado bien 
    float tiempoEspera = 0.0f;
    bool listos = false;

    SelectorPais() = default;

    void moverJ1(int dir);   // -1 arriba, +1 abajo
    void moverJ2(int dir);

    bool confirmarJ1();
    bool confirmarJ2();

    bool seleccionCompleta() const {
        return confirmadoJ1 && confirmadoJ2;
    }

    void dibuja() const;

    std::string getPaisJ1() const { return paisJ1; }
    std::string getPaisJ2() const { return paisJ2; }
};

#endif
