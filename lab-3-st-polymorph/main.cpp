#include <libutils/io.h>
#include <libutils/bin-image.h>
#include <iostream>
#include "shared-ptr.h"
#include "unique-ptr.h"
#include "my-vector.h"
#include "my-list.h"
#include <vector>
#include <list>
#include <memory>

//template<typename T> using CollectionType = Vector<T>;
//template<typename T> using CollectionType = std::vector<T>;
template<typename T> using CollectionType = List<T>;
//template<typename T> using CollectionType = std::list<T>;
template<class T> using UniquePtrType = UniquePtr<T>;
//template<class T> using UniquePtrType = std::unique_ptr<T>;
template<class T> using SharedPtrType = SharedPtr<T>;

template<typename T>
void printCollection(CollectionType<T> collection){
	auto begin = collection.begin();
	auto end = collection.end();
	while (begin != end) {
		std::cout << *begin << " ";
		++begin;
	}
	std::cout << std::endl;
}
template<typename T>
T sum(T x, T y) {
	return x + y;
}

void main () {
	int i = 1;
	int j = 2;
	int a = sum(i, j);
	std::cout << a;
	getchar();
	CollectionType<int> collection(1);
	{
		collection.insert(collection.begin(), 2);
		collection.insert(collection.begin(), 1);
		collection.insert(collection.end(), 3);
		collection.insert(collection.end(), 4);
	}
	printCollection(collection);
	{
		CollectionType<int> collection1(collection);
		CollectionType<int> collection2(1);
		collection2 = collection1;
		printCollection(collection2);
	}
	std::cout << "Amount of elements: " << collection.size() << std::endl;
	auto willErased = collection.begin();
	willErased++;
	collection.erase(willErased);
	std::cout << "Size after erasing: " << collection.size() << std::endl << "Collection after erasig" << std::endl;
	printCollection(collection);
	collection.clear();
	std::cout << "Size after cleaning: " << collection.size() << std::endl << std::endl;
	std::cout << "UniquePtr demonstration: " << std::endl;
	{
		UniquePtrType<Image> uniqPtr1(new Image(2,2));
		std::cout << "UniquePtr 1: \n" << *uniqPtr1 << std::endl;
		UniquePtrType<Image> uniqPtr2;
		uniqPtr2 = std::move(uniqPtr1);
		std::cout << "UniquePtr 2: \n" << *uniqPtr2 << std::endl;
		uniqPtr2.release();
		std::cout << "\nUniquePtr2 after release: \n" << &uniqPtr2 <<std::endl;
		UniquePtrType<Image> uniqPtr3(new Image(3, 3));
		std::cout << "\nUniquePtr3: \n" << *uniqPtr3 << std::endl;
		uniqPtr3.reset(new Image(2, 2));
		std::cout << "\nUniquePtr3 after reset: \n" << *uniqPtr3 << std::endl;
		UniquePtrType<Image> uniqPtr4(new Image(4, 4));
		std::cout << "\nUniquePtr4:\n" << *uniqPtr4 << std::endl;
		uniqPtr4.swap(uniqPtr3);
		std::cout << "\nUniquePtr4 after swap with UniquePtr3: \n" << *uniqPtr4 << std::endl;
		std::cout << "\nUniquePtr3 after swap: \n"<<*uniqPtr3<<std::endl;
		if (uniqPtr1) std::cout << "\nUniquePtr1 != nullptr" << std::endl;
		else std::cout << "\nUniquPtr1 == nullptr" << std::endl;
		if (uniqPtr3) std::cout << "UniquePtr3 != nullptr" << std::endl;
		else std::cout << "UniquPtr3 == nullptr" << std::endl;
		if (uniqPtr1 == uniqPtr2) std::cout << "UniquePtr1 and UniquePtr2 are equal" << std::endl;
		else std::cout << "UniquePtr1 and UniquePtr2 are not equal" << std::endl;
	}
	std::cout << "\nSharedPtr demonstration: " << std::endl;
	{
		SharedPtrType<Image> sharedPtr1(new Image(2, 2));
		std::cout << "SharedPtr 1: \n" << *sharedPtr1 << std::endl;
		SharedPtrType<Image> sharedPtr2;
		sharedPtr2 = std::move(sharedPtr1);
		std::cout << "SharePtr 2: \n" << *sharedPtr2 << std::endl;
		SharedPtrType<Image> sharedPtr3=sharedPtr2;
		std::cout << "\nSharedPtr3: \n" << *sharedPtr3 << std::endl;
		sharedPtr3.reset(new Image(2, 2));
		std::cout << "\nSharedPtr3 after reset: \n" << *sharedPtr3 << std::endl;
		SharedPtrType<Image> sharedPtr4(new Image(4, 4));
		std::cout << "\nUniquePtr4:\n" << *sharedPtr4 << std::endl;
		sharedPtr4.swap(sharedPtr3);
		std::cout << "\nSharedPtr4 after swap with SharedPtr3: \n" << *sharedPtr4 << std::endl;
		std::cout << "\nSharedPtr3 after swap: \n" << *sharedPtr3 << std::endl;
		if (sharedPtr1) std::cout << "\nSharedPtr1 != nullptr" << std::endl;
		else std::cout << "\nSharedPtr1 == nullptr" << std::endl;
		if (sharedPtr3) std::cout << "SharedPtr3 != nullptr" << std::endl;
		else std::cout << "SharedPtr3 == nullptr" << std::endl;
		if (sharedPtr1 == sharedPtr2) std::cout << "SharedPtr1 and SharedPtr2 are equal" << std::endl;
		else std::cout << "SharedPtr1 and SharedPtr2 are not equal" << std::endl;
	}
}