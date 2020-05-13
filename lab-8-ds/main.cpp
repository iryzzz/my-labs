#include "ordered-vector.h"
#include "unordered-set.h"
#include <cstdlib>
#include <iostream>
#include "libutils/io.h"
#include <chrono>

using namespace std;

int main() {
	UnorderedSet<string> vector;
	{
		vector.insert("Mother");
		vector.insert("Father");
		vector.insert("Sister");
		vector.insert("Brother");
	}
	vector.print();;
	vector.remove("Brother");
	vector.print();
	vector.remove("Mother");
	vector.print();
	return 0;
}