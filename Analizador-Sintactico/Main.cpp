// Main.cpp
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Programa principal.

#include <iostream>
#include "Variable.h"
#include "TablaVariables.h"
#include "Analizador_Texto.h"
#include "Analizador_Sintaxis.h"

int main(int argc, char* argv[]) {
	
	Analizador_Sintaxis* miAnalizadorS = new Analizador_Sintaxis();


	Variable* var = new Variable("int", "x", "Global");
	Variable* var2 = new Variable("float", "y", "Global");
	Variable* var3 = new Variable("string", "z", "Global");
	Variable* var4 = new Variable("float", "w", "Global");
	var->SetValue("20+");
	var4->SetValue("803.982+");
	Variable* var5 = new Variable("", "z", "Local");

	TablaVariables* miTablaVariables = new TablaVariables();

	miTablaVariables->Insert(*var);
	miTablaVariables->Insert(*var2);
	miTablaVariables->Insert(*var3);


	miTablaVariables->ShowTable();

	//Se elimina un elemento

	std::cout << miTablaVariables->RemoveValue("z"); // Se muestra si se elimino (1) o no (0)

	std::cout << std::endl << "Tabla tras eliminacion: " << std::endl;

	miTablaVariables->ShowTable();

	std::cout << std::endl << "Elemento conseguido via busqueda: " << std::endl;
	//Esto debería verificarse por si devuelve null o basura
	std::cout << miTablaVariables->Search("x")->second.ToString();
	std::cout << std::endl;


	//Javier: Prueba Corta de Análisis S.

	std::cout << "Probando el método de check variable declaration con una w como float y llamada a z que no existe"
		<< std::endl << std::endl;
	miAnalizadorS->SetVariableTable(miTablaVariables);

	if (!miAnalizadorS->CheckVariableCall("Foo",*var4,22)) {
		std::cout << std::endl;
		std::cout << "LLamada a x incorrecta" << std::endl;
	}

	if (!miAnalizadorS->CheckVariable("",*var4, 22)) {
		std::cout << std::endl;
		std::cout << "Declaracion incorrecta de w" << std::endl;
	}


	std::cout << std::endl;

	if (!miAnalizadorS->CheckVariable("Foo", *var5, 23)) {
		std::cout << std::endl;
		std::cout << "LLamada a z incorrecta" << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;
	miAnalizadorS->ShowErrorList();
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << std::endl << "Tabla tras asignacion: " << std::endl;

	miTablaVariables->ShowTable();

	/*delete miTablaVariables;*/ // Analizador Sintaxis elimina esto
	delete var, var2, var3;
	std::cout << std::endl;

	//Analizador_Texto a("..//Texto.txt");
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();
	//a.analiza_2();


	system("pause");
	return 0;
}