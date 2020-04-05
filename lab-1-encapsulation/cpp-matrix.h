namespace cpp {
	class Matrix {
		double _a1, _a2, _a3, _a4;
	public:
		Matrix();

		Matrix(double A1, double A2, double A3, double A4);

		void printMatrix();

		Matrix operator+ (const Matrix& B) const;

		Matrix operator- (const Matrix& B) const;

		Matrix operator* (const Matrix& B) const;

		Matrix operator* (const double& multiplier) const;

		double getDeterminate() const;
		
		static double getDeterminateStatic(const Matrix& A);
	};
}