#pragma once
#include <iostream>

namespace utils {
	int readInt(const char* prompt, int min, int max);

	double readDouble(const char* promt, double min, double max);

	template <typename T>
	void printArray (T*arr, int size) {
	    for (int i=0;i<size;++i)
	        std::cout<<arr[i]<<" ";
        std::cout<<std::endl;
	}
}