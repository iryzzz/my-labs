#pragma once
#include <functional>

template<typename TKey, typename TKeyHash = std::hash<TKey>>
class UnorderedSet {
	struct Node {
		const TKey key;
		Node* next;

		explicit Node(const TKey& key) : key(key), next(nullptr) {}
	};

	Node** _table;
	const std::size_t _count;

	Node** Find(const TKey& key) {
		const auto i = TKeyHash()(key) % _count;
		auto node = _table + i;
		while (*node) {
			if ((*node)->key == key) {
				return node;
			}
			node = &((*node)->next);
		}
		return node;
	}

public:
	static const size_t DEFAULT_SIZE = 10000;

	UnorderedSet() : _table(new Node* [DEFAULT_SIZE]), _count(DEFAULT_SIZE) {
		for (std::size_t i = 0; i < _count; ++i) {
			_table[i] = nullptr;
		}
	}

	UnorderedSet(const UnorderedSet&) = delete;

	UnorderedSet& operator=(const UnorderedSet&) = delete;

	UnorderedSet(const UnorderedSet&&) = delete;

	UnorderedSet& operator=(const UnorderedSet&&) = delete;

	~UnorderedSet() {
		clear();
		delete[] _table;
	}

	void clear() {
		Node* crnt;
		for (auto i = 0; i < _count; ++i) {
			crnt = _table[i];
			if (_table[i]) {
				while (crnt) {
					auto tmp = crnt;
					crnt = crnt->next;
					delete tmp;
					tmp = nullptr;
				}
				_table[i] = nullptr;
			}
		}
	}

	bool insert(const TKey& key) {
		auto node = Find(key);
		if (*node != nullptr) {
			return false;
		}
		*node = new Node(key);
		return true;
	}

	bool contains(const TKey& key) {
		return *Find(key) != nullptr;
	}

	bool erase (const TKey& key) {
		auto node = Find(key);
		if (*node == nullptr) {
			return false;
		}
		auto tmp = *node;
		*node = (*node)->next;
		delete tmp;
		return true;
	}

	bool find (const TKey& key) {
		return (*(Find(key)) != nullptr);
	}

	void print() {
		Node** node;
		for (auto i = 0; i < _count; ++i) {
			if (_table[i]) {
				node = _table + i;
				while (*node) {
					std::cout << "[Hash: " << i << " | Value: " << (*node)->key << "]  ";
					node = &((*node)->next);
				}		
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}
};