#include "sorts.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include "libutils/io.h"
using namespace std;

int main () {
    auto n=15;
    int arr[n];
    for (auto i=0; i<n; ++i){
        arr[i]=rand()%100;
    }
    utils::printArray(arr,n);
    //selectionSort(A,n);
    //bubbleSort(arr,n);
    shellSort(arr,n);
    utils::printArray(arr,n);
    return 0;
}