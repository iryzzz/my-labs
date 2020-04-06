#pragma once
#include <iostream>
#include <memory>

class Figure {
protected:
	Figure() = default;

	Figure(const Figure&) = default;

	Figure& operator=(const Figure&) = default;
public:
	virtual ~Figure() = default;

	virtual double getPerimeter() const = 0;

	virtual double getSquare() const = 0;

	virtual std::shared_ptr<Figure> getRectangle() const = 0;

	virtual bool equals(const Figure&) const = 0;

	virtual void print() const = 0;
};