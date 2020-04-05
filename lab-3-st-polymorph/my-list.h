#pragma once 
#include <iostream> 
#include <string>
#include <memory>
#include<cstddef>

template<typename T>
class Node {
public:
	T _data;
	Node<T>* _next;
	Node<T>* _prev;
	Node(const T& data = (T)NULL, Node* const next = nullptr, Node* const prev = nullptr) : _data(data), _next(next), _prev(prev) {}
};

template<typename T>
class List;

template<typename T>
class IteratorList {
	Node<T>* _node;
	IteratorList() : _node(nullptr) { }
	IteratorList(Node<T>* const node) : _node(node) { }
public:
	friend class List<T>;
	IteratorList& operator++() {
		if(_node == nullptr) throw 404;
		_node = _node->_next;
		return *this;
	}
	IteratorList operator++(int) {
		if (_node == nullptr) throw 404;
		IteratorList copy(*this);
		_node = _node->_next;
		return copy;
	}

	IteratorList& operator+(int num) {
		for (int i = 0; i < num; ++i)
			_node = _node->_next;
		return *this;
	}

	IteratorList& operator--() {
		if (_node == nullptr) throw 404;
		_node = _node->_prev;
		return *this;
	}
	IteratorList operator--(int) {
		if (_node == nullptr) throw 404;
		IteratorList copy(*this);
		_node = _node->_prev;
		return copy;
	}
	IteratorList& operator-(int num) {
		if (_node == nullptr)|| throw 404;
		for (int i = 0; i < num; ++i)
			_node = _node->_prev;
		return *this;
	}
	T& operator*() const {
		return _node->_data;
	}
	T* operator->() const {
		return _node;
	}

	bool operator==(const IteratorList& rhs) const {
		return _node == rhs._node;
	}
	bool operator!=(const IteratorList& rhs) const {
		return _node != rhs._node;
	}
};

template<typename T>
class List {
	Node<T>* _head;
	Node<T>* _tail;
	size_t _size;
public:
	List(): _size(0), _head(new Node<T>(NULL, nullptr, nullptr)) {
		_tail = _head;
	}

	List(const int& size): _size(size), _head (new Node<T>(NULL, nullptr, nullptr)) {
		_tail = _head;
		for (auto i=0; i <size; ++i) {
			_tail->_next = new Node<T>(NULL, nullptr, _tail);
			_tail = _tail->_next;
		}
	}

	List(const List<T>& obj) {
		_size = obj._size;
		auto oldHead = obj._head;
		_head = new Node<T>(oldHead->_data, nullptr, nullptr);
		_tail = _head;
		while (oldHead != obj._tail) {
			oldHead = oldHead->_next;
			_tail->_next = new Node<T>(oldHead->_data, nullptr, _tail);
			_tail = _tail->_next;
		}
	}
	
	List<T>& operator=(const List<T>& obj) { 
		if (this != &obj) {
			clear();
			delete _tail;
			_size = obj._size;
			auto oldHead = obj._head;
			_head = new Node<T>(oldHead->_data, nullptr, nullptr);
			_tail = _head;
			while (oldHead != obj._tail) {
				oldHead = oldHead->_next;
				_tail->_next = new Node<T>(oldHead->_data, nullptr, _tail);
				_tail = _tail->_next;
			}
			return *this;
		}
	}
	
	List(List<T>&& obj) noexcept : _head(obj._head), _size(obj._size), _tail(obj._tail) {
		obj._head = nullptr;
		obj._size = 0;
		obj._tail = nullptr;
	}
	
	List<T>& operator=(List<T>&& obj) noexcept {
		if (*this != list) {
			delete _head;
			_head = obj._head;
			_size = obj._size;
			_tail = obj._tail;
			obj._head = nullptr;
			obj._size = 0;
			obj._tail = nullptr;
			return *this;
		}
	}
	
	~List() { 
		clear();
		delete _tail;
	}
	size_t size() const noexcept {
		return _size;
	}
	IteratorList<T> begin() const noexcept {
		return IteratorList<T>(_head);
	}
	IteratorList<T> end() const noexcept {
		return IteratorList<T>(_tail);
	}

	IteratorList<T> insert(IteratorList<T> it, const T& elem) {
		IteratorList<T> it2(it);
		--it2;
		auto nod = new Node<T>(elem, it._node, it2._node);
		it._node->_prev = nod;
		if (it2._node != nullptr) it2._node->_next = nod;
		if ((_size == 0) || (it._node == _head)) _head = nod;
		++_size;
		return IteratorList<T>(nod);
	}

	IteratorList<T> erase(IteratorList<T> it) {
		IteratorList<T> it2(it);
		IteratorList<T> it3(it);
		if (it != nullptr) {
			++it2;
			--it3;
			if (it2._node != nullptr) it2._node->_prev = it3._node;
			if (it3._node != nullptr) it3._node->_next = it2._node;
			if (it == _head) _head = it2._node;
			delete it._node;
			--_size;
		}
		return it2;
	}
	void clear() {
		_size = 0;
		while (_head != _tail) {
			_head = _head->_next;
			delete _head->_prev;
		}
		_head = _tail;
	}
};
