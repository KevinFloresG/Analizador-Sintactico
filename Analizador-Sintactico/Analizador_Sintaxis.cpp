// Analizador_Sintaxis.cpp
// Authors: Javier Amador, Philippe Gairaud, Kevin Flores.
// Description: Implementation of the class "Analizador_Sintaxis".

#include "Analizador_Sintaxis.h"
#include "Analizador_Texto.h"

// Constructor
Analizador_Sintaxis::Analizador_Sintaxis() {
	this->variable_table = new TablaVariables();
	this->function_table = new TablaFunciones();
	this->functionToAnalyze = nullptr;
	this->variableToAnalyze = nullptr;
	this->text_analyzer = nullptr;
}

Analizador_Sintaxis::Analizador_Sintaxis(Analizador_Texto* analyzer) {
	this->variable_table = new TablaVariables();
	this->function_table = new TablaFunciones();
	this->text_analyzer = analyzer;
	this->functionToAnalyze = text_analyzer->GetFunction();
	this->variableToAnalyze = text_analyzer->GetVariable();

}

void Analizador_Sintaxis::SetVariableTable(TablaVariables* vTable){
	if (vTable != nullptr)
		this->variable_table = vTable;
}

TablaVariables* Analizador_Sintaxis::GetVariableTable() {
	return variable_table;
}

TablaFunciones* Analizador_Sintaxis::GetFunctionTable() {
	return function_table;
}

// Setter of text_analyzer
void Analizador_Sintaxis::SetText_Analyzer(Analizador_Texto* analyzer) {
	if (analyzer != nullptr)
		this->text_analyzer = analyzer;
}

void Analizador_Sintaxis::SetFunctionTA(Funcion* fun){
	delete functionToAnalyze;
	this->functionToAnalyze = fun;
}

void Analizador_Sintaxis::SetVariableTA(Variable* var){
	delete variableToAnalyze;
	this->variableToAnalyze = var;
}

Funcion* Analizador_Sintaxis::GetFunctionTA(){
	return functionToAnalyze;
}

Variable* Analizador_Sintaxis::GetVariableTA(){
	return variableToAnalyze;
}

// Javier: 
// El siguiente método requiere cambios para reflejar mejor nuestra manera de lidiar con errores.
// Este método es como un prototipo o apenas la primera versión.
// Parece que van a quedar bien chanchos.
bool Analizador_Sintaxis::CheckVariableCall(Variable toCheck,int line){

	const std::string key = toCheck.GetId();
	std::unordered_map<std::string, Variable>::const_iterator resultado = this->variable_table->Search(key);
	// En caso de no existir el error sería que la variable no está definida
	if (resultado == this->variable_table->GetEnd()) {
		std::cout << "Error - Linea " << line << " : La variable " << key << " no esta definida" << std::endl;
		return false;
	}

	// El orden puede alterarse
	else {

		// Se verifica que el alcance sea correcto
		if (resultado->second.GetScope() != toCheck.GetScope() && resultado->second.GetScope() != "Global") {

			std::cout << "Error - Linea " << line << " : La variable " << key << " no tiene ese alcance" << std::endl;

			return false;
		}
		else // Se verifica que los tipos coincidan
			if (resultado->second.GetType() != toCheck.GetType()) {

				std::cout << "Error - Linea " << line << " : El tipo de la variable " << key << " es incorrecto" << std::endl;
				return false;

			}
			else // Si los tipos coincidieron y el valor coincide con el en caso de ser diferente se actualiza en la tabla
				if (resultado->second.GetValue() != toCheck.GetValue()) {
					// Probablemente falta comprobar que el valor sea valido a través de un método tipo
					// esInt y esFloat 
					this->variable_table->Update(toCheck.GetValue(), key);
				}

	}

	return true;
}

void Analizador_Sintaxis::Update(){
	delete variableToAnalyze, functionToAnalyze;
	this->functionToAnalyze = this->text_analyzer->GetFunction();
	this->variableToAnalyze = this->text_analyzer->GetVariable();
}

// Destructor
Analizador_Sintaxis::~Analizador_Sintaxis() {
	delete variable_table;
	delete function_table;
}