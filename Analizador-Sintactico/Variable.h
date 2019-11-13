// Variable.h
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Definición de la clase "Variable".

#include<iostream>

#ifndef VARIABLE_H
#define VARIABLE_H

class Variable {
private:
	std::string tipo;
	std::string id;
	std::string alcance;
	std::string valor;
public:
	Variable();
	Variable(std::string, std::string, std::string);
	Variable(std::string, std::string, std::string, std::string); // con valor
	std::string getTipo();
	std::string getId();
	std::string getAlcance();
	std::string getValor();
	void setValor(std::string);
	void setTipo(std::string);
	void setId(std::string);
	void setAlcance(std::string);
	~Variable();
};

#endif // !VARIABLE_H
