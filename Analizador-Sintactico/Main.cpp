// Main.cpp
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Programa principal.

#include <iostream>
#include "Variable.h"
#include "TablaVariables.h"
#include "Analizador_Texto.h"
#include "Analizador_Sintaxis.h"

int main(int argc, char* argv[]) {
	

	// OJO, NO SE HA PROBADO CON FUNCIONES !!!

	Analizador_Sintaxis* miAnalizadorS = new Analizador_Sintaxis();


	Variable* var = new Variable("int","x","Global");
	Variable* var2 = new Variable("float", "y", "Global");
	Variable* var3 = new Variable("string", "z", "Global");
	Variable* var4 = new Variable("string", "x", "Local");
	Variable* var5 = new Variable("int", "z", "Local");

	TablaVariables* miTablaVariables = new TablaVariables();

	miTablaVariables->Insert(*var);
	miTablaVariables->Insert(*var2);
	miTablaVariables->Insert(*var3);


	miTablaVariables->ShowTable();

	// Se elimina un elemento

	std::cout << miTablaVariables->RemoveValue("z"); // Se muestra si se elimino (1) o no (0)

	std::cout << std::endl <<"Tabla tras eliminacion: " << std::endl;

	miTablaVariables->ShowTable();

	std::cout << std::endl << "Elemento conseguido via busqueda: " << std::endl;
	// Esto debería verificarse por si devuelve null o basura
	std::cout << miTablaVariables->Search("x")->second.ToString();
	std::cout << std::endl;


	// Javier: Prueba Corta de Análisis S.
	std::cout << "Probando el método de check variable call con una x como string y z que no existe" << std::endl << std::endl;
	miAnalizadorS->SetVariableTable(miTablaVariables);

	if (!miAnalizadorS->CheckVariableCall(*var4,22)) {
		std::cout << std::endl;
		std::cout << "LLamada a x incorrecta" << std::endl;
	}

	std::cout << std::endl;

	if (!miAnalizadorS->CheckVariableCall(*var5,23)) {
		std::cout << std::endl;
		std::cout << "LLamada a z incorrecta" << std::endl;
	}


	/*delete miTablaVariables;*/ // Analizador Sintaxis elimina esto
	delete var, var2, var3;


	// Javier: Lo siguiente se comentó porque yo no tengo ese archivo para correrlo

	//Analizador_Texto a("..//Texto.txt");
	//std::string s = a.siguiente_palabra();
	//while (s != "-end-")
	//{
	//	std::cout << s << std::endl;
	//	s = a.siguiente_palabra();
	//}


	system("pause");
	return 0;
}