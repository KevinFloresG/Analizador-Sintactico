// Utiles.h
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores.
// Descripcion: Definición de la clase "Utiles", una clase con funciones simples que se ocupan pero no pertenecen a
// las demás clases.

#include <string>
#include <iterator>

#ifndef UTILES_H
#define UTILES_H

class Utiles {

public:
	static bool IsInt(std::string); // Funcion que revisa que un string este compuesto solo por números
	static bool IsFloat(std::string); // Funcion que revisa si un string podría ser un float
	static bool IsString(std::string); // Función que revisa que un string contenga " " (Ya que al recuperar del archivo)
									   // los strings se serían así: ""String"" !!! Falta probar esta y la de IsFloat que hizo Philippe
};

#endif //!UTILES_H
