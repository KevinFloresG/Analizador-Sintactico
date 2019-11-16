// Analizador_Texto.h
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores
// Descripción: Implementación de la clase "Analizador_Texto".

#include"Analizador_Texto.h"
#include"Analizador_Sintaxis.h"
#include"Utiles.h"

#include<list>

Analizador_Texto::Analizador_Texto(std::string direccion) {
	this->codigo = std::ifstream(direccion.c_str());
	this->alcance_actual.push("global");
	this->funcion = nullptr;
	this->num_linea = 0;
	this->variable = nullptr;
	this->linea = "";
	this->falta = true;
	this->posicion_en_linea = 0;
	this->analizador_sintax = new Analizador_Sintaxis(this);
}

int Analizador_Texto::getNum_linea() { return this->num_linea; }

void Analizador_Texto::setNum_linea(int num_linea) { this->num_linea = num_linea; }

bool Analizador_Texto::limitador() {
	char x = this->linea[posicion_en_linea];
	return x == ';' || x == '(' || x == ')' || x == '{' || x == '}' || x == ',' || x == '=' || x == '+' || x == '-' || x == '*' || x == '/';
}

std::string Analizador_Texto::next() {

	std::string resultado = "";			// resultado

	if (posicion_en_linea == linea.length())		// verifica si estoy en el final de la linea 
		return "-end-";					            // valor default para saber que tengo que leer otra linea del archivo

	while (linea[posicion_en_linea] == ' ' || linea[posicion_en_linea] == '\t') {		// recorre los espacios en blanco de la linea hasta llegar a una palabra
		if (posicion_en_linea == linea.length()-1) 
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

std::list<std::string> Analizador_Texto::lee_parametros_declaracion() {
	std::string lector = siguiente_palabra();
	std::string nombre = siguiente_palabra();
	std::list<std::string> resultado;
	while (lector != "{" && nombre != "{") {
		resultado.push_back(lector +"+"+nombre);
		siguiente_palabra();
		lector = siguiente_palabra();
		if (lector != "{") { nombre = siguiente_palabra(); }
	}
	return resultado;
}


std::list<std::string> Analizador_Texto::lee_parametros_llamada() {
	std::string lector = siguiente_palabra();
	std::list<std::string> resultado;
	while (lector != ")") {
		resultado.push_back(lector);
		lector = siguiente_palabra();
		if (lector != ")") {
			lector = siguiente_palabra();
		}
	}
	return resultado;
}

std::list<std::string> Analizador_Texto::lee_return() {
	std::string lector = siguiente_palabra();
	std::list<std::string> result;
	while (lector != ";" && lector != "}" && lector != "-end-") {
		result.push_back(lector);
		if (linea[posicion_en_linea] == '\0' || linea[posicion_en_linea] == ';' || 
			linea[posicion_en_linea] == '}') { break; }
		siguiente_palabra();
		lector = siguiente_palabra();
	}
	if (lector == "}") { posicion_en_linea--; }
	if (lector == "-end-") { this->falta = false; }
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

bool Analizador_Texto::es_nombre(std::string x) {
	if (es_valor(x)) { return false; }
	if (tipo(x) != NO_EXISTE) { return false; }
	posicion_en_linea--;
	if (limitador()) {
		posicion_en_linea++;
		return false;
	}
	posicion_en_linea++;
	return true;
}

bool Analizador_Texto::es_valor(std::string x) {
	return Utiles::IsFloat(x) || Utiles::IsString(x) || Utiles::IsInt(x);
}

std::string Analizador_Texto::values() {
	std::string result = "";
	std::list<std::string> valores = lee_return();
	for (std::string x : valores) {
		result += x;
		result += "+";
	}
	return result;
}

void Analizador_Texto::trabaja() {
	while (falta) {
		analiza();
	}
}

void Analizador_Texto::analiza() {

	std::string lector = siguiente_palabra(); // variable que va obteniendo las palabras del archivo

	while (lector == "}" || lector == ";") {
		lector = siguiente_palabra();
	}
	if (lector == "-end-") {
		this->falta = false;
		return;
	}
	int clausula = tipo(lector);

	if (clausula < NO_EXISTE) {
		if (clausula < IF) {
			std::string type = lector;
			lector = siguiente_palabra();
			std::string name = lector;
			lector = siguiente_palabra();
			if (lector == "=") {
				//lector = siguiente_palabra();
				lector = values();
				std::string value = lector;
				lector = siguiente_palabra();
				if (lector != ";") {
					std::string mensaje = "Error - Linea " + Utiles::convertirString(num_linea-1);
					std::string mensaje2 = " Falta el ; ";
					analizador_sintax->AddError(mensaje + mensaje2);
					posicion_en_linea -= lector.length();
				}
				// llamo a sintax
				if (variable) { delete variable; }
				variable = new Variable(type, name, alcance_actual.top(), value);
				analizador_sintax->CheckVariable(alcance_actual.top(), *variable, num_linea);
				return;
			}
			else {
				std::list<std::string> parameters = lee_parametros_declaracion();
				// llamo a sintax
				if (funcion) { delete funcion; }
				funcion = new Funcion(type, name, alcance_actual.top(), "");
				funcion->SetParameters(parameters);
				alcance_actual.push(funcion->GetId());
				analizador_sintax->CheckFunctionDeclaration(*funcion, num_linea);
				return;
			}
		}
		else {
			if (clausula != RETURN) {
				lector = "";
				while (lector != "{") { lector = siguiente_palabra(); }
				if (variable) { delete variable; }
				variable = new Variable("if/while", "", alcance_actual.top(), "");
				return;
			}
			else {
				std::list<std::string> return_values = lee_return();
				analizador_sintax->CheckValidReturnType(funcion->GetTipo(), return_values, num_linea);
				if (funcion) { delete funcion; }
				funcion = nullptr;
				if (alcance_actual.size() >= 1) {
					alcance_actual.pop();
				}
				return;
			}
		}
	}
	std::string name = lector;
	lector = siguiente_palabra();
	if (lector == "=") {
		//lector = siguiente_palabra();
		lector = values();
		std::string value = lector;
		lector = siguiente_palabra();
		if (lector != ";") {
			std::string mensaje = "Error - Linea " + Utiles::convertirString(num_linea-1);
			std::string mensaje2 = " Falta el ; ";
			analizador_sintax->AddError(mensaje + mensaje2);
			posicion_en_linea -= lector.length();
		}
		// llamo a sintax type ""
		if (variable) { delete variable; }
		variable = new Variable("", name, alcance_actual.top(), value);
		analizador_sintax->CheckVariable(alcance_actual.top(), *variable, num_linea);
		return;
	}
	else {
		std::list<std::string> parameters = lee_parametros_llamada();
		lector = siguiente_palabra();
		if (lector != ";") {
			std::string mensaje = "Error - Linea " + Utiles::convertirString(num_linea-1);
			std::string mensaje2 = " Falta el ; ";
			analizador_sintax->AddError(mensaje + mensaje2);
			posicion_en_linea -= lector.length();
		}
		// llamo a sintax type ""
		if (funcion) { delete funcion; }
		funcion = new Funcion("", name, alcance_actual.top(), "");
		funcion->SetParameters(parameters);
		alcance_actual.push(funcion->GetId());
		return;
	}
}

// Javier: Se agrego delete
Analizador_Texto::~Analizador_Texto() {
	if (variable) delete variable;
	if (funcion) delete funcion;
}

void Analizador_Texto::SetSyntaxAnalyzer(Analizador_Sintaxis* syntaxA){
	if(syntaxA!=nullptr)
		this->analizador_sintax = syntaxA;
}

void Analizador_Texto::SetVariable(Variable* var){
	this->variable = var;
}

void Analizador_Texto::SetFunction(Funcion* fun){
	this->funcion = fun;
}

Variable* Analizador_Texto::GetVariable(){
	return variable;
}

Funcion* Analizador_Texto::GetFunction(){
	return funcion;
}
