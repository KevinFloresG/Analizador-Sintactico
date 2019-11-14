// Variable.h
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Definición de la clase "Variable".

#include <iostream>
#include <sstream>

#ifndef VARIABLE_H
#define VARIABLE_H

class Variable {
private:
	std::string type;
	std::string id;
	std::string scope;
	std::string value;
public:
	Variable();
	Variable(std::string, std::string, std::string);
	Variable(std::string, std::string, std::string, std::string); // con valor
	std::string GetType()const;
	std::string GetId()const;
	std::string GetScope()const;
	std::string GetValue()const;
	void SetValue(std::string);
	void SetType(std::string);
	void SetId(std::string);
	void SetScope(std::string);
	std::string ToString()const;
	~Variable();
};

#endif // !VARIABLE_H
