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
	std::unordered_map<std::string, Variable>* GetTableSV(); // Creo que se ocupa acceder desde otras partes a tablaSV, si no luego quitamos esto
	void Insert(Variable); // Inserta una variable en la tabla hash.
	size_t RemoveValue(const std::string); // Elimina un valor de la tabla hash.
	std::unordered_map<std::string, Variable>::const_iterator Search(const std::string);
	void Update(std::string, const std::string); // 
	void ShowTable(); // Muestra todos los elementos de la tablaSV.
	std::unordered_map<std::string, Variable>::const_iterator GetEnd();
	~TablaVariables(); // Destructor


};


#endif // !TABLAVARIABLES_H