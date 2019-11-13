// Analizador_Texto.h
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores
// Descripción: Implementación de la clase "Analizador_Texto".

#include"Analizador_Texto.h"

Analizador_Texto::Analizador_Texto(std::string direccion) {
	this->codigo = std::ifstream(direccion.c_str());
	this->funcion = nullptr;
	this->num_linea = 0;
	this->variable = nullptr;
	this->linea = "";
	this->posicion_en_linea = 0;
	// this->anlizardos_S = new anala...(this);
}

int Analizador_Texto::getNum_linea() { return this->num_linea; }

void Analizador_Texto::setNum_linea(int num_linea) { this->num_linea = num_linea; }

bool Analizador_Texto::limitador() {
	char x = this->linea[posicion_en_linea];
	return x == ';' || x == '(' || x == ')' || x == '{' || x == '}' || x == ',';
}

std::string Analizador_Texto::next() {

	std::string resultado = "";			// resultado

	if (posicion_en_linea == linea.length())		// verifica si estoy en el final de la linea 
		return "-end-";					            // valor default para saber que tengo que leer otra linea del archivo

	while (linea[posicion_en_linea] == ' ') {	// recorre los espacios en blanco de la linea hasta llegar a una palabra
		if (posicion_en_linea == linea.length()) 
			return "-end-";				
		posicion_en_linea++;
	}

	if (limitador()) {  // me fijo si es ; ( ) { } ,
		resultado = linea[posicion_en_linea];
		posicion_en_linea++;	
	}

	else {
		while (linea[posicion_en_linea] != ' ' && !limitador()) {  // este es en caso de tener que leer un nombre o tipo
			if (posicion_en_linea == linea.length())
				return resultado;
			resultado += linea[posicion_en_linea];
			posicion_en_linea++;
		}
	}
	return resultado;
}

std::string Analizador_Texto::siguiente_palabra() {

	std::string result;  // resultado

	while (!codigo.eof() && linea == "") {  // llegar hasta una linea no vacia
		this->posicion_en_linea = 0;
		this->num_linea++;
		std::getline(codigo, linea, '\n');
	}
	if (codigo.eof()) { return "-end-"; }

	result = next();

	while (result == "-end-") {
		linea = "";
		while (!codigo.eof() && linea == "") {	// llegar hasta una linea no vacia
			this->posicion_en_linea = 0;
			this->num_linea++;
			std::getline(codigo, linea, '\n');
		}
		if (codigo.eof()) { return "-end-"; }
		result = next();
	}

	return result;
}

int Analizador_Texto::tipo(std::string word) {
	if (word == "int") return INT;
	if (word == "float") return FLOAT;
	if (word == "if") return IF;
	if (word == "string") return STRING;
	if (word == "void") return VOID;
	if (word == "return") return RETURN;
	if (word == "while") return WHILE;
	return NO_EXISTE;
}

void Analizador_Texto::analiza() {
	

}

Analizador_Texto::~Analizador_Texto() {}