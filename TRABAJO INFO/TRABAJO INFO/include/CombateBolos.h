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

	// cosas para las estelas
	float anguloJ1;
	float dirJ1;

	float anguloJ2;
	float dirJ2;

	// esto es para la potencia del disparo
	float potenciaJ1;
	float potenciaJ2;
	bool cargandoJ1;
	bool cargandoJ2;
	bool lanzandoJ1;
	bool lanzandoJ2;

public:

	CombateBolos();	

    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
	void crearBolos();
	void teclaSuelta(unsigned char key) override;

};

