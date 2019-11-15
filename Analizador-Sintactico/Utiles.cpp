// Utiles.h
// Authors: Javier Amador, Philippe Gairaud, Kevin Flores.
// Description: Implementation of the class "Utiles".

#include "Utiles.h"

bool Utiles::IsInt(std::string s) {
	std::string::iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool Utiles::IsFloat(std::string s) {
	// Javier: Falta verificar que solo pueda haber un pto, pero no es tan importante
	std::string::iterator it = s.begin();
	bool numbers = false;
	bool point = false;
	while (it != s.end()) {

		if (isdigit(*it))
			numbers = true;
		else
			return false;
		if (*it == '.')
			point = true;
		++it;
	}
	return numbers && point;
}

bool Utiles::IsString(std::string s) {
	std::string::iterator it = s.begin();

	int contadorComillas = 0;

	while (it != s.end()) {
		if (*it == '"')
			contadorComillas++;
		++it;
	}

	if (contadorComillas == 2)
		return true;
	else
		return false;
}