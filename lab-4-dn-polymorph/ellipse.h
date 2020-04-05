#pragma once
#include "point.h"
#include "figure.h"

class Ellipse : public Figure {
	Point _a;
	double _r1;
	double _r2;	
public:
	Ellipse(double, double, double, double);

	virtual double getSquare() const override;
	virtual double getPerimeter() const override;

	virtual std::shared_ptr<Figure> getRectangle() const override;

	virtual void print() const override;

	virtual bool equals(const Figure&) const override;
};