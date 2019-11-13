// Main.cpp
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Programa principal.

#include <iostream>
#include "Variable.h"
#include "TablaVariables.h"

int main(int argc, char* argv[]) {

	// OJO, NO SE HA PROBADO CON FUNCIONES !!!

	Variable* var = new Variable("int","x","Global");
	Variable* var2 = new Variable("float", "y", "Global");
	Variable* var3 = new Variable("string", "z", "Global");

	TablaVariables* miTablaVariables = new TablaVariables();

	miTablaVariables->Insertar(*var);
	miTablaVariables->Insertar(*var2);
	miTablaVariables->Insertar(*var3);


	miTablaVariables->MostrarTabla();

	// Se elimina un elemento

	std::cout << miTablaVariables->Eliminar("z"); // Se muestra si se elimino (1) o no (0)

	std::cout << std::endl <<"Tabla tras eliminacion: " << std::endl;

	miTablaVariables->MostrarTabla();

	std::cout << std::endl << "Elemento conseguido via busqueda: " << std::endl;
	// Esto debería verificarse por si devuelve null o basura
	std::cout << miTablaVariables->Buscar("x")->second.toString();
	std::cout << std::endl;

	delete miTablaVariables;
	delete var, var2, var3;
	system("pause");
	return 0;
}