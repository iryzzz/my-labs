#include <stdio.h>
#include <libutils/io.h>
#include <iostream>
#include "cpp-matrix.h"

using namespace std;
using namespace cpp;

Matrix::Matrix():_a1(0), _a2(0),
		_a3(0), _a4(0) {}

Matrix::Matrix(double a1, double a2, double a3, double a4) : _a1 (a1), _a2(a2),
		_a3(a3), _a4(a4) {}

void Matrix::printMatrix() {
	cout.setf(ios::fixed);
	cout.fill('0');
	cout.width(2);
	cout.precision(2);
	cout << _a1 << "  " << _a2 << endl;
	cout << _a3 << "  " << _a4 << endl;
	cout.unsetf(ios::fixed);
}

Matrix Matrix::operator+ (const Matrix& B) const{
	Matrix tmp;
	tmp._a1 = _a1 + B._a1;
	tmp._a2 = _a2 + B._a2;
	tmp._a3 = _a3 + B._a3;
	tmp._a4 = _a4 + B._a4;
	return tmp;
}

Matrix Matrix::operator- (const Matrix& B) const{
	Matrix tmp;
	tmp._a1 = _a1 - B._a1;
	tmp._a2 = _a2 - B._a2;
	tmp._a3 = _a3 - B._a3;
	tmp._a4 = _a4 - B._a4;
	return tmp;
}

Matrix Matrix::operator* (const Matrix& B) const{
	Matrix tmp;
	tmp._a1 = _a1 * B._a1 + _a2 * B._a3;
	tmp._a2 = _a1 * B._a2 + _a2 * B._a4;
	tmp._a3 = _a3 * B._a1 + _a4 * B._a3;
	tmp._a4 = _a3 * B._a2 + _a4 * B._a4;
	return tmp;
}

Matrix Matrix::operator* (const double& multiplier) const{
	Matrix tmp;
	tmp._a1 = _a1 * multiplier;
	tmp._a2 = _a2 * multiplier;
	tmp._a3 = _a3 * multiplier;
	tmp._a4 = _a4 * multiplier;
	return tmp;
}

double Matrix::getDeterminate() const{
	return(_a1 * _a4 - _a2 * _a3);
}

double Matrix::getDeterminateStatic(const Matrix& A){
	return(A._a1 * A._a4 - A._a2 * A._a3);
}