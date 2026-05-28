#pragma once

class Combates {
public:
    virtual void mueve(double dt) = 0;
    virtual void dibujar() = 0;
    virtual void tecla(unsigned char key) = 0;
    virtual void teclaEspecial(int key) {};           
    virtual void teclaEspecialSuelta(int key) {};     

    //chiquillas he añadido esta clase para poder poner la potencia del disparillo
	//que sea que al soltar la tecla se dispare, y mientras se mantenga pulsada
	//se vaya cargando la potencia, tiene corchetes para que no de error al no implementarla 
    //en los otros combates, pero se puede sobreescribir en el combate de bolos
    virtual void teclaSuelta(unsigned char key) {};
    virtual bool haTerminado() const { return false; } //ESTO ES LO QUE TENEMOS QUE USAR TODAS PARA DECIR QUE EL COMBATE HA TERMINADO Y VOLVER A TABLERO (POLIMORFISMO)
	virtual int getGanador() const { return 0; }  //PARA QUE LOS COMBATES DIGAN QUIEN HA GANADO, DEVOLVIENDO 0 SI NO HAY GANADOR, 1 SI GANA EL JUGADOR 1 Y 2 SI GANA EL JUGADOR 2

    virtual ~Combates() {}
};


