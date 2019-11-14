// Funcion.cpp
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Implementación de la clase "Funcion".

#include"Funcion.h"

Funcion::Funcion() :id(""), type(""), return_value("") {}

Funcion::Funcion(std::string type, std::string id, std::string return_value) {
	this->id = id;
	this->return_value = return_value;
	this->type= type;
}

std::string Funcion::GetId() { return this->id; }

std::string Funcion::GetTipo() { return this->type; }

std::string Funcion::GetReturnValue() { return this->return_value; }

std::list<std::string> Funcion::GetParameters() { return this->parameters; }

void Funcion::SetId(std::string id) { this->id = id; }

void Funcion::SetType(std::string tipo) { this->type = tipo; }

void Funcion::SetReturnValue(std::string valor_de_retorno) { this->return_value = valor_de_retorno; }

void Funcion::SetParameters(std::list<std::string> parametros) { this->parameters = parametros; }

std::string Funcion::ToString() const {
	std::stringstream s;

	s << "Id: " << id << " " << "Tipo: " << type << " " << "Valor de R.: " << return_value <<
		" " << "Parametros: ";

	// Javier: No se ha probado, no recuerdo si así era como uno recorría adecuadamente la lista
	int i = 0;
	std::list<std::string>::const_iterator iterator = this->parameters.begin();

	while (i < this->parameters.size()) {
		s << *iterator << " "; // ?
		i++;
	}

	s << std::endl;

	return s.str();
}

Funcion::~Funcion() {

}
