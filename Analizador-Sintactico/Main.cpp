// Main.cpp
// Autores: Kevin Flores, Javier Amador, Philippe Gairaud.
// Descripción: Programa principal.

#include <iostream>
#include "Variable.h"
#include "TablaVariables.h"
#include "Analizador_Texto.h"
#include "Analizador_Sintaxis.h"

int main(int argc, char* argv[]) {
	
	Utiles::ShowFile("..//Texto.txt");
	Analizador_Texto a("..//Texto.txt");
	a.trabaja();
	a.analizador_sintax->ShowErrorList();


	system("pause");
	return 0;
}