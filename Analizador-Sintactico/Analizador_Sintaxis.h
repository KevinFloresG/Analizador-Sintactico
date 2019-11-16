// Analizador_Sintaxis.h
// Autores: Javier Amador, Philippe Gairaud, Kevin Flores.
// Descripcion: Definicion de la clase "Analizador_Sintaxis".

#include <iostream>
#include <sstream>
#include "TablaFunciones.h"
#include "TablaVariables.h"
#include "Utiles.h"

#ifndef ANALIZADOR_SINTAXIS_H
#define ANALIZADOR_SINTAXIS_H


class Analizador_Texto; // Fwd de la clase


class Analizador_Sintaxis {
private:
	TablaVariables* variable_table;
	TablaFunciones* function_table;
	Analizador_Texto* text_analyzer;
	std::list<std::string>* error_list; // Lista donde se almacenaran los errores
public:
	// Javier: Puede que algunos métodos necesiten cambiarse o que al final no se use
	Analizador_Sintaxis();
	Analizador_Sintaxis(Analizador_Texto*);
	void SetVariableTable(TablaVariables*);
	TablaVariables* GetVariableTable();
	TablaFunciones* GetFunctionTable();
	void SetText_Analyzer(Analizador_Texto*);
	bool CheckVariable(std::string, Variable, int);
	bool CheckVariableDeclaration(Variable, int);
	bool CheckFunctionDeclaration(Funcion, int);
	bool CheckVariableCall(std::string, Variable, int); // Recibe un scope, una variable, y la linea en la que se llama
	bool CheckIfVariableIsValid(std::string, std::string, int); // Recibe el nombre de la variable, el nombre del tipo y una linea
	void AddError(std::string s);
	void ShowErrorList();
	bool CheckValidReturnType(std::string, std::list<std::string>&, int);
	~Analizador_Sintaxis();
};

#endif // !ANALIZADOR_SINTAXIS_H