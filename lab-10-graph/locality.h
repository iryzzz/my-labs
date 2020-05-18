#pragma once
#include <iostream>

class Locality {
	char* _name;
	int _population;
	Locality() :_name(nullptr), _population(0) {}
public:
	Locality(char* _namecity, int count) :_name(_namecity), _population(count) {}

	Locality(const Locality&) = delete;

	Locality& operator= (const Locality& obj) {
		char* _name = new char[strlen(obj._name)];
		auto length = strlen(obj._name);
		for (auto i = 0; i < length; ++i) {
			_name[i] = obj._name[i];
		}
		delete[] _name;
		_name = _name;
		_population = obj._population;
		return *this;
	}

	bool operator==(const Locality& obj) {
		if ((!(strcmp((this->_name), (obj._name))) && (this->_population == obj._population)))
			return true;
		else
			return false;
	}

	bool operator!=(const Locality& obj) {
		if ((this->_name == obj._name) && (this->_population == obj._population))
			return false;
		else
			return true;
	}

	char* getName() const {
		return _name;
	}

	int getPopulation() const {
		return _population;
	}

};


std::ostream& operator << (std::ostream& out, const Locality* obj) noexcept {
	return out << "[" << obj->getName() << " | " << obj->getPopulation() << ']';
}
