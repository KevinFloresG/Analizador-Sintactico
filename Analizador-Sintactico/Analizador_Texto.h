// Analizador_Texto.h
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores
// Descripci�n: Definici�n de la clase "Analizador_Texto", se encaargar� de leer el txt con el codigo y generar 
// objetos que ser�n analizados por el "Analizador_Sintax".

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

class Analizador_Sintaxis; 

class Analizador_Texto {
private:

	Variable* variable;
	Funcion* funcion;
	Analizador_Sintaxis* analizador_sintax;
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
	
	Analizador_Texto(std::string);
	int getNum_linea();
	std::string siguiente_palabra();
	void setNum_linea(int);
	~Analizador_Texto();
	void analiza();
	void trabaja();
	void SetSyntaxAnalyzer(Analizador_Sintaxis*);
	void SetVariable(Variable*);
	void SetFunction(Funcion*);
	Variable* GetVariable();
	Funcion* GetFunction();
};

#endif // !ANALIZADOR_TEXTO_H


