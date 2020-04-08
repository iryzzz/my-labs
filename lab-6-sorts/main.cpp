#include "sorts.h"
#include <vector>
#include "time.h"
#include <cstdlib>
#include <iostream>
#include "libutils/io.h"
using namespace std;

int main () {
    auto n=15;
    int arr[n];
    srand(time(0));
    for (auto i=0; i<n; ++i){
        arr[i]=rand()%100;
    }
    utils::printArray(arr,n);
    //selectionSort(arr,n);
    //bubbleSort(arr,n);
    //shellSort(arr,n);
    //qSort(arr,n);
    mergeSort(arr,n);
    utils::printArray(arr,n);
    return 0;
}