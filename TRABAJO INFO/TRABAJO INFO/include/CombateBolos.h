#pragma once
#include "Combates.h"
#include "Bolo.h"
#include <vector>
#include "BolaBolos.h"
#include "Personaje.h"


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

	void comprobarColisiones();

	// declaramos el tiempo que va a permanecer el juego mostrando fin juego antes de volver al tablero 
	float tiempoFinJuego;

	//los personajes van a entrar por punteros
	Personaje* jugador1;
	Personaje* jugador2;

	//para saber el ganador del combate 

	int ganador;  // 1 o 2

	enum Estado { INSTRUCCIONES, JUGANDO, FIN };
	Estado estado = INSTRUCCIONES;

	float posXj1, posYj1;//para encapsular la posicion de combate con la real de los personajes, para que no se líen con las posiciones del tablero y esas
	float posXj2, posYj2;// cosas, y para que el combate sea más fluida y no se note el cambio de posiciones entre tablero y combate, que es lo que me ha pasado a mí al principio jajaja


public:

	CombateBolos();

	void mueve(double dt) override;
	void dibujar() override;
	void tecla(unsigned char key) override;
	void crearBolos();
	void teclaSuelta(unsigned char key) override;

	//métodos para obtener el ganador y saber si el juego ha temrinado 
	bool haTerminado() const override { return estado == FIN; }
	int getGanador() const override { return ganador; }
	bool j1DerriboEnEsteLanzamiento = false;
	bool j2DerriboEnEsteLanzamiento = false;


	CombateBolos(Personaje* j1, Personaje* j2); //constructor para recibir los personajes que van a combatir

	void iniciarCombate();    // Aquí sonará la campana de inicio

};

