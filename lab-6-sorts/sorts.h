#pragma once
#include <iostream>
#include <memory>

template <typename T>
void selectionSort(T* arr, const size_t size) {
for (int i=0; i<size; ++i) {
    for (int j=(i+1); j<size; ++j) {
        if (arr[j] < arr[i])
            std::swap(arr[j], arr[i]);
        }
    }
}

template <typename T>
void bubbleSort(T* arr, const size_t size) {
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
void shellSort(T* arr, const size_t size) {
    int distance= (size / 2);
    int j=0;
    while (distance > 0) {
        for (int i = 0; i < (size - distance); ++i) {
            if(arr[i] > arr[i + distance]) {
                std::swap(arr[i],arr[i+distance]);
                j=i;
                while(((j-distance)>=0) && (arr[j]<arr[j-distance])) {
                    std::swap(arr[j],arr[j-distance]);
                    j=(j-distance);
                }
            }
        }
        distance = distance / 2;
    }
}

template <typename T>
void qSort(T* arr, const size_t size) {
    int l = 0, r = (size - 1);
    T piv = arr[(l + r) / 2];
    while (l <= r) {
        while (arr[l] < piv)
            ++l;
        while (arr[r] > piv)
            --r;
        if (l <= r) {
            if (l != r) {
                std::swap(arr[l], arr[r]);
            }
            ++l;
            --r;
        }
    }
    if (0 < r)
        qSort(arr, r + 1);
    if ((size - 1) > l)
        qSort(arr + l, size - l);
}

template <typename T>
void mergeSort (T* arr, const size_t size) {
    T* tmp = new T [size * 2];
    auto s = false;
    bool goAgain;
    for (int i=0; i<size; ++i) {
        tmp[i]=arr[i];
    }
    int i, j, k, l;
    do {
        auto d = 1;
        goAgain = false;
        if (!s) {
            i = 0;
            j = (size - 1);
            k = size;
            l = (2 * size -1);
        }
        else {
            i = size;
            j = (2 * size - 1);
            k = 0;
            l = (size - 1);
        }
        while (i != j) {
            if (tmp[i] > tmp[j]) {
                tmp[k]=tmp[j];
                k+=d;
                --j;
                if (tmp[j+1]<=tmp[j]) continue;
                do {
                    tmp[k] = tmp[i];
                    k+=d;
                    ++i;
                } while (tmp[i-1]<=tmp[i]);
            }
            else {
                tmp[k]=tmp[i];
                k+=d;
                ++i;
                if (tmp[i-1]<=tmp[i]) continue;
                do {
                    tmp[k] = tmp[j];
                    k+=d;
                    --j;
                } while (tmp[j+1]<=tmp[j]);
            }
            goAgain=true;
        }
        s = !s;
        tmp[k] = tmp[i];
        d = -d;
    } while (goAgain);
    if (s) {
        for (int i = 0; i < size; ++i)
            arr[i] = tmp[i];
    }
    else {
        for (int i = 0; i < size; ++i)
            arr[i] = tmp[i + size];
    }
    delete[] tmp;
}