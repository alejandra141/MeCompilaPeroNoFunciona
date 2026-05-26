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

    virtual ~Combates() {}
};


