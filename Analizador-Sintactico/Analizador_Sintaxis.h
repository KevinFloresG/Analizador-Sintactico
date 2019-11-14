// Analizador_Sintaxis.h
// Authors: Javier Amador, Philippe Gairaud, Kevin Flores.
// Description: Definition of the class "Analizador_Sintaxis".

#include <iostream>
#include <sstream>
#include "TablaFunciones.h"
#include "TablaVariables.h"

#ifndef ANALIZADOR_SINTAXIS_H
#define ANALIZADOR_SINTAXIS_H


class Analizador_Texto; // Fwd de la clase


class Analizador_Sintaxis {
private:
	TablaVariables* variable_table;
	TablaFunciones* function_table;
	Analizador_Texto* text_analyzer;
	Funcion* functionToAnalyze; // Javier: Esto y la Variable no sé que tan necesario es aquí, lo pongo más que nada por 
	Variable* variableToAnalyze;// que hablando ahora quedamos de que esto iba a ser como un tipo de Observer
public:
	// Javier: Puede que algunos métodos necesiten cambiarse o que al final no se use
	Analizador_Sintaxis();
	Analizador_Sintaxis(Analizador_Texto*);
	void SetVariableTable(TablaVariables*);
	TablaVariables* GetVariableTable();
	TablaFunciones* GetFunctionTable();
	void SetText_Analyzer(Analizador_Texto*);
	void SetFunctionTA(Funcion*);
	void SetVariableTA(Variable*);
	Funcion* GetFunctionTA();
	Variable* GetVariableTA();
	bool CheckVariableCall(Variable);
	bool CheckFunctionCall(Funcion); // Pendiente
	void Update();
	~Analizador_Sintaxis();

};

#endif // !ANALIZADOR_SINTAXIS_H