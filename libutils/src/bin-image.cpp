#include <libutils/bin-image.h>
#include <stdio.h>
#include <stdlib.h>
#include <libutils/io.h>
#include <iostream>

extern bool trace;

using namespace std;

Image::Image(const int& lines, const int& columns) noexcept : _lines(lines),
_columns(columns), _pixel(new bool* [lines]) {
	//if (trace)
	//	cout << "ctor\n";
	for (int i = 0; i < lines; ++i) {
		_pixel[i] = new bool[columns];
	}
	for (int i = 0; i < lines; ++i) {
		for (int j = 0; j < columns; ++j) {
			_pixel[i][j] = (rand() % 2 < 1) ? false : true;
		}
	}
}

Image::Image(const Image& rhs) noexcept : _lines(rhs._lines),
_columns(rhs._columns), _pixel(new bool* [rhs._lines]), _fillFactor(rhs._fillFactor) {
	//if (trace)
	//	cout << "copy ctor\n";
	for (int i = 0; i < _lines; ++i) {
		_pixel[i] = new bool[_columns];
	}
	for (int i = 0; i < _lines; ++i) {
		for (int j = 0; j < _columns; ++j) {
			_pixel[i][j] = rhs._pixel[i][j];
		}
	}
}

Image& Image::operator=(const Image& rhs) noexcept {
	//if (trace)
	//	std::cout << "copy assign\n";
	if ((_lines == rhs._lines) && (_columns == rhs._columns)) {
		for (int i = 0; i < _lines; ++i) {
			for (int j = 0; j < _columns; ++j) {
				_pixel[i][j] = rhs._pixel[i][j];
			}
		}
		_fillFactor = rhs._fillFactor;
	}
	else {
		for (int i = 0; i < _lines; ++i) {
			delete[] _pixel[i];
		}
		delete[] _pixel;
		_columns = rhs._columns;
		_lines = rhs._lines;
		_fillFactor = rhs._fillFactor;
		_pixel = new bool* [_lines];
		for (int i = 0; i < _lines; ++i) {
			_pixel[i] = new bool[_columns];
		}
		for (int i = 0; i < _lines; ++i) {
			for (int j = 0; j < _columns; ++j) {
				_pixel[i][j] = rhs._pixel[i][j];
			}
		}
	}
	return *this;
}

//Image::Image(Image&& rhs) noexcept: _columns(rhs._columns), _lines(rhs._lines), 
//	_fillFactor(rhs._fillFactor), _pixel(rhs._pixel) {
//	if (trace)
//		std::cout << "move ctor\n";
//	rhs._pixel = nullptr;
//}
//
//Image& Image::operator=(Image&& rhs) noexcept {
//	if (trace)
//		std::cout << "move assign\n";
//	for (int i = 0; i < _lines; ++i) {
//		delete[] _pixel[i];
//	}
//	delete[] _pixel;
//	_columns = rhs._columns;
//	_lines = rhs._lines;
//	_fillFactor = rhs._fillFactor;
//	_pixel = rhs._pixel;
//	rhs._pixel = nullptr;
//	return *this;
//}

Image::~Image() noexcept {
	//if (trace)
	//	std::cout << "dtor\n";
	if (_pixel) {
		for (int i = 0; i < _lines; ++i) {
			delete[] _pixel[i];
		}
		delete[] _pixel;
	}
}

int Image::getLines() const noexcept {
	return _lines;
}

int Image::getColumns() const noexcept {
	return _columns;
}

Image& Image::operator+=(const Image& rhs) {
	try {
		if ((_lines != rhs._lines) || (_columns != rhs._columns)) {
			throw 7;
		}
		for (int i = 0; i < _lines; ++i) {
			for (int j = 0; j < _columns; ++j) {
				_pixel[i][j] = (_pixel[i][j] || rhs._pixel[i][j]);
			}
		}
		_fillFactor = -1;
	}
	catch (int i) {
		cout << "Error " << i << ": images with different size cannot be summarized, the result will be incorrect" << endl;
	}
	return *this;
}

Image& Image::operator+=(const bool& term) noexcept {
	for (int i = 0; i < _lines; ++i) {
		for (int j = 0; j < _columns; ++j) {
			_pixel[i][j] = (_pixel[i][j] || term);
		}
	}
	_fillFactor = -1;
	return *this;
}

Image& Image::operator*=(const Image& rhs) {
	try {
		if ((_lines != rhs._lines) || (_columns != rhs._columns)) {
			throw 8;
		}
		for (int i = 0; i < _lines; ++i) {
			for (int j = 0; j < _columns; ++j) {
				_pixel[i][j] = (_pixel[i][j] && rhs._pixel[i][j]);
			}
		}
		_fillFactor = -1;
	}
	catch (int i) {
		cout << "Error " << i << ": images with different size cannot be multiplied, the result will be incorrect" << endl;
	}
	return *this;
}

Image& Image::operator*=(const bool& multiplier) noexcept {
	for (int i = 0; i < _lines; ++i) {
		for (int j = 0; j < _columns; ++j) {
			_pixel[i][j] = (_pixel[i][j] && multiplier);
		}
	}
	_fillFactor = -1;
	return *this;
}

bool Image::operator==(const Image& rhs) const noexcept {
	bool isSame = true;
	if ((_lines == rhs._lines) && (_columns == rhs._columns)) {
		for (int i = 0; (i < _lines) && isSame; ++i) {
			for (int j = 0; (j < _columns) && isSame; ++j) {
				if (_pixel[i][j] != rhs._pixel[i][j]) {
					isSame = false;
				}
			}
		}
	}
	else {
		isSame = false;
	}
	return isSame;
}

bool Image::operator!=(const Image& rhs) const noexcept {
	bool isNotSame = true;
	if ((_lines != rhs._lines) && (_columns != rhs._columns)) {
		for (int i = 0; (i < _lines) && isNotSame; ++i) {
			for (int j = 0; (j < _columns) && isNotSame; ++j) {
				if (_pixel[i][j] == rhs._pixel[i][j]) {
					isNotSame = false;
				}
			}
		}
	}
	else {
		isNotSame = false;
	}
	return isNotSame;
}

const bool Image::operator()(const int& line, const int& column) const {
	try {
		if ((line > _lines) || (column > _columns)) {
			throw 404;
		}
		return _pixel[line][column];
	}
	catch (int i) {
		cout << "Error " << i << ": requested pixel does not founded";
		return nullptr;
	}
}

void Image::operator()(const int& line, const int& column, const bool& newValue) {
	try {
		if ((line > _lines) || (column > _columns)) {
			throw 404;
		}
		_pixel[line][column] = newValue;
		_fillFactor = -1;
	}
	catch (int i) {
		cout << "Error " << i << ": requested pixel does not founded";
	}
}

Image Image::operator!() noexcept {
	Image tmp(*this);
	for (int i = 0; i < _lines; ++i) {
		for (int j = 0; j < _columns; ++j) {
			tmp._pixel[i][j] = (tmp._pixel[i][j]) ? false : true;
		}
	}
	tmp._fillFactor = -1;
	return tmp;
}

double Image::getFillFactor() const noexcept {
	if (_fillFactor < 0) {
		int counter = 0;
		double size = (double)_lines * (double)_columns;
		for (int i = 0; i < _lines; ++i) {
			for (int j = 0; j < _columns; ++j) {
				if (_pixel[i][j]) {
					++counter;
				}
			}
		}
		_fillFactor = (counter / size);
	}
	return _fillFactor;
}

ostream& operator<<(ostream& out, const Image& rhs) noexcept {
	auto lines = rhs.getLines(), columns = rhs.getColumns();
	for (int i = 0; i < lines; ++i) {
		for (int j = 0; j < columns; ++j) {
			(rhs(i, j)) ? out << "X" : out << ".";
		}
		out << endl;
	}
	return out;
}

Image operator+(const Image& first, const Image& second) {
	Image tmp(first);
	tmp += second;
	return tmp;
}

Image operator+(const Image& rhs, const bool& term) {
	Image tmp(rhs);
	tmp += term;
	return tmp;
}

Image operator+(const bool& term, const Image& rhs) {
	Image tmp(rhs);
	tmp += term;
	return tmp;
}

Image operator*(const Image& first, const Image& second) {
	Image tmp(first);
	tmp *= second;
	return tmp;
}

Image operator*(const Image& rhs, const bool& multiplier) {
	Image tmp(rhs);
	tmp *= multiplier;
	return tmp;
}

Image operator*(const bool& multiplier, const Image& rhs) {
	Image tmp(rhs);
	tmp *= multiplier;
	return tmp;
}
