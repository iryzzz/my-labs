#pragma once
template<typename T>
class SharedPtr {
	T* _ptr;
	long* _count;
public:
	SharedPtr() : _ptr(nullptr), _count(nullptr) {}

	explicit SharedPtr(T* const ptr) {
		_ptr = ptr;
		if (_ptr != nullptr) {
			_count = new long(1);
		}
		else _count = nullptr;
	}
	
	SharedPtr(const SharedPtr& ptr) : _ptr(ptr._ptr) {
		_count = ptr._count;
		if (_count != nullptr) ++(*_count);
	}
	
	SharedPtr& operator=(const SharedPtr& ptr) {
		SharedPtr<T>(ptr).swap(*this);
		return *this;
	}
	
	SharedPtr(SharedPtr&& ptr) noexcept : _ptr(ptr._ptr), _count(ptr._count) {
		ptr._ptr = nullptr;
		ptr._count = nullptr;
	}
	
	SharedPtr& operator=(SharedPtr&& ptr) noexcept {
		SharedPtr<T>(std::move(ptr)).swap(*this);
		return *this;
	}
	
	~SharedPtr() { 
		reset();
	}

	long use_count() const {
		if (_count == nullptr) return 0;
		else return *_count;
	}

	void reset(T* const ptr = nullptr) { //
		if (_ptr != nullptr) {
			--(*_count);
			if (*_count == 0) {
				delete _ptr;
				delete _count;
			}
		}
		if (ptr != nullptr) _count = new long(1);
		else _count = nullptr;
		_ptr = ptr;
	}

	T* get() const {
		return _ptr;
	}

	void swap(SharedPtr& other) {
		std::swap(_ptr, other._ptr);
		std::swap(_count, other._count);
	}

	explicit operator bool() const {
		return (get() != nullptr);
	}

	T& operator*() const {
		return *_ptr;
	}

	T* operator->() const {
		return _ptr;
	}
};
template<typename T>
bool operator==(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return (lhs.get() == rhs.get());
}

template<typename T>
bool operator==(const SharedPtr<T>& lhs, nullptr_t) {
	return (lhs.get() == nullptr);
}
template<typename T>
bool operator==(nullptr_t, const SharedPtr<T>& rhs) {
	return (rhs.get() == nullptr);
}

template<typename T>
bool operator!=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return !(rhs == lhs);
}

template<typename T>
bool operator!=(const SharedPtr<T>& lhs, nullptr_t) {
	return !(nullptr == lhs);
}

template<typename T>
bool operator!=(nullptr_t, const SharedPtr<T>& rhs) {
	return !(rhs == nullptr);
}

template<typename T>
bool operator<(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return (lhs.get() < rhs.get());
}
template<typename T>
bool operator<(const SharedPtr<T>& lhs, nullptr_t) {
	return (lhs.get() < nullptr);
}
template<typename T>
bool operator<(nullptr_t, const SharedPtr<T>& rhs) {
	return (nullptr < rhs.get());
}

template<typename T>
bool operator>(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return (rhs < lhs);
}
template<typename T>
bool operator>(const SharedPtr<T>& lhs, nullptr_t) {
	return (nullptr < lhs);
}
template<typename T>
bool operator>(nullptr_t, const SharedPtr<T>& rhs) {
	return (rhs < nullptr);
}

template<typename T>
bool operator>=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return !(lhs < rhs);
}
template<typename T>
bool operator>=(const SharedPtr<T>& lhs, nullptr_t) {
	return !(nullptr < lhs);
}
template<typename T>
bool operator>=(nullptr_t, const SharedPtr<T>& rhs) {
	return !(rhs < nullptr);
}

template<typename T>
bool operator<=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return !(rhs < lhs);
}
template<typename T>
bool operator<=(const SharedPtr<T>& lhs, nullptr_t) {
	return !(lhs < nullptr);
}
template<typename T>
bool operator<=(nullptr_t, const SharedPtr<T>& rhs) {
	return !(nullptr < rhs);
}