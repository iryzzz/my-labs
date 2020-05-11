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

	Node** find(const TKey& key) {
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
	static const size_t DEFAULT_SIZE = 17;

	UnorderedSet() : _table(new Node* [DEFAULT_SIZE]), _count(DEFAULT_SIZE) {
		for (std::size_t i = 0; i < _count; ++i) {
			_table[i] = nullptr;
		}
	}

	UnorderedSet(const UnorderedSet&) = delete;

	UnorderedSet& operator=(const UnorderedSet&) = delete;

	~UnorderedSet() {
		// clear();
		delete[] _table;
	}

	void clear() {

	}

	bool insert(const TKey& key) {
		auto node = find(key);
		if (*node != nullptr) {
			return false;
		}
		*node = new Node(key);
		return true;
	}

	bool contains(const TKey& key) {
		return *find(key) != nullptr;
	}

	bool remove(const TKey& key) {
		auto node = find(key);
		if (*node == nullptr) {
			return false;
		}
		auto tmp = *node;
		*node = (*node)->next;
		delete tmp;
		return true;
	}
};