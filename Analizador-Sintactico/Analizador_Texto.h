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

class Analizador_Texto {
private:
	//Analizador_Sintax analizador_sintax;
	int num_linea;
	int posicion_en_linea;
	std::string linea;
	Variable* variable; 
	Funcion* funcion;   
	std::ifstream codigo;


	std::string next();
	bool limitador();
	int tipo(std::string);
	void analiza();

public:
	Analizador_Texto(std::string);
	int getNum_linea();
	std::string siguiente_palabra();
	void setNum_linea(int);
	~Analizador_Texto();
};

#endif // !ANALIZADOR_TEXTO_H


