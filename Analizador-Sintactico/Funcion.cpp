// Funcion.cpp
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Implementación de la clase "Funcion".

#include"Funcion.h"

Funcion::Funcion() :id(""), tipo(""), valor_de_retorno("") {}
Funcion::Funcion(std::string tipo, std::string id, std::string valor_de_retorno) {
	this->id = id;
	this->valor_de_retorno = valor_de_retorno;
	this->tipo = tipo;
}
std::string Funcion::getId() { return this->id; }
std::string Funcion::getTipo() { return this->tipo; }
std::string Funcion::getValor_de_retorno() { return this->valor_de_retorno; }
std::list<std::string> Funcion::getParametros() { return this->parametros; }
void Funcion::setId(std::string id) { this->id = id; }
void Funcion::setTipo(std::string tipo) { this->tipo = tipo; }
void Funcion::setValor_de_retorno(std::string valor_de_retorno) { this->valor_de_retorno = valor_de_retorno; }
void Funcion::setParametros(std::list<std::string> parametros) { this->parametros = parametros; }
Funcion::~Funcion() {}
