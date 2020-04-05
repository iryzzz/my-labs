#include "rectangle.h"
#include "figure.h"
#include "point.h"
#include "math.h"
#include <iostream>
#include "ellipse.h"

Ellipse::Ellipse(double x, double y, double rl, double rh): _r1(rl), _r2(rh), _a(x, y) {}

double Ellipse::getSquare() const {
	return (3.14 * _r2 * _r1);
}

double Ellipse::getPerimeter() const {
	return (4* (3.14 * _r2 * _r1 + (_r2 - _r1))/(_r2+_r1));
}

std::shared_ptr<Figure> Ellipse::getRectangle() const {
	return std::shared_ptr<Rectangle>(new Rectangle(_r1+_a.getX(), _a.getX()-_r1, _a.getY()+_r2, _a.getY()-_r2));
}

void Ellipse::print() const {
	std::cout << "Ellipse is based on point" <<"("<<_a.getX()<< "," << _a.getY() << ")" << std::endl; 
	std::cout << "First radius: = " << _r2 << std::endl;
	std::cout << "Second radius: = " << _r1 << std::endl;
}

bool Ellipse::equals(const Figure& obj) const {
	auto copy = dynamic_cast<const Ellipse*>(&obj);
	if (copy == nullptr) return false;
	if ((_r2 != copy->_r2) || (_r1 != copy->_r1)) return false;
	return true;
}
