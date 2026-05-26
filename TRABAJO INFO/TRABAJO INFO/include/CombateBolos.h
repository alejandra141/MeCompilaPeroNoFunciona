#pragma once

#include "Combates.h"
#include "Bolo.h"
#include <vector>
#include "BolaBolos.h"
#include "Bolerito.h"


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

	//vamos a poner ya las bolas por aquí
	
	BolaBolos bolaJ1;
	BolaBolos bolaJ2;


	// Efectos BOOM para el impacto jajaja
	float tiempoEfectoJ1;
	float tiempoEfectoJ2;

	//vamos a inicializar unos personajes auxiliares los boleritos
	
	Bolerito* jugador1;
	Bolerito* jugador2;

	void comprobarColisiones();// la voy a poner privada porque no quiero que se pueda llamar desde fuera

public:

	CombateBolos(Bolerito* j1, Bolerito* j2);

    void mueve(double dt) override;
    void dibujar() override;
    void tecla(unsigned char key) override;
	void crearBolos();
	void teclaSuelta(unsigned char key) override;

};

