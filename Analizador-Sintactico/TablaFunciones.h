// TablaFunciones.h
// Autores: Javier Amador, Philippe Gairaud, Kevin Flores.
// Descripci�n: Definici�n de la clase "TablaFunciones".

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Funcion.h"

#ifndef TABLAFUNCIONES_H
#define TABLAFUNCIONES_H


class TablaFunciones {
private:
	std::unordered_map<std::string, Funcion>* tablaSF; // Tabla Hash/de S�mbolos para las funciones.
													   // Creo que solo esto ser�a de atributos igualmente.
public:
	TablaFunciones(); // Constructor
	std::unordered_map<std::string, Funcion>* getTableSF(); // Lo mismo que puse en T. Variables.
	void Insertar(Funcion); // Inserta una funcion en la tabla hash.
	size_t Eliminar(const std::string); // Elimina un valor de la tabla hash.
	std::unordered_map<std::string, Funcion>::const_iterator Buscar(const std::string); // Busca elemento y devuelve iterador
	/*Pendiente*/void Actualizar(Funcion, std::string); // Lo mismo que puse en T.Variables.
	void MostrarTabla(); // Muestra todos los elementos de la tablaSF.
	~TablaFunciones(); // Destructor

};


#endif // !TABLAFUNCIONES_H