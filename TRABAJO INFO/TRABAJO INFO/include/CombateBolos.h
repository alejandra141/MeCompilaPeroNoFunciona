#pragma once

#include "Combates.h"
#include "Bolo.h"
#include <vector>


using std::vector;

class CombateBolos : public Combates {
private:
	vector<Bolo> bolos;

	//detalles de los jugadores
	int bolosDerribadosJ1{};
	int bolosDerribadosJ2{};
	bool j1esEspecialista{};
	bool j2esEspecialista{};

	// cosas para los punteros
	float anguloJ1;
	float dirJ1;

	float anguloJ2;
	float dirJ2;

public:

	CombateBolos();	

    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
	void crearBolos();

};

