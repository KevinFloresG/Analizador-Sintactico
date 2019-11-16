// TablaVariables.cpp
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores
// Descripción: Implementación de la clase "TablaVariables"

#include "TablaVariables.h"

TablaVariables::TablaVariables() {
	this->tablaSV = new std::unordered_map<std::string, Variable>();
}

void TablaVariables::Insert(Variable var) {

	const std::string key = var.GetId(); // Se requiere que la llave sea constante
	auto registro = std::make_pair(key, var);
	tablaSV->insert(registro);

}

size_t TablaVariables::RemoveValue(const std::string key) {
	return tablaSV->erase(key); // Retorna 1 si eliminó el elemento, 0 si no existía.
}

std::unordered_map<std::string, Variable>::const_iterator TablaVariables::Search(const std::string key) {
	return tablaSV->find(key); // Retorna un interador al elemento elegido o a end en caso de no hayar el elemento
}

void TablaVariables::Update(std::string nValue, const std::string key) {
	std::unordered_map<std::string, Variable>::const_iterator resultado = Search(key);
	if (resultado == tablaSV->end())
		return; // Se puede pasar a Excepcion
	else {
		tablaSV->at(key).SetValue(nValue);
	}
}

void TablaVariables::ShowTable() {

	std::cout << "La tabla contiene: " << std::endl;
	for (auto registro = tablaSV->begin(); registro != tablaSV->end(); ++registro)
		std::cout << registro->second.ToString();
	std::cout << std::endl;

}

std::unordered_map<std::string, Variable>::const_iterator TablaVariables::GetEnd(){
	return tablaSV->end();
}

TablaVariables::~TablaVariables() {
	delete tablaSV;
}
