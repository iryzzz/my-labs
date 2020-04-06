#include <cstdio>
#include <stdlib.h>
#include "c-matrix.h"
#include "../libutils/include/libutils/io.h"
#include "cpp-matrix.h"
#include <iostream>

using namespace std;

inline void readElements (const string str, double &a1, double &a2, double &a3, double &a4);

void cSolution(const double* a1, const double* a2, const double* a3, const double* a4,
	const double* b1, const double* b2, const double* b3, const double* b4, const double* x);

void cppSolution(const double& a1, const double& a2, const double& a3, const double& a4,
	const double& b1, const double& b2, const double& b3, const double& b4, const double& x);

int main () {
	double a1=0, a2=0, a3=0, a4=0, b1=0, b2=0, b3=0, b4=0;
	readElements("Enter the A matrix", a1, a2, a3, a4);
	readElements("Enter the B matrix", b1, b2, b3, b4);
	double x = utils:: readDouble("Enter the multiplier for A*x operation", -255, 255);
	cppSolution(a1, a2, a3, a4, b1, b2, b3, b4, x);
	cSolution(&a1, &a2, &a3, &a4, &b1, &b2, &b3, &b4, &x);
}

void readElements(const string str, double &a1, double &a2, double &a3, double &a4) {
	cout << str << endl;
	a1 = utils::readDouble("Enter the [1][1] element: ", -99.0, 99.0);
	a2 = utils::readDouble("Enter the [1][2] element: ", -99.0, 99.0);
	a3 = utils::readDouble("Enter the [2][1] element: ", -99.0, 99.0);
	a4 = utils::readDouble("Enter the [2][2] element: ", -99.0, 99.0);
}

void cSolution(const double *a1, const double *a2, const double *a3, const double *a4,
	const double *b1, const double* b2, const double* b3, const double* b4, const double* x) {
	c::Matrix A = c::setMatrix(*a1, *a2, *a3, *a4);
	c::Matrix B = c::setMatrix(*b1, *b2, *b3, *b4);
	c::Matrix res;
	printf("C realisation:\n");
	res = c::getSum(&A, &B);
	printf("A+B=\n");
	c::printMatrix(&res);
	printf("\n");
	res = c::getDifference(&A, &B);
	printf("A-B=\n");
	c::printMatrix(&res);
	printf("\n");
	res = c::getProduct(&A, &B);
	printf("A*B=\n");
	c::printMatrix(&res);
	printf("\n");
	res = c::getProductFromNumber(&A, *x);
	printf("A*x=\n");
	c::printMatrix(&res);
	printf("\n");
	double det = c::getDeterminate(&A);
	printf("detA=%f\n", det);
	printf("\n");
}

void cppSolution(const double& a1, const double& a2, const double& a3, const double& a4,
	const double& b1, const double& b2, const double& b3, const double& b4, const double& x){
	cpp::Matrix A(a1, a2, a3, a4);
	cpp::Matrix B(b1, b2, b3, b4);
	cpp::Matrix res;
	cout << "C++ realisation:" << endl;
	res = A + B;
	cout << "A+B=" << endl;
	res.printMatrix();
	cout << endl;
	res = A - B;
	cout << "A-B=" << endl;
	res.printMatrix();
	cout << endl;
	res = A * B;
	cout << "A*B=" << endl;
	res.printMatrix();
	cout << endl;
	res = A * x;
	cout << "A*x=" << endl;
	res.printMatrix();
	cout << endl;
	double det = A.getDeterminate();
	cout << "detA=" << A.getDeterminate() << endl<<"(static) detA="<<cpp::Matrix::getDeterminateStatic(A)<<endl<<endl;
} 