// Variable.cpp
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Implementación de la clase "Variable".

#include"Variable.h"

Variable::Variable() : tipo(""), id(""), alcance(""), valor("") {}
Variable::Variable(std::string tipo, std::string id, std::string alcance) {
	this->tipo = tipo;
	this->alcance = alcance;
	this->id = id;
}
Variable::Variable(std::string tipo, std::string id, std::string alcance, std::string valor) {
	this->tipo = tipo;
	this->alcance = alcance;
	this->id = id;
	this->valor = valor;
}
std::string Variable::getTipo() { return this->tipo; }
std::string Variable::getId() { return this->id; }
std::string Variable::getAlcance() { return this->alcance; }
std::string Variable::getValor() { return this->valor; }
void Variable::setValor(std::string valor) { this->valor = valor; }
void Variable::setTipo(std::string tipo) { this->tipo = tipo; }
void Variable::setId(std::string id) { this->id = id; }
void Variable::setAlcance(std::string alcance) { this->alcance = alcance; }
Variable::~Variable() {}