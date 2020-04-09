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
    auto n=10;
    int* arr= new int[n];
    for (auto i=0; i<n; ++i){
        arr[i]=rand()%100;
    }
    utils::printArray(arr,n);
	auto start = time.now();
    //selectionSort(arr,n);
    //bubbleSort(arr,n);
    //shellSort(arr,n);
    //qSort(arr,n);
    mergeSort(arr,n);
	auto end = time.now();
    utils::printArray(arr,n);
	chrono::duration<double> diff = end - start;
	cout << diff.count() / 100 <<  endl;
	delete[] arr;
    return 0;
}