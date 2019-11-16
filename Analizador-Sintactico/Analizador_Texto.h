// Analizador_Texto.h
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores
// Descripción: Definición de la clase "Analizador_Texto", se encaargará de leer el txt con el codigo y generar 
// objetos que serán analizados por el "Analizador_Sintax".

#ifndef ANALIZADOR_TEXTO_H
#define ANALIZADOR_TEXTO_H

#include<fstream>
#include<stack>

#include"Funcion.h"
#include"Variable.h"

constexpr int INT = 1;
constexpr int FLOAT = 2;
constexpr int STRING = 3;
constexpr int VOID = 4;

constexpr int IF = 5;
constexpr int WHILE = 6;
constexpr int RETURN = 7;

constexpr int NO_EXISTE = 8;

class Analizador_Sintaxis; // Javier: Fwd de la clase

class Analizador_Texto {
private:

	Variable* variable;
	Funcion* funcion;
	 // Javier: Se descomento esta linea y se hizo ptr
	bool falta;
	int num_linea;
	int posicion_en_linea;
	std::string linea;
	std::stack<std::string> alcance_actual;
	std::ifstream codigo;

	std::string next();
	std::string values();
	bool limitador();
	bool es_nombre(std::string);
	bool es_valor(std::string);
	int tipo(std::string);
	std::list<std::string> lee_parametros_declaracion();
	std::list<std::string> lee_parametros_llamada();
	std::list<std::string> lee_return();

public:
	Analizador_Sintaxis* analizador_sintax;
	Analizador_Texto(std::string);
	int getNum_linea();
	std::string siguiente_palabra();
	void setNum_linea(int);
	~Analizador_Texto();
	void analiza();
	void trabaja();
	// Javier: Los siguientes métodos se agregaron por pensar que pueden ser necesarios, de no serlos se pueden quitar
	void SetSyntaxAnalyzer(Analizador_Sintaxis*);
	void SetVariable(Variable*);
	void SetFunction(Funcion*);
	Variable* GetVariable();
	Funcion* GetFunction();
};

#endif // !ANALIZADOR_TEXTO_H


