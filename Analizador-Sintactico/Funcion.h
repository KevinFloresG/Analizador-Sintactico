// Funcion.h
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Definición de la clase "Funcion".

#include <iostream>
#include <sstream>
#include <list>

#ifndef FUNCION_H
#define FUNCION_H

class Funcion {
private:
	std::string id;
	std::string tipo;
	std::string valor_de_retorno;
	std::list<std::string>* parametros;
public:
	Funcion();
	Funcion(std::string, std::string, std::string, std::list<std::string>*);
	std::string getId();
	std::string getTipo();
	std::string getValor_de_retorno();
	std::list<std::string>* getParametros();
	void setId(std::string);
	void setTipo(std::string);
	void setValor_de_retorno(std::string);
	void setParametros(std::list<std::string>*);
	std::string toString()const; // PENDIENTE !!!
	~Funcion();
};

#endif // !FUNCION_H

