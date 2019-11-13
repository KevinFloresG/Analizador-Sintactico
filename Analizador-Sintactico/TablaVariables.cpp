// TablaVariables.cpp
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores
// Descripción: Implementación de la clase "TablaVariables"

#include "TablaVariables.h"

TablaVariables::TablaVariables(){
	this->tablaSV = new std::unordered_map<std::string, Variable>();
}

std::unordered_map<std::string, Variable>* TablaVariables::getTableSV(){
	return tablaSV;
}

void TablaVariables::Insertar(Variable var) {

	const std::string key = var.getId(); // Se requiere que la llave sea constante
	auto registro = std::make_pair(key, var);
	tablaSV->insert(registro);

}

size_t TablaVariables::Eliminar(const std::string key){
	return tablaSV->erase(key); // Retorna 1 si eliminó el elemento, 0 si no existía.
}

std::unordered_map<std::string, Variable>::const_iterator TablaVariables::Buscar(const std::string key){
	return tablaSV->find(key); // Retorna un interador al elemento elegido o a end en caso de no hayar el elemento
}

void TablaVariables::Actualizar(Variable var, std::string key){
	//PENDIENTE
}

void TablaVariables::MostrarTabla(){

	std::cout << "La tabla contiene: " << std::endl;
	for (auto registro = tablaSV->begin(); registro != tablaSV->end(); ++registro)
		std::cout << registro->second.toString();
	std::cout << std::endl;

}

TablaVariables::~TablaVariables(){
	delete tablaSV;
}
