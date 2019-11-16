// Analizador_Sintaxis.cpp
// Authors: Javier Amador, Philippe Gairaud, Kevin Flores.
// Description: Implementation of the class "Analizador_Sintaxis".

#include "Analizador_Sintaxis.h"
#include "Analizador_Texto.h"

// Constructor
Analizador_Sintaxis::Analizador_Sintaxis() {
	this->variable_table = new TablaVariables();
	this->function_table = new TablaFunciones();
	this->error_list = new std::list<std::string>();
	this->text_analyzer = nullptr;

}

Analizador_Sintaxis::Analizador_Sintaxis(Analizador_Texto* analyzer) {
	this->variable_table = new TablaVariables();
	this->function_table = new TablaFunciones();
	this->text_analyzer = analyzer;
	this->error_list = new std::list<std::string>();
}

void Analizador_Sintaxis::SetVariableTable(TablaVariables* vTable) {
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

bool Analizador_Sintaxis::CheckVariable(std::string scope, Variable var, int line){

	if(var.GetId()==""||var.GetId().empty())
		return false;
	// Si no hay tipo es una llamada a una variable
	if (var.GetType() == "" || var.GetType().empty())
		return CheckVariableCall(scope, var, line);
	else // En caso contrario es una declaración
		return CheckVariableDeclaration(var,line);

}

bool Analizador_Sintaxis::CheckFunctionDeclaration(Funcion toCheck, int line) {

	if (toCheck.GetId() == "")
		return false;

	const std::string key = toCheck.GetId();
	std::unordered_map<std::string, Funcion>::const_iterator resultado = this->function_table->Search(key);
	std::stringstream ss;
	ss << line;
	std::string num = ss.str();

	if (resultado != this->function_table->GetEnd()) {

		std::string mensaje = "Error - Linea " + num;
		std::string mensaje2 = " La funcion ya se había declarado " + key;
		this->error_list->push_back(mensaje + mensaje2);
		return false;
	}

	else {
		//Si es una funcion con la lista de parametros vacia la inserta de una vez
		if (toCheck.GetParameters().empty()) {
			this->function_table->Insert(toCheck);
			return true;
		}
		//Si la lista no esta vacia, verifica que los tipos sean correctos 
		else {
			for (std::string parametro : toCheck.GetParameters()) {
				std::string type = "";
				std::string name = "";
				int x = 0;
				while (parametro[x] != '+') {
					type += parametro[x];
					x++;
				}
				x++;
				while (x < parametro.length()) {
					name += parametro[x];
					x++;
				}
				Variable nueva(type, name, toCheck.GetId(), "");
				variable_table->Insert(nueva);
			}

		}

	}
	this->function_table->Insert(toCheck);
	return true;
}

bool Analizador_Sintaxis::CheckVariableDeclaration(Variable toCheck, int line) {
	// Javier: Asumiendo que si no consigue algo de esto lo manda como vacío
	// Preguntar a Kevin si sigue estando en analizador de texto lo que verificaba que hubiera nombre
	if (toCheck.GetType() == "" || toCheck.GetId() == "" || toCheck.GetScope() == "")
		return false;

	const std::string key = toCheck.GetId();
	std::unordered_map<std::string, Variable>::const_iterator resultado = this->variable_table->Search(key);
	std::stringstream ss;
	ss << line;
	std::string num = ss.str();

	// En caso de existir el error sería que la variable se esta intentando definir dos veces
	if (resultado != this->variable_table->GetEnd()) {
		// Javier: Lo siguiente se ve y esta bien feo, pero no se pudo hacer la suma de todo de un solo dentro
		// del push back
		std::string mensaje = "Error - Linea " + num;
		std::string mensaje2 = " La variable ya se habia declarado " + key;
		this->error_list->push_back(mensaje + mensaje2);
		return false;
	}

	// Caso en que a variable no esté en la tabla hash 
	else {
		// Si la variable tiene un valor entonces hay qur verificar que esté bien
		if (toCheck.GetValue() != "") {

			// Caso en el que el tipo es float
			if (toCheck.GetType() == "float") {

				// Caso de que no sea una cadena de valores
				if (Utiles::CountChar(toCheck.GetValue(),'+') == 1) {
					std::string val = toCheck.GetValue();
					val.pop_back();
					toCheck.SetValue(val);
					// Si el valor no esta compuesto de # o de # y al lo sumo un pto entonces es invalido
					if (!(Utiles::IsInt(toCheck.GetValue())) && !(Utiles::IsFloat(toCheck.GetValue()))) {
						std::string mensaje = "Error - Linea " + num;
						std::string mensaje2 = " El valor asignado no coincide con el tipo float de la variable " + key;
						this->error_list->push_back(mensaje + mensaje2);
						return false;
					}
				}
				else {

					std::string val = toCheck.GetValue();
					std::string miCopia = val;
					std::string delimiter = "+";
					int pos = 0;
					std::string actual = "";

					while ((pos = miCopia.find(delimiter)) != std::string::npos) {
						actual = miCopia.substr(0, pos);

						if (!Utiles::IsInt(actual) && !CheckIfVariableIsValid(actual, "float", line)
							&& !Utiles::IsFloat(actual)) {

							std::string mensaje = "Error - Linea " + num;
							std::string mensaje2 = " El valor asignado no coincide con el tipo float de la variable " + key;
							this->error_list->push_back(mensaje + mensaje2);
							return false;
						}

						miCopia.erase(0, pos + delimiter.length());
					}

					// Se elimina el + del final y se actualiza el value
					val.pop_back();
					toCheck.SetValue(val);
				}

			}
			else // Caso en el que el tipo es int 
				if (toCheck.GetType() == "int") {

					// Caso de que no sea una cadena de valores
					if (Utiles::CountChar(toCheck.GetValue(), '+') == 1) {
						std::string val = toCheck.GetValue();
						val.pop_back();
						toCheck.SetValue(val);
						// Si el valor no es un # entonces hay error
						if (!(Utiles::IsInt(toCheck.GetValue()))) {
							std::string mensaje = "Error - Linea " + num;
							std::string mensaje2 = " El valor asignado no coincide con el tipo int de la variable " + key;
							this->error_list->push_back(mensaje + mensaje2);
							return false;
						}
					}
					else {

						std::string val = toCheck.GetValue();
						std::string miCopia = val;
						std::string delimiter = "+";
						int pos = 0;
						std::string actual = "";

						while ((pos = miCopia.find(delimiter)) != std::string::npos) {
							actual = miCopia.substr(0, pos);

							if (!Utiles::IsInt(actual) && !CheckIfVariableIsValid(actual, "int", line)) {

								std::string mensaje = "Error - Linea " + num;
								std::string mensaje2 = " El valor asignado no coincide con el tipo int de la variable " + key;
								this->error_list->push_back(mensaje + mensaje2);
								return false;
							}

							miCopia.erase(0, pos + delimiter.length());
						}

						// Se elimina el + del final y se actualiza el value
						val.pop_back();
						toCheck.SetValue(val);
					}

				}
				else // Caso en el que tipo es string y el nuevo valor no
					if (toCheck.GetType() == "string" && !(Utiles::IsString(toCheck.GetValue()))) {

						std::string mensaje = "Error - Linea " + num;
						std::string mensaje2 = " El valor asignado no coincide con el tipo string de la variable " + key;
						this->error_list->push_back(mensaje + mensaje2);

						return false;
					}

		}

	}

	//En teoría si se llega a este punto todo esta bien, entonces la variable se agregaría a la tabla hash
	this->variable_table->Insert(toCheck);
	return true;
}


// El siguiente método puede requerir cambios sobre como trata los errores.
// Este método va a ocupar recibir en que scope se esta llamando a la variable
bool Analizador_Sintaxis::CheckVariableCall(std::string scope, Variable toCheck, int line) {

	// Se intenta conseguir la variable de la tabla hash
	const std::string key = toCheck.GetId();
	std::unordered_map<std::string, Variable>::const_iterator resultado = this->variable_table->Search(key);

	std::stringstream ss;
	ss << line;
	std::string num = ss.str();



	// En caso de no existir el error sería que la variable no está definida
	if (resultado == this->variable_table->GetEnd()) {
		std::string mensaje = "Error - Linea " + num;
		std::string mensaje2 = " No esta definida la variable " + key;
		this->error_list->push_back(mensaje + mensaje2);
		return false;
	}

	// Casos para cuando la variable exista en la tabla hash
	else {
		// Se verifica que el alcance sea correcto
		if (resultado->second.GetScope() != toCheck.GetScope()) {

			// Caso en el que la variable llega sin scope, y el scope de la tabla no coincida con Global o el actual
			if (toCheck.GetScope() == "") {

				if (resultado->second.GetScope() != scope && resultado->second.GetScope() != "Global") {
					std::string mensaje = "Error - Linea" + num;
					std::string mensaje2 = " Alcance incorrecto para la variable " + key;
					this->error_list->push_back(mensaje + mensaje2);
					return false;
				}

			}

			else // Caso en el que el scope de la variable llegue por algún motivo con scope
				 // y este sea diferente del que hay en la tabla
				if (toCheck.GetScope() != scope && resultado->second.GetScope() != "Global") {
					std::string mensaje = "Error - Linea " + num;
					std::string mensaje2 = " Alcance incorrecto para la variable " + key;
					this->error_list->push_back(mensaje + mensaje2);
					return false;
				}

		}
		//else  // Se verifica que los tipos coincidan
		if (toCheck.GetType() != "") {
			if (resultado->second.GetType() != toCheck.GetType()) {

				std::string mensaje = "Error - Linea " + num;
				std::string mensaje2 = " Tipo incorrecto para la variable " + key;
				this->error_list->push_back(mensaje + mensaje2);
				return false;
			}
		}

		else {
			if (resultado->second.GetValue() != toCheck.GetValue()) {

				if (toCheck.GetValue() != "") {

					// Caso en el que el tipo es float
					if (resultado->second.GetType() == "float") {

						// Caso de que no sea una cadena de valores
						if (Utiles::CountChar(toCheck.GetValue(), '+') == 1) {
							std::string val = toCheck.GetValue();
							val.pop_back();
							toCheck.SetValue(val);
							// Si el valor no esta compuesto de # o de # y al lo sumo un pto entonces es invalido
							if (!(Utiles::IsInt(toCheck.GetValue())) && !(Utiles::IsFloat(toCheck.GetValue()))) {
								std::string mensaje = "Error - Linea " + num;
								std::string mensaje2 = " El valor asignado no coincide con el tipo float de la variable " + key;
								this->error_list->push_back(mensaje + mensaje2);
								return false;
							}
						}
						else {

							std::string val = toCheck.GetValue();
							std::string miCopia = val;
							std::string delimiter = "+";
							int pos = 0;
							std::string actual = "";

							while ((pos = miCopia.find(delimiter)) != std::string::npos) {
								actual = miCopia.substr(0, pos);

								if (!Utiles::IsInt(actual) && !CheckIfVariableIsValid(actual, "float", line)
									&& !Utiles::IsFloat(actual)) {

									std::string mensaje = "Error - Linea " + num;
									std::string mensaje2 = " El valor asignado no coincide con el tipo float de la variable " + key;
									this->error_list->push_back(mensaje + mensaje2);
									return false;
								}

								miCopia.erase(0, pos + delimiter.length());
							}

							// Se elimina el + del final y se actualiza el value
							val.pop_back();
							toCheck.SetValue(val);
						}

					}
					else // Caso en el que el tipo es int 
						if (resultado->second.GetType() == "int") {

							// Caso de que no sea una cadena de valores
							if (Utiles::CountChar(toCheck.GetValue(), '+') == 1) {
								std::string val = toCheck.GetValue();
								val.pop_back();
								toCheck.SetValue(val);
								// Si el valor no es un # entonces hay error
								if (!(Utiles::IsInt(toCheck.GetValue()))) {
									std::string mensaje = "Error - Linea " + num;
									std::string mensaje2 = " El valor asignado no coincide con el tipo int de la variable " + key;
									this->error_list->push_back(mensaje + mensaje2);
									return false;
								}
							}
							else {

								std::string val = toCheck.GetValue();
								std::string miCopia = val;
								std::string delimiter = "+";
								int pos = 0;
								std::string actual = "";

								while ((pos = miCopia.find(delimiter)) != std::string::npos) {
									actual = miCopia.substr(0, pos);

									if (!Utiles::IsInt(actual) && !CheckIfVariableIsValid(actual, "int", line)) {

										std::string mensaje = "Error - Linea " + num;
										std::string mensaje2 = " El valor asignado no coincide con el tipo int de la variable " + key;
										this->error_list->push_back(mensaje + mensaje2);
										return false;
									}

									miCopia.erase(0, pos + delimiter.length());
								}

								// Se elimina el + del final y se actualiza el value
								val.pop_back();
								toCheck.SetValue(val);
							}

						}
					
						else { // Caso en el que tipo es string y el nuevo valor no
							bool x = !(Utiles::IsString(toCheck.GetValue()));
							if (resultado->second.GetType() == "string" && x) {

								std::string mensaje = "Error - Linea " + num;
								std::string mensaje2 = " El valor asignado no coincide con el tipo string de la variable " + key;
								this->error_list->push_back(mensaje + mensaje2);

								return false;
							}
						}
					// En caso de no darse ninguno de los errores anteriores entonces se actualiza el valor en la tabla
					this->variable_table->Update(toCheck.GetValue(), key);
				}
			}
		}
	}
	// Si se llega a este punto en teoría no hay problema con la llamada a la variable
	return true;
}

// Método auxiliar usado en CheckVariableCall y CheckVariableDeclaration cuando se le asignan valores a la variable
bool Analizador_Sintaxis::CheckIfVariableIsValid(std::string varId, std::string type, int line) {

	// Se intenta conseguir la variable de la tabla hash
	const std::string key = varId;
	std::unordered_map<std::string, Variable>::const_iterator resultado = this->variable_table->Search(key);

	std::stringstream ss;
	ss << line;
	std::string num = ss.str();

	// En caso de no existir el error sería que la variable no está definida
	if (resultado == this->variable_table->GetEnd()) {
		std::string mensaje = "Error - Linea " + num;
		std::string mensaje2 = " No esta definida la variable " + key;
		this->error_list->push_back(mensaje + mensaje2);
		return false;
	}
	else { // En caso de que si exista la variable

		// Si no coinciden los tipos
		if (type != resultado->second.GetType()) {
			std::string mensaje = "Error - Linea " + num;
			std::string mensaje2 = " No coincide el tipo de la variable " + key;
			this->error_list->push_back(mensaje + mensaje2);
			return false;
		}
		else // En caso de que no tenga valor la variable
			if (resultado->second.GetValue() == "") {

				std::string mensaje = "Error - Linea " + num;
				std::string mensaje2 = " No hay valor asignado a la variable " + key;
				this->error_list->push_back(mensaje + mensaje2);
				return false;

			}

	}

	// Si se llega aquí en teoría era válido
	return true;
}

// Agrega un error a la lista de errores
void Analizador_Sintaxis::AddError(std::string s) {
	if (!s.empty())
		this->error_list->push_back(s);
}

// Funcion que muestra la lista de errores
void Analizador_Sintaxis::ShowErrorList() {

	if (!error_list->empty()) {
		std::cout << "Lista de errores: " << std::endl << std::endl;
		std::list<std::string>::const_iterator iterator = this->error_list->begin();

		while (iterator != error_list->end()) {
			std::cout << *iterator << std::endl;
			iterator++;
		}
		std::cout << std::endl;
	}
	else
		std::cout << "No hay errores" << std::endl;

}

// Función usada para analizar si el valor de retorno de una función es correcto
bool Analizador_Sintaxis::CheckValidReturnType(std::string type, std::list<std::string> &values, int line) {

	std::stringstream ss;
	ss << line;
	std::string num = ss.str();
	std::list<std::string>::const_iterator iterator = values.begin();

	// Caso en que el tipo de retorno sea void pero la lista de valores esta vacía.
	if (type == "void" && !values.empty()) {
		std::string mensaje = "Error - Linea " + num;
		std::string mensaje2 = " El valor de retorno no coincide con el de la funcion ";
		this->error_list->push_back(mensaje + mensaje2);
		return false;
	}
	else // Caso que el tipo de retorno es int
		if (type == "int") {
			// Si la lista de valores esta vacia entonces hay error
			if (values.empty()) {
				std::string mensaje = "Error - Linea " + num;
				std::string mensaje2 = " El valor de retorno no coincide con el de la funcion ";
				this->error_list->push_back(mensaje + mensaje2);
				return false;

			} // Si la lista no esta vacía
			else {
				// Variable que se usara para comprobar variables
				std::unordered_map<std::string, Variable>::const_iterator resultado;

				while (iterator != values.end()) {

					if (!Utiles::IsInt(*iterator)) {

						resultado = this->variable_table->Search(*iterator);
						// En caso de no existir el error sería que la variable no está definida
						if (resultado == this->variable_table->GetEnd()) {
							std::string mensaje = "Error - Linea " + num;
							std::string mensaje2 = " Valor invalido para el retorno de la funcion ";
							this->error_list->push_back(mensaje + mensaje2);
							return false;
						} // Si existe pero el tipo no coincide
						else {
							if (resultado->second.GetType() != "int") {
								std::string mensaje = "Error - Linea " + num;
								std::string mensaje2 = " Valor invalido para el retorno de la funcion en la variable " + *iterator;
								this->error_list->push_back(mensaje + mensaje2);
								return false;

							}
						}
					}
					iterator++;
				}
			}
		}
		else // Caso de que el tipo sea float
			if (type == "float") {

				// Si la lista de valores esta vacia entonces hay error
				if (values.empty()) {
					std::string mensaje = "Error - Linea " + num;
					std::string mensaje2 = " El valor de retorno no coincide con el de la funcion";
					this->error_list->push_back(mensaje + mensaje2);
					return false;

				} // Si la lista no esta vacía
				else {
					// Variable que se usara para comprobar variables
					std::unordered_map<std::string, Variable>::const_iterator resultado;

					while (iterator != values.end()) {

						if (!Utiles::IsInt(*iterator) && !Utiles::IsFloat(*iterator)) {

							resultado = this->variable_table->Search(*iterator);
							// En caso de no existir el error sería que la variable no está definida
							if (resultado == this->variable_table->GetEnd()) {
								std::string mensaje = "Error - Linea " + num;
								std::string mensaje2 = " Valor invalido para el retorno de la funcion ";
								this->error_list->push_back(mensaje + mensaje2);
								return false;
							} // Si existe pero el tipo no coincide
							else {
								if (resultado->second.GetType() != "float") {
									std::string mensaje = "Error - Linea " + num;
									std::string mensaje2 = " Valor invalido para el retorno de la funcion en la variable " + *iterator;
									this->error_list->push_back(mensaje + mensaje2);
									return false;

								}
							}

						}
						iterator++;
					}
				}
			}
			else
				if (type == "string") {

					// Si la lista de valores esta vacia entonces hay error
					if (values.empty()) {
						std::string mensaje = "Error - Linea " + num;
						std::string mensaje2 = " El valor de retorno no coincide con el de la funcion";
						this->error_list->push_back(mensaje + mensaje2);
						return false;

					} // Si la lista no esta vacía
					else {
						// Variable que se usara para comprobar variables
						std::unordered_map<std::string, Variable>::const_iterator resultado;

						while (iterator != values.end()) {

							if (!Utiles::IsString(*iterator)) {

								resultado = this->variable_table->Search(*iterator);
								// En caso de no existir el error sería que la variable no está definida
								if (resultado == this->variable_table->GetEnd()) {
									std::string mensaje = "Error - Linea " + num;
									std::string mensaje2 = " Valor invalido para el retorno de la funcion ";
									this->error_list->push_back(mensaje + mensaje2);
									return false;
								} // Si existe pero el tipo no coincide
								else {
									if (resultado->second.GetType() != "string") {
										std::string mensaje = "Error - Linea " + num;
										std::string mensaje2 = " Valor invalido para el retorno de la funcion en la variable " + *iterator;
										this->error_list->push_back(mensaje + mensaje2);
										return false;
									}
								}
							}
							iterator++;
						}
					}

				}

	return true;
}

// Destructor
Analizador_Sintaxis::~Analizador_Sintaxis() {
	delete variable_table;
	delete function_table;
}