#pragma once
#include <iostream>
#include <memory>

template <typename T>
void selectionSort(T* arr, size_t size) {
for (int i=0; i<size; ++i) {
    for (int j=(i+1); j<size; ++j) {
        if (arr[j] < arr[i])
            std::swap(arr[j], arr[i]);
        }
    }
}

template <typename T>
void bubbleSort(T* arr, size_t size) {
    auto isSwapped = false;
    for (size_t i=0; i<size; ++i) {
        isSwapped=false;
        for (size_t j=0; j<size-i; ++j) {
            if (arr[j]>arr[j+1]) {
                std::swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }
        if (!isSwapped) break;
    }
}

template <typename T>
void shellSort(T* arr, size_t size) {
    int distance= (size / 2);
    int j=0;
    while (distance > 0) {
        for (int i = 0; i < (size - distance); ++i) {
            if(arr[i] > arr[i + distance]) {
                std::swap(arr[i],arr[i+distance]);
                j=i;
                while(((j-distance)>0) && (arr[j]<arr[j-distance])) {
                    std::swap(arr[j],arr[j-distance]);
                    j=(j-distance);
                }
            }
        }
        distance = distance / 2;
    }
}

template <typename T>
void quickSort(T* arr, size_t size) {

}