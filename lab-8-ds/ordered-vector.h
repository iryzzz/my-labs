#pragma once 
#include <iostream>
#include <memory>

template<typename T>
class OrderedVector;

template<typename T>
class IteratorVector final {
		T* _ptr;

	public:
		friend class OrderedVector<T>;

		IteratorVector() :_ptr(nullptr) {}

		explicit IteratorVector(T* const _p) :_ptr(_p) {}

		IteratorVector(const IteratorVector<T>& iterator) :_ptr(iterator._ptr) {}

		T& operator* () {
			return *_ptr;
		}

		T* operator-> () {
			return _ptr;
		}

		bool operator==(const IteratorVector<T>& obj)const noexcept {
			return _ptr == obj._ptr;
		}

		bool operator!=(const IteratorVector<T>& obj)const noexcept {
			return _ptr != obj._ptr;
		}

		bool operator==(std::nullptr_t _ptr)noexcept {
			return _ptr == nullptr;
		}

		bool operator!=(std::nullptr_t _ptr)noexcept {
			return _ptr != nullptr;
		}

		IteratorVector<T>& operator+(int value) {
			for (int i = 0; i < value; ++i)
				++_ptr;
			return *this;
		}

		IteratorVector<T>& operator-(int value) {
			for (int i = 0; i < value; ++i)
				--_ptr;
			return *this;
		}

		IteratorVector<T>& operator++() {
			if (_ptr == nullptr) throw 404;
			++_ptr;
			return *this;
		}

		IteratorVector<T> operator++(int) {
			if (_ptr == nullptr) throw 404;
			IteratorVector<T> copy(*this);
			++_ptr;
			return copy;
		}

		IteratorVector<T>& operator--() {
			if (_ptr == nullptr) throw 404;
			--_ptr;
			return *this;
		}

		IteratorVector<T> operator--(int) {
			if (_ptr == nullptr) throw 404;
			IteratorVector copy(*this);
			--_ptr;
			return copy;
		}
	};


template<typename T>
class OrderedVector {
	T* _arr;
	std::size_t _size;

	IteratorVector<T> binarySearch(const T& value) {
		if (_size == 0) return IteratorVector<T>(nullptr);
		bool isFound = false;
		int left = 0;
		int right = _size - 1;
		int idx = 0;
		while (left <= right) {
			idx = (left + right) / 2;
			if (_arr[idx] == value) {
				isFound = true; 
				break;
			}
			if (_arr[idx] > value) right = idx - 1;
			else left = idx + 1;
		}

		if (isFound == true) return IteratorVector<T>(_arr + idx);
		else return IteratorVector<T>(nullptr);
	}


public:
	friend class IteratorVector<T>;

	OrderedVector() :_arr(nullptr), _size(0) {}

	OrderedVector(std::size_t _size) : _arr(new T[_size]), _size(_size) {}

	OrderedVector(const OrderedVector<T>& obj) : _arr(new T[obj._size]), _size(obj._size) {
		for (auto i = 0; i < _size; ++i) {
			_arr[i] = obj._arr[i];
		}
	}

	OrderedVector(OrderedVector<T>&& obj) noexcept : _arr(obj._arr), _size(obj._size) {
		obj._arr = nullptr;
		obj._size = 0;
	}

	OrderedVector<T>& operator=(const OrderedVector<T>& obj) { //присваивание копированием 
		if (this == &obj) return *this;
		T* _data = new T[obj._size];
		for (auto i = 0; i < obj._size; ++i) {
			_data[i] = obj._arr[i];
		}
		delete[] _arr;
		_arr = _data;
		_size = obj._size;
		return *this;
	}

	OrderedVector<T>& operator=(OrderedVector<T>&& obj)noexcept {
		delete[] _arr;
		_arr = obj._arr;
		_size = obj._size;
		obj._arr = nullptr;
		obj._size = 0;
		return *this;
	}

	~OrderedVector() {
		clear();
	}

	std::size_t size()const noexcept {
		return _size;
	}

	IteratorVector<T> begin()const noexcept {
		return IteratorVector<T>(_arr);
	}

	IteratorVector<T> end()const noexcept {
		return IteratorVector<T>(_arr + _size);
	}

	void clear()noexcept {
		delete[]_arr;
		_arr = nullptr;
		_size = 0;
	}

	bool find(const T& elem) {
		return (binarySearch(elem) != IteratorVector<T>(nullptr));
	}

	IteratorVector<T> insert(const T& val) {
		if (_arr == nullptr) {
			T* newData = new T[1];
			newData[0] = val;
			_arr = newData;
			++_size;
			return IteratorVector<T>(_arr);
		}
		int left = 0;
		int right = (_size - 1);
		int idx = 0;
		while (left <= right) {
			idx = (left + right) / 2;
			if (_arr[idx] == val)
				return IteratorVector<T>(nullptr);
			if (_arr[idx] > val) right = idx - 1;
			else left = idx + 1;
		}
		if (right == _size - 1) {
			if (_arr[right] > val)
				idx = right;
			else if (_arr[right] < val)
				idx = right + 1;
		}
		else {
			if (_arr[left] > val) idx = left;
			else if (_arr[left] < val) idx = left + 1;
		}
		T* newData = new T[_size + 1];
		for (int i = 0; i < idx; ++i)
			newData[i] = _arr[i];
		newData[idx] = val;
		for (int i = idx + 1; i < _size + 1; ++i)
			newData[i] = _arr[i - 1];
		delete[] _arr;
		_arr = newData;
		++_size;
		return IteratorVector<T>(_arr + idx);
	}

	IteratorVector<T> erase(const T& value) {
		if (_arr == nullptr)
			return IteratorVector<T>(nullptr);
		T* newData = new T[_size - 1];
		if (newData == nullptr)
			return IteratorVector<T>(nullptr);
		IteratorVector<T> current = binarySearch(value);
		if (current == IteratorVector<T>(nullptr))
			return IteratorVector<T>(nullptr);
		int idx = static_cast<int>(current._ptr - _arr);
		for (int i = 0; i < idx; ++i)
			newData[i] = _arr[i];
		for (int i = idx; i < _size - 1; ++i)
			newData[i] = _arr[i + 1];
		delete[] _arr;
		_arr = newData;
		--_size;
		return IteratorVector<T>(_arr + idx);
	}

	void print() {
		for (auto i = 0; i < _size; ++i) {
			std::cout << _arr[i] << " ";
		}
		std::cout << std::endl ;
	}
};
template<typename T>
bool operator==(const OrderedVector<T>& first, const OrderedVector<T>& second)noexcept {
	if (first._size() != second._size()) return false;
	IteratorVector<T> it1(first.begin());
	IteratorVector<T> it2(second.begin());
	for (; it1 != first.end(); ++it1) {
		if (it1 != it2) return false;
		else {
			++it2;
		}
		return true;
	}
}

template<typename T>
bool operator!=(const OrderedVector<T> first, const OrderedVector<T> second)noexcept {
	return !(first == second);
};
