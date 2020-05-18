#include "sorts.h"
#include <vector>
#include "time.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include "libutils/io.h"

using namespace std;

int main () {
	srand(time(0));
	chrono::steady_clock time;
    auto n=12;
	int arr[12] = {5, 3, 3, 3, 5, 4, 5, 3, 3, 4, 2, 1};
    utils::printArray(arr,n);
	auto start = time.now();
    //selectionSort(arr,n);
    //bubbleSort(arr,n);
    shellSort(arr,n);
    //qSort(arr,n);
    //mergeSort(arr,n);
	auto end = time.now();
    utils::printArray(arr,n);
	chrono::duration<double> diff = end - start;
	cout << diff.count() / 100 <<  endl;
    return 0;
}