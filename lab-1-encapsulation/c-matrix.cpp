#include <cstdio>
#include "c-matrix.h"
#include <libutils/io.h>

c::Matrix c::setMatrix(const double a1, const double a2, const double a3, const double a4) {
	c::Matrix res;
	res._a1 = a1;
	res._a2 = a2;
	res._a3 = a3;
	res._a4 = a4;
	return res;
}

void c::printMatrix(const c::Matrix* A) {
	printf("%.3f \t%.3f\n%.3f\t%.3f\n", A->_a1, A->_a2, A->_a3, A->_a4);
}

c::Matrix c::getSum(const c::Matrix* const A, const c::Matrix* const B) {
	c::Matrix res;
	res._a1 = A->_a1 + B->_a1;
	res._a2 = A->_a2 + B->_a2;
	res._a3 = A->_a3 + B->_a3;
	res._a4 = A->_a4 + B->_a4;
	return res;
}

c::Matrix c::getDifference(const c::Matrix* A, const c::Matrix* B) {
	c::Matrix res;
	res._a1 = A->_a1 - B->_a1;
	res._a2 = A->_a2 - B->_a2;
	res._a3 = A->_a3 - B->_a3;
	res._a4 = A->_a4 - B->_a4;
	return res;
}

c::Matrix c::getProduct(const c::Matrix* A, const c::Matrix* B) {
	c::Matrix res;
	res._a1 = A->_a1 * B->_a1 + A->_a2 * B->_a3;
	res._a2 = A->_a1 * B->_a2 + A->_a2 * B->_a4;
	res._a3 = A->_a3 * B->_a1 + A->_a4 * B->_a3;
	res._a4 = A->_a3 * B->_a2 + A->_a4 * B->_a4;
	return res;
}

c::Matrix c::getProductFromNumber(const c::Matrix* A, const double multiplier) {
	c::Matrix res;
	res._a1 = A->_a1 * multiplier;
	res._a2 = A->_a2 * multiplier;
	res._a3 = A->_a3 * multiplier;
	res._a4 = A->_a4 * multiplier;
	return res;
}

double c::getDeterminate(const c::Matrix* A) {
	return(A->_a1 * A->_a4 - A->_a2 * A->_a3);
}
