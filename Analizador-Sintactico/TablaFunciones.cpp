// TablaFunciones.cpp
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores
// Descripción: Implementación de la clase "TablaFunciones"

#include "TablaFunciones.h"

TablaFunciones::TablaFunciones() {
	this->tablaSF = new std::unordered_map<std::string, Funcion>();
}

std::unordered_map<std::string, Funcion>* TablaFunciones::GetTableSF() {
	return tablaSF;
}

void TablaFunciones::Insert(Funcion fun) {

	const std::string key = fun.GetId(); // Se requiere que la llave sea constante
	auto registro = std::make_pair(key, fun);
	tablaSF->insert(registro);

}

std::unordered_map<std::string, Funcion>::const_iterator TablaFunciones::GetEnd(){
	return tablaSF->end();
}

size_t TablaFunciones::RemoveValue(const std::string key) {
	return tablaSF->erase(key); // Retorna 1 si eliminó el elemento, 0 si no existía.
}

std::unordered_map<std::string, Funcion>::const_iterator TablaFunciones::Search(const std::string key) {
	return tablaSF->find(key); // Retorna un interador al elemento elegido o a end en caso de no hayar el elemento
}


void TablaFunciones::ShowTable() {

	std::cout << "La tabla contiene: " << std::endl;
	for (auto registro = tablaSF->begin(); registro != tablaSF->end(); ++registro)
		std::cout << registro->second.ToString();
	std::cout << std::endl;

}

TablaFunciones::~TablaFunciones() {
	delete tablaSF;
}

