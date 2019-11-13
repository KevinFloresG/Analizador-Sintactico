// TablaVariables.h
// Autores: Javier Amador, Philippe Gairaud, Kevin Flores.
// Descripción: Definición de la clase "TablaVariables".

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Variable.h"

#ifndef TABLAVARIABLES_H
#define TABLAVARIABLES_H


class TablaVariables {
private:
	std::unordered_map<std::string, Variable>* tablaSV; // Tabla Hash/de Símbolos para las variables
	// Creo que solo esto sería de atributos.
public:
	TablaVariables(); // Constructor
	std::unordered_map<std::string, Variable>* getTableSV(); // Creo que se ocupa acceder desde otras partes a tablaSV, si no luego quitamos esto
	void Insertar(Variable); // Inserta una variable en la tabla hash.
	size_t Eliminar(const std::string); // Elimina un valor de la tabla hash.
	std::unordered_map<std::string, Variable>::const_iterator Buscar(const std::string);
	/*Pendiente*/void Actualizar(Variable, std::string); // Esto en vez de recibir la variable puede recibir los atributos y luego armarlo.
	void MostrarTabla(); // Muestra todos los elementos de la tablaSV.
	~TablaVariables(); // Destructor

};


#endif // !TABLAVARIABLES_H