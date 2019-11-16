// Variable.cpp
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Implementación de la clase "Variable".

#include"Variable.h"

Variable::Variable() : type(""), id(""), scope(""), value("") {}

Variable::Variable(std::string tipo, std::string id, std::string alcance) {
	this->type = tipo;
	this->scope = alcance;
	this->id = id;
	this->value = ""; 
}
Variable::Variable(std::string tipo, std::string id, std::string alcance, std::string valor) {
	this->type = tipo;
	this->scope = alcance;
	this->id = id;
	this->value = valor;
}
std::string Variable::GetType()const { return this->type; }

std::string Variable::GetId()const { return this->id; }

std::string Variable::GetScope()const { return this->scope; }

std::string Variable::GetValue()const { return this->value; }

void Variable::SetValue(std::string valor) { this->value = valor; }

void Variable::SetType(std::string tipo) { this->type = tipo; }

void Variable::SetId(std::string id) { this->id = id; }

void Variable::SetScope(std::string alcance) { this->scope = alcance; }

std::string Variable::ToString()const {
	std::stringstream s;

	s << "Id: " << id << " " << "Tipo: " << type << " " << "Valor: " << value << " " << "Alcance: " << scope << std::endl;

	return s.str();
}

Variable::~Variable() {}