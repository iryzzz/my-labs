namespace c {
	struct Matrix {
		double _a1=0, _a2=0, _a3=0, _a4=0;
	};

	Matrix setMatrix(double a1, double a2, double a3, double a4);

	void printMatrix (const Matrix* A);

	Matrix getSum (const Matrix* A, const Matrix* B);

	Matrix getDifference (const Matrix* A, const Matrix* B);

	Matrix getProduct (const Matrix* A, const Matrix* B);

	Matrix getProductFromNumber (const Matrix* A, const double multiplier);

	double getDeterminate (const Matrix* A);

}