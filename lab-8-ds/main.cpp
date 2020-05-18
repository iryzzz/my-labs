#include "ordered-vector.h"
#include "unordered-set.h"
#include "ordered-set.h"
#include <cstdlib>
#include <iostream>
#include "time.h"
#include <chrono>
using namespace std;

template<typename T> using StructureType = OrderedVector<T>;
//template<typename T> using StructureType = UnorderedSet<T>;
//template<typename T> using StructureType = OrderedSet<T>;

int main() {
	srand(time(0));
	chrono::steady_clock time;
	auto n = 3200;
	cout << "Amount of elements: " << n << endl;
	{
		StructureType<int> structure1;
		for (auto i = 0; i < n; ++i) {
			structure1.insert(rand() % 10000);
		}
		auto start = time.now();
		structure1.insert(rand() % 10000);
		auto end = time.now();
		chrono::duration<double> diff = end - start;
		cout << "Insertion time: " << diff.count() / 100 << endl;
	}
	
	{
		StructureType<int> structure1;
		for (auto i = 0; i < n; ++i) {
			structure1.insert(rand() % 10000);
		}
		auto start = time.now();
		structure1.find(rand() % 10000);
		auto end = time.now();
		chrono::duration<double> diff = end - start;
		cout << "Searching time: " << diff.count() / 100 << endl;
	}

	{
		StructureType<int> structure1;
		for (auto i = 0; i < n; ++i) {
			structure1.insert(rand() % 10000);
		}
		//structure1.print();
		auto start = time.now();
		structure1.erase(rand() % 10000);
		auto end = time.now();
		//structure1.print();
		chrono::duration<double> diff = end - start;
		cout << "Erasing time: " << diff.count() / 100 << endl;
	}
	
	
	return 0;
}