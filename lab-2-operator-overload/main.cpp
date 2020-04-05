#include <cstdio>
#include <stdlib.h>
#include <conio.h>
#include <libutils/io.h>
#include "bin-image.h"
#include <iostream>

extern bool trace = false;

using namespace std;

void main() {
	auto columns1 = utils::readInt("Enter amount of pixel columns in image 1: ", 0, 64);
	auto lines1 = utils::readInt("Enter amount of pixel lines in image 1: ", 0, 64);
	auto columns2 = utils::readInt("Enter amount of pixel columns in image 2: ", 0, 64);
	auto lines2 = utils::readInt("Enter amount of pixel lines in image 2: ", 0, 64);
	Image first(lines1,columns1), second(lines2,columns2);
	cout << "The first image:" << endl << first << endl 
		<< "The second image:" << endl << second << endl;
	Image res(2, 5);
	trace = true;
	res = first + second;
	cout << "first one + second one=" << endl << res << endl << endl;
	res = first * second;
	cout << "first one * second one=" << endl << res << endl << endl;
	res = !first;
	cout << "first one in negative will be:" << endl << res << endl << endl;
	auto x = (utils::readInt("Enter 0 or 1 ", 0, 1) ? true : false);
	res = first + x;
	cout << "first one + your value=" << endl << res << endl << endl;
	res = x + first;
	cout << "your value + first one=" << endl << res << endl << endl;
	res = first * x;
	cout << "first one * your value=" << endl << res << endl << endl;
	res = x * first;
	::trace = false;
	cout << "your value * first one=" << endl << res << endl << endl;
	auto fillFactor = first.getFillFactor();
	cout << "fill factor = " << fillFactor << endl;
}