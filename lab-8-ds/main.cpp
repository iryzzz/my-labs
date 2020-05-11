#include "ordered-vector.h"
#include <cstdlib>
#include <iostream>
#include "libutils/io.h"
#include <chrono>

using namespace std;

int main() {
	OrderedVector<int> vector;
	{
		vector.insert(2);
		vector.insert(1);
		vector.insert(4);
		vector.insert(99);
		vector.insert(1);
		vector.insert(2);
		vector.insert(16);
		vector.insert(4);
		vector.insert(4);
		vector.insert(3);
	}
	cout << vector;
	auto b = vector.search(16);
	vector.erase(b);
	cout << vector;
	b = vector.search(3);
	vector.erase(b);
	cout << vector;
	return 0;
}