#include "sorts.h"
#include <vector>
#include "time.h"
#include <cstdlib>
#include <iostream>
#include "libutils/io.h"
#include <chrono>
using namespace std;

int main () {
	srand(time(0));
	chrono::steady_clock time;
    auto n=73;
	int arr[73] = {5, 3, 3, 3, 5, 4, 5, 3, 3, 4, 2, 1, 5, 2, 4, 0, 2, 2, 3, 2, 2,
	1, 3,3,1,2,4,6,6,4,1,2,4,3,1,5,2,4,6,3,8,4,5,1,1,2,0,2,3,3,2,4,2,1,2,4,3,0,6,3,1,4,3,7,1,1,0,2,3,1,1};
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