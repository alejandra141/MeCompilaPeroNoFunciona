#pragma once

#include "Combates.h"
#include "Bolo.h"
#include <vector>


using std::vector;

class CombateBolos : public Combates {
private:
	vector<Bolo> bolos;

public:

	CombateBolos();	

    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
	void crearBolos();

};

