#pragma once
#include <iostream>
#include <cstdint>
#include <algorithm>

template <typename T>
class OrderedSet {
	struct Node {
		T key;
		Node* left;
		Node* right;
		size_t height;
		Node(const T& key) : key(key), left(nullptr), right(nullptr),
			height(1) {}
	};
	Node* root;

	size_t getHeight(Node* p) {
		return p != nullptr ? p->height : 0;
	}

	int getBalance(Node* p) {
		return getHeight(p->right) - getHeight(p->left);
	}

	void updateHeight(Node* p) {
		auto leftHeight = getHeight(p->left);
		auto rightHeight = getHeight(p->right);
		p->height = (std::max(leftHeight, rightHeight) + 1);
	}

	Node* rotateRight(Node* p) {
		auto q = p->left;
		p->left = q->right;
		q->right = p;
		updateHeight(p);
		updateHeight(q);
		return q;
	}

	Node* rotateLeft(Node* q) {
		auto p = q->right;
		q->right = p->left;
		p->left = q;
		updateHeight(q);
		updateHeight(p);
		return p;
	}

	Node* balance(Node* p) {
		updateHeight(p);
		auto b = getBalance(p);
		if (b == 2) {
			if (getBalance(p->right) < 0)
				p->right = rotateRight(p->right);
			return rotateLeft(p);
		}
		if (b == -2) {
			if (getBalance(p->left) > 0)
				p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
		return p;
	}

	Node* insert(Node* p, const T& key) {
		if (p == nullptr)
			return new Node(key);
		if (key < p->key)
			p->left = insert(p->left, key);
		else if (p->key < key)
			p->right = insert(p->right, key);
		return balance(p);
	}

	void clear(Node* p)
	{
		if (p->left)
			clear(p->left);
		if (p->right)
			clear(p->right);
		if (p) delete p;
	}

	Node* findMin(Node* p) {
		return p->left ? findMin(p->left) : p;
	}

	Node* removeMin(Node* p) {
		if (p->left == nullptr)
			return p->right;
		p->left = removeMin(p->left);
		return balance(p);
	}

	Node* remove(Node* p, const T& key) {
			if (p==nullptr) return nullptr;
			if (key < p->key)
				p->left = remove(p->left, key);
			else if (key > p->key)
				p->right = remove(p->right, key);
			else {
				auto q = p->left;
				auto r = p->right;
				delete p;
				if (r==nullptr) return q;
				auto min = findMin(r);
				min->right = removeMin(r);
				min->left = q;
				return balance(min);
			}
			return balance(p);
		}

	Node* find(Node* p, const T& key) {
		if (p == nullptr)
			return nullptr;
		if (key < p->key)
			return find(p->left, key);
		else if (p->key < key)
			return find(p->right, key);
		else return p;
	}

	void print(Node* p, int offset) {
	
		cout << string(offset, ' ');
		if (p == nullptr) {
			cout << "NULL" << endl;
			return;
		}
		cout << p->key << endl;
		print(p->left, offset + 2);
		print(p->right, offset + 2);
	}

	public:
	OrderedSet() :root(nullptr) {}

	OrderedSet(const OrderedSet&) = delete;

	OrderedSet(const OrderedSet&&) = delete;

	OrderedSet& operator =(const OrderedSet&) = delete;

	OrderedSet& operator =(const OrderedSet&&) = delete;

	~OrderedSet() {
		if (root) {
			clear();
			root = nullptr;
		}
	}

	bool find(const T& key) {
		return find(root, key) != nullptr;
	}

	void insert(const T& key) {
		root = insert(root, key);
	}

	void erase(const T& key) {
		root = remove(root, key);
	}

	void clear() {
		clear(root);
		root = nullptr;
	}

	void print() {
		print(root, 1);
		std::cout << std::endl;
	}
};