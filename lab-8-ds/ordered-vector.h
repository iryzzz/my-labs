#pragma once 
#include <iostream> 
#include <string>
#include <memory>
#include <cstddef>


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
	size_t _size;

public:
	friend class IteratorVector<T>;

	OrderedVector() :_arr(nullptr), _size(0) {}

	OrderedVector(size_t _size) : _arr(new T[_size]), _size(_size) {}

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

	size_t size()const noexcept {
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

	IteratorVector<T> insert(const T& elem) {
		if (_size == 0) {
			T* tmp = new T[++_size];
			delete[] _arr;
			_arr = tmp;
			_arr[0] = elem;
			return IteratorVector<T>(_arr);
		}
		if (_size == 1) {
			T* tmp = new T[++_size];
			if (_arr[0] > elem) {
				tmp[0] = elem;
				tmp[1] = _arr[0];
			}
			delete[] _arr;
			_arr = tmp;
			return IteratorVector<T>(_arr+1);
		}
		auto left = 0;
		auto right = (_size - 1);
		size_t mid = _size / 2;
		while (left <= right) {
			mid = ((left + right) / 2);
			if ((_arr[mid] <= elem) && (elem < _arr[mid + 1]))
				break;
			if (elem < _arr[mid])
				right = mid - 1;
			else
				left = mid + 1;
		}
		T* tmp = new T[++_size];
		auto k = 0;
		for (auto i = 0; i < _size; ++i) {
			if (i == (mid +1)) {
				tmp[i] = elem;
			}
			else {
				tmp[i] = _arr[k];
				++k;
			}
		}
		delete[] _arr;
		_arr = tmp;
		return IteratorVector<T>(_arr + (mid + 1));
	}
		//size_t idx = it._ptr - _arr;
		//T* tmp = new T[++_size];
		//for (auto i = 0; i < idx; ++i)
		//	tmp[i] = _arr[i];
		//tmp[idx] = elem;
		//for (auto i = idx + 1; i < _size; ++i)
		//	tmp[i] = _arr[i - 1];
		//delete[] _arr;
		//_arr = tmp;
		//return IteratorVector<T>(_arr + idx);

	IteratorVector<T> erase(IteratorVector<T>& it) {
		size_t idx = it._ptr - _arr;
		auto size = _size;
		T* tmp = new T[_size --];
		for (auto i = 0; i < idx; ++i)
			tmp[i] = _arr[i];
		for (auto i = idx; i < size - 1; ++i)
			tmp[i] = _arr[i + 1];
		delete[] _arr;
		_arr = tmp;
		return IteratorVector<T>(_arr + idx);
	}

	IteratorVector<T> search(T elem) {
		int left = 0;
		int right = _size;
		size_t mid;
		try {
			while (left <= right) {
				mid = (left + right) / 2;
				if ((left == right) && (elem != _arr[mid])) throw 404;
				if (elem == _arr[mid]) { 
					return IteratorVector<T>(_arr + mid);
				}
				if (elem < _arr[mid])
					right = mid - 1;
				else
					left = mid + 1;
			}
		}
		catch (int i) {
			std::cout << "Error " << i << ": not found"<<std::endl;
		}
		return IteratorVector<T>(nullptr);
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

template<typename T>
std::ostream& operator<<(std::ostream& out, const OrderedVector<T>& vector) noexcept {
	auto begin = vector.begin();
	auto end = vector.end();
	while (begin != end) {
		out << *begin << " ";
		++begin;
	}
	out << endl;
	return out;
}