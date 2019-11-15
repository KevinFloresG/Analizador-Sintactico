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
	//Funcion* functionToAnalyze; // Javier: Esto y la Variable no sé que tan necesario es aquí, lo pongo más que nada por 
	//Variable* variableToAnalyze;// que hablando ahora quedamos de que esto iba a ser como un tipo de Observer
	std::list<std::string>* error_list; // Lista donde se almacenaran los errores
public:
	// Javier: Puede que algunos métodos necesiten cambiarse o que al final no se use
	Analizador_Sintaxis();
	Analizador_Sintaxis(Analizador_Texto*);
	void SetVariableTable(TablaVariables*);
	TablaVariables* GetVariableTable();
	TablaFunciones* GetFunctionTable();
	void SetText_Analyzer(Analizador_Texto*);
	//void SetFunctionTA(Funcion*);
	//void SetVariableTA(Variable*);
	//Funcion* GetFunctionTA();
	//Variable* GetVariableTA();
	bool CheckFunction(Funcion, int);
	bool CheckVariable(std::string, Variable, int);
	bool CheckVariableDeclaration(Variable, int);
	bool CheckFunctionDeclaration(Funcion, int);
	bool CheckVariableCall(std::string, Variable, int); // Recibe un scope, una variable, y la linea en la que se llama
	bool CheckFunctionCall(Funcion, int); // Pendiente
	bool CheckIfVariableIsValid(std::string, std::string, int); // Recibe el nombre de la variable, el nombre del tipo y una linea
	void AddError(std::string s);
	void ShowErrorList();
	void Update(); // Probablemente no lo acabemos usando
	~Analizador_Sintaxis();

};

#endif // !ANALIZADOR_SINTAXIS_H