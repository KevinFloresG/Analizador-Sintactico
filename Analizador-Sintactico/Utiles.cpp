// Utiles.h
// Autores: Javier Amador, Philippe Gairaud, Kevin Flores.
// Descripcion: Implementacion de la clase "Utiles".

#include "Utiles.h"
#include <sstream>

bool Utiles::IsInt(std::string s) {
	std::string::iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool Utiles::IsFloat(std::string s) {
	std::string::iterator it = s.begin();
	int pointCounter = 0;
	bool numbers = false;
	bool point = false;
	while (it != s.end()) {

		if (pointCounter > 1)
			return false;

		if (isdigit(*it))
			numbers = true;
		else {
			if (*it == '.') {
				point = true;
				pointCounter++;
			}
			else
				return false;
		}
		++it;
	}
	return numbers && point;
}

bool Utiles::IsString(std::string s) {
	std::string::iterator it = s.begin();
	int contadorComillas = 0;
	while (it != s.end()) {
		if (*it == '\"')
			contadorComillas++;
		++it;
	}

	if (contadorComillas == 2)
		return true;
	else
		return false;
}

int Utiles::CountChar(std::string str, char c){

	int count = 0;
	for (int i = 0; i < str.length(); i++){
		if (str.at(i) == c)
			count++;
	}

	return count;
}

std::string Utiles::convertirString(int x) {
	std::stringstream ss;
	ss << x;
	std::string num = ss.str();
	return num;
}