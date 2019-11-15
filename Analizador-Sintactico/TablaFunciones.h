// TablaFunciones.h
// Autores: Javier Amador, Philippe Gairaud, Kevin Flores.
// Descripción: Definición de la clase "TablaFunciones".

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Funcion.h"

#ifndef TABLAFUNCIONES_H
#define TABLAFUNCIONES_H


class TablaFunciones {
private:
	std::unordered_map<std::string, Funcion>* tablaSF; // Tabla Hash/de Símbolos para las funciones.
	// Creo que solo esto sería de atributos igualmente.
public:
	TablaFunciones(); // Constructor
	std::unordered_map<std::string, Funcion>* GetTableSF(); // Lo mismo que puse en T. Variables.
	void Insert(Funcion); // Inserta una funcion en la tabla hash.
	size_t RemoveValue(const std::string); // Elimina un valor de la tabla hash.
	std::unordered_map<std::string, Funcion>::const_iterator Search(const std::string); // Busca elemento y devuelve iterador
	void ShowTable(); // Muestra todos los elementos de la tablaSF.
	~TablaFunciones(); // Destructor

};


#endif // !TABLAFUNCIONES_H