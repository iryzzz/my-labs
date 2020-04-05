#pragma once
#include "point.h"
#include "figure.h"

class Triangle : public Figure {
	Point _a, _b, _c;
public:
	Triangle(double, double, double, double, double, double);

	virtual double getSquare() const override;

	virtual double getPerimeter() const override;

	virtual std::shared_ptr<Figure> getRectangle() const override;

	virtual void print() const override;

	virtual bool equals(const Figure&) const override;
};