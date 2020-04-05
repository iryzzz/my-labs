#pragma once
template<typename T>
class UniquePtr {
	T* _ptr;
public:
	explicit UniquePtr(T* const ptr = nullptr) : _ptr(ptr) { }
	
	UniquePtr(const UniquePtr&) = delete;
	
	UniquePtr& operator=(const UniquePtr&) = delete;
	
	UniquePtr(UniquePtr&& ptr) noexcept : _ptr(ptr._ptr) {
		ptr._ptr = nullptr;
	}
	
	UniquePtr& operator=(UniquePtr&& ptr) noexcept {
		if (*this != ptr) {
			delete _ptr;
			_ptr = ptr._ptr;
			ptr._ptr = nullptr;
			return *this;
		}
	}

	~UniquePtr() {
		reset();
	}

	T* release() {
		T* tmp = _ptr;
		_ptr = nullptr;
		return tmp;
	}

	void reset(T* const ptr = nullptr) {
		if (_ptr != ptr) {
			delete _ptr;
			_ptr = ptr;
		}
	}

	T* get() const {
		if (_ptr == nullptr) return nullptr;
		return _ptr;
	}

	void swap(UniquePtr& other) {
		std::swap(_ptr, other._ptr);
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
bool operator==(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return (lhs.get() == rhs.get());
}

template<typename T>
bool operator==(const UniquePtr<T>& lhs, nullptr_t) {
	return (lhs.get() == nullptr);
}

template<typename T>
bool operator==(nullptr_t, const UniquePtr<T>& rhs) {
	return (rhs.get() == nullptr);
}


template<typename T>
bool operator!=(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return (lhs.get() != rhs.get());
}

template<typename T>
bool operator!=(const UniquePtr<T>& lhs, nullptr_t) {
	return !(nullptr == lhs);
}

template<typename T>
bool operator!=(nullptr_t, const UniquePtr<T>& rhs) {
	return !(rhs == nullptr);
}

template<typename T>
bool operator<(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return (lhs.get() < rhs.get());
}

template<typename T>
bool operator<(const UniquePtr<T>& lhs, nullptr_t) {
	return (lhs.get() < nullptr);
}

template<typename T>
bool operator<(nullptr_t, const UniquePtr<T>& rhs) {
	return (nullptr < rhs.get());
}

template<typename T>
bool operator>(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return (rhs < lhs);
}

template<typename T>
bool operator>(const UniquePtr<T>& lhs, nullptr_t) {
	return (nullptr < lhs);
}

template<typename T>
bool operator>(nullptr_t, const UniquePtr<T>& rhs) {
	return (rhs < nullptr);
}

template<typename T>
bool operator>=(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return !(lhs < rhs);
}

template<typename T>
bool operator>=(const UniquePtr<T>& lhs, nullptr_t) {
	return !(nullptr < lhs);
}

template<typename T>
bool operator>=(nullptr_t, const UniquePtr<T>& rhs) {
	return !(rhs < nullptr);
}

template<typename T>
bool operator<=(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return !(rhs < lhs);
}

template<typename T>
bool operator<=(const UniquePtr<T>& lhs, nullptr_t) {
	return !(lhs < nullptr);
}

template<typename T>
bool operator<=(nullptr_t, const UniquePtr<T>& rhs) {
	return !(nullptr < rhs);
}
