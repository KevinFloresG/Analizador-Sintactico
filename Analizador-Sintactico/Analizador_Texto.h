// Analizador_Texto.h
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores
// Descripción: Definición de la clase "Analizador_Texto", se encaargará de leer el txt con el codigo y generar 
// objetos que serán analizados por el "Analizador_Sintax".

#ifndef ANALIZADOR_TEXTO_H
#define ANALIZADOR_TEXTO_H

#include<fstream>

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
	Analizador_Sintaxis* analizador_sintax; // Javier: Se descomento esta linea y se hizo ptr
	int num_linea;
	int posicion_en_linea;
	std::string linea;
 
	std::ifstream codigo;


	std::string next();
	bool limitador();
	bool es_nombre(std::string);
	bool es_valor(std::string);
	int tipo(std::string);
	
	std::list<std::string> lee_parametros_declaracion();
	std::list<std::string> lee_parametros_llamada();

public:
	Variable* variable;
	Funcion* funcion;
	Analizador_Texto(std::string);
	int getNum_linea();
	std::string siguiente_palabra();
	void setNum_linea(int);
	~Analizador_Texto();
	void analiza();
	void analiza_2();
	// Javier: Los siguientes métodos se agregaron por pensar que pueden ser necesarios, de no serlos se pueden quitar
	void SetSyntaxAnalyzer(Analizador_Sintaxis*);
	void Notify();

	void SetVariable(Variable*);
	void SetFunction(Funcion*);
	Variable* GetVariable();
	Funcion* GetFunction();
};

#endif // !ANALIZADOR_TEXTO_H


