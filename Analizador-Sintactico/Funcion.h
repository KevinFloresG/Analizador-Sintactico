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
	std::string type;
	std::string return_value;
	std::list<std::string> parameters;
	std::string alcance;
public:
	Funcion();
	Funcion(std::string, std::string, std::string, std::string);
	std::string GetId();
	std::string GetTipo();
	std::string GetReturnValue();
	std::list<std::string> GetParameters();
	std::string GetAlcance();
	void SetAlcance(std::string);
	void SetId(std::string);
	void SetType(std::string);
	void SetReturnValue(std::string);
	void SetParameters(std::list<std::string>);
	std::string ToString()const; // Javier: PENDIENTE PROBAR !!!
	~Funcion();
};

#endif // !FUNCION_H

