#pragma once
#include "point.h"
#include "figure.h"

class Rectangle : public Figure {
private: 
	Point _a, _b, _c, _d;
public:
	Rectangle(double, double, double, double) noexcept;

	virtual double getSquare() const override;

	virtual double getPerimeter() const override;

	virtual std::shared_ptr<Figure> getRectangle() const override;

	virtual void print() const override;

	virtual bool equals(const Figure&) const override;
};