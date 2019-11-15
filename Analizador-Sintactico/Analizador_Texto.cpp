// Analizador_Texto.h
// Autores: Javier Amador Delgado, Philippe Gairaud, Kevin Flores
// Descripción: Implementación de la clase "Analizador_Texto".

#include "Analizador_Texto.h"
#include "Analizador_Sintaxis.h"
#include"Utiles.h"

#include<list>

Analizador_Texto::Analizador_Texto(std::string direccion) {
	this->codigo = std::ifstream(direccion.c_str());
	this->funcion = nullptr;
	this->num_linea = 0;
	this->variable = nullptr;
	this->linea = "";
	this->posicion_en_linea = 0;
}

int Analizador_Texto::getNum_linea() { return this->num_linea; }

void Analizador_Texto::setNum_linea(int num_linea) { this->num_linea = num_linea; }

bool Analizador_Texto::limitador() {
	char x = this->linea[posicion_en_linea];
	return x == ';' || x == '(' || x == ')' || x == '{' || x == '}' || x == ',' || x == '=';
}

std::string Analizador_Texto::next() {

	std::string resultado = "";			// resultado

	if (posicion_en_linea == linea.length())		// verifica si estoy en el final de la linea 
		return "-end-";					            // valor default para saber que tengo que leer otra linea del archivo

	while (linea[posicion_en_linea] == ' ') {		// recorre los espacios en blanco de la linea hasta llegar a una palabra
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
	std::list<std::string> resultado;
	while (lector != "{") {
		resultado.push_back(lector);
		siguiente_palabra(); siguiente_palabra();
		lector = siguiente_palabra();
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

void Analizador_Texto::analiza() {
	bool tuvo_error_global = false;
	bool tuvo_error_momento = false;
	std::string lector = siguiente_palabra(); // variable que va obteniendo las palabras del archivo
	int clausula = tipo(lector); // guarda el numero constante asignado al tipo o clausula
	if (clausula != NO_EXISTE) {  // si es algun TIPO
		std::string type = lector; // guardo el TIPO de la variable o funcion
		lector = siguiente_palabra(); // avanzo a la siguiente palabra
		if (!es_nombre(lector)) {
			// si no es nombre hay un error...
			std::cout << "Variable sin Nombre" << num_linea << std::endl;
			tuvo_error_global = true;
			posicion_en_linea -= lector.length();
			lector = "";
		}
		std::string name = lector; // guardo el nombre, vacio en caso de que no haya leido un nombre.
		lector = siguiente_palabra();  // leo lo siguiente
		if (lector != "(" && lector != "=") {
			// si no es limitador hay un error...
			std::cout << "Falta el =." << num_linea << std::endl;
			tuvo_error_global = true;
			posicion_en_linea -= lector.length();
		}
		lector = siguiente_palabra();
		if (!es_valor(lector) && tipo(lector) > STRING) {
			// error si no es ni valor ni parametro..
			std::cout << "Variable sin valor." << num_linea << std::endl;
			tuvo_error_global = true;
			tuvo_error_momento = true;
		}
		if (!tuvo_error_momento) {
			if (es_valor(lector)) {
				std::string value = lector;
				lector = siguiente_palabra();
				if (lector != ";") {
					// Error de que falta el ;
					std::cout << "No hay ; en linea" << num_linea << std::endl;
				}
				if (!tuvo_error_global) {
					// envio lo creado a sintaxis.
					std::cout << type << "|" << name << "|" << value << "|" << "in if para el scope\n";
					std::cout << "envio lo creado a sintaxis.\n";
				}
				else {
					std::cout << type << "|" << name << "|" << value << "|" << "in if para el scope\n";
					std::cout << "No envio ni picha a sintaxis.\n";
				}
			}
			else if (tipo(lector) <= STRING) {


			}
		}
		else {
			// si hubo error que?
		}

	}

}

void Analizador_Texto::analiza_2() {

	std::string lector = siguiente_palabra(); // variable que va obteniendo las palabras del archivo
	int clausula = tipo(lector);

	if (clausula < NO_EXISTE) {
		if (clausula < IF) {
			std::string type = lector;
			lector = siguiente_palabra();
			std::string name = lector;
			lector = siguiente_palabra();
			if (lector == "=") {
				lector = siguiente_palabra();
				std::string value = lector;
				lector = siguiente_palabra();
				if (lector != ";") {
					std::cout << "Falta ; en linea -> " << num_linea << std::endl;
					posicion_en_linea -= lector.length();
				}
				std::string scope = "global";
				if (funcion) { scope = funcion->GetId(); }
				// llamo a sintax
				if (variable) { delete variable; }
				variable = new Variable(type, name, scope, value);
				return;
			}
			else {
				std::list<std::string> parameters = lee_parametros_declaracion();
				// llamo a sintax
				if (funcion) { delete funcion; }
				funcion = new Funcion(type, name, "empty");
				funcion->SetParameters(parameters);
				return;
			}
		}
		else {
			// va lo de while
		}
	}
	std::string name = lector;
	lector = siguiente_palabra();
	if (lector == "=") {
		lector = siguiente_palabra();
		std::string value = lector;
		lector = siguiente_palabra();
		if (lector != ";") {
			std::cout << "Falta ; en linea -> " << num_linea << std::endl;
			posicion_en_linea -= lector.length();
		}
		std::string scope = "global";
		if (funcion) { scope = funcion->GetId(); }
		// llamo a sintax type ""
		if (variable) { delete variable; }
		variable = new Variable("empty", name, scope, value);
		return;
	}
	else {
		std::list<std::string> parameters = lee_parametros_llamada();
		lector = siguiente_palabra();
		if (lector != ";") {
			std::cout << "Falta ; en linea -> " << num_linea << std::endl;
			posicion_en_linea -= lector.length();
		}
		// llamo a sintax type ""
		if (funcion) { delete funcion; }
		funcion = new Funcion("empty", name, "empty");
		funcion->SetParameters(parameters);
		return;
	}

}

//std::list<std::string> lee_parametros() {
//
//
//}

// Javier: Se agrego delete
Analizador_Texto::~Analizador_Texto() {
	delete variable, funcion;
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
