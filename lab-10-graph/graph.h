#pragma once

#include <algorithm>
#include <limits>
#include <stdexcept>
#include"Locality.h"

template<typename TVertex, typename TEdge>
class Graph {

public:
	struct Edge {
		TVertex dstVertex;
		TEdge edge;

		Edge(TVertex dstVertex, TEdge edge) : dstVertex(dstVertex), edge(edge) {}
	};

private:
	struct EdgeNode {
		Edge edge;
		EdgeNode* next;

		EdgeNode(Edge edge, EdgeNode* next) : edge(edge), next(next) {}
	};

	struct Vertex {
		TVertex vertex;
		EdgeNode* edges;

		Vertex() : edges(nullptr) {}

		explicit Vertex(TVertex vertex) : vertex(vertex), edges(nullptr) {}
	};

	Vertex* _graph;
	std::size_t _count;

	std::size_t getVertexIndex(TVertex vertex) const {
		for (std::size_t i = 0; i < _count; ++i) {
			if (_graph[i].vertex == vertex) {
				return i;
			}
		}
		return _count;
	}

public:
	Graph() : _graph(nullptr), _count(0) {}

	Graph(const Graph&) = delete;

	Graph& operator=(const Graph&) = delete;

	~Graph() {
		for (std::size_t i = 0; i < _count; ++i)
		{
			if (_graph[i].edges != nullptr) {
				auto tmp = _graph[i].edges;
				if (tmp != nullptr)
				{
					while (tmp->next != nullptr)
					{
						auto d = tmp;
						tmp = tmp->next;
						delete d;
					}
				}
				_graph[i].edges = nullptr;
			}
		}
		delete[] _graph;
		_count = 0;
	}

	std::size_t getVertexIndexOrThrow(TVertex vertex) const {
		const auto index = getVertexIndex(vertex);
		if (index == _count)
			throw std::invalid_argument("Vertex not found!");
		return index;
	}

	std::size_t getVertexCount() const {
		return _count;
	}

	TVertex getVertex(std::size_t index) const {
		return _graph[index].vertex;
	}

	EdgeNode* getEdgeList(int index) {
		if (index < 0 || index > _count - 1)
			throw std::invalid_argument("Index is out of range");

		return _graph[index].edges;
	}


	void addVertex(TVertex vertex) {
		const auto index = getVertexIndex(vertex);
		if (index != _count)
			throw std::invalid_argument("Vertex already exists!");
		auto graph = new Vertex[_count + 1];
		for (std::size_t i = 0; i < _count; ++i) {
			graph[i] = _graph[i];
		}
		graph[_count] = Vertex(vertex);
		delete[] _graph;
		_graph = graph;
		++_count;
	}

	void addEdge(TVertex srcVertex, TVertex dstVertex, TEdge edge) {
		const auto sourceIndex = getVertexIndexOrThrow(srcVertex);
		const auto destinationIndex = getVertexIndexOrThrow(dstVertex);
		Edge e(dstVertex, edge);
		_graph[sourceIndex].edges = new EdgeNode(e, _graph[sourceIndex].edges);
	}

	void eraseEdge(TVertex srcVertex, TVertex dstVertex) {
		const auto srcIndex = getVertexIndexOrThrow(srcVertex);
		auto tmp = _graph[srcIndex].edges;
		if (tmp != nullptr) {
			auto p = _graph[srcIndex].edges;
			if (tmp->next == nullptr) {
				if (tmp->edge.dstVertex == dstVertex) {
					auto del = tmp;
					tmp = tmp->next;
					_graph[srcIndex].edges = tmp;
					delete del;
				}
			}
			else {
				while (tmp != nullptr) {
					if (tmp->edge.dstVertex == dstVertex) {
						if (tmp->edge.dstVertex == _graph[srcIndex].edges->edge.dstVertex) {
							EdgeNode* del = tmp;
							tmp = tmp->next;
							_graph[srcIndex].edges = tmp;
							delete del;
							break;
						}
						else {
							EdgeNode* del = tmp;
							tmp = tmp->next;
							p->next = tmp;
							delete del;
							break;
						}
					}
					p = tmp;
					tmp = tmp->next;
				}
			}
		}
	}

	void eraseVertex(TVertex vertex) {
		const auto index = getVertexIndexOrThrow(vertex);
		Vertex* newgraph = new Vertex[_count - 1];
		for (size_t i = 0; i < index; ++i) {
			newgraph[i] = _graph[i];
		}
		for (size_t i = index; i < _count - 1; ++i) {
			newgraph[i] = _graph[i + 1];
		}
		delete[] _graph;
		_graph = newgraph;
		--_count;
		for (int i = 0; i < _count; ++i) {
			EdgeNode* tmp = _graph[i].edges;
			if (tmp != nullptr) {
				EdgeNode* p = _graph[i].edges;
				if (tmp->next == nullptr) {
					if (tmp->edge.dstVertex == vertex) {
						EdgeNode* del = tmp;
						tmp = tmp->next;
						_graph[i].edges = tmp;
						delete del;
						break;
					}
				}
				else {
					while (tmp != nullptr) {
						if (tmp->edge.dstVertex == vertex) {
							if (tmp->edge.dstVertex == _graph[i].edges->edge.dstVertex) {
								EdgeNode* del = tmp;
								tmp = tmp->next;
								_graph[i].edges = tmp;
								delete del;
								break;
							}
							else {
								EdgeNode* del = tmp;
								tmp = tmp->next;
								p->next = tmp;
								delete del;
								break;
							}
						}
						p = tmp;
						tmp = tmp->next;
					}
				}
			}
		}
	}

	void editVertex(TVertex oldVertex, TVertex newVertex) {
		const auto index = getVertexIndexOrThrow(oldVertex);

		_graph[index].vertex = newVertex;
	}

	void editEdge(TVertex srcVertex, TVertex dstVertex, TEdge newEdge) {
		const auto sourceIndex = getVertexIndexOrThrow(srcVertex);
		const auto destinationIndex = getVertexIndexOrThrow(dstVertex);

		auto tmp = _graph[sourceIndex].edges;
		while (tmp) {
			if (tmp->edge.dstVertex == dstVertex) {
				tmp->edge.edge = newEdge;
				return;
			}
			tmp = tmp->next;
		}
	}

	std::size_t getEdgeCount(TVertex srcVertex) const {
		std::size_t count = 0;
		auto node = _graph[getVertexIndexOrThrow(srcVertex)].edges;
		while (node) {
			++count;
			node = node->next;
		}
		return count;
	}

	Edge getEdge(TVertex srcVertex, std::size_t index) const {
		std::size_t count = 0;
		auto node = _graph[getVertexIndexOrThrow(srcVertex)].edges;
		for (size_t i = 0; i < index; ++i)
			node = node->next;
		return node->edge;
	}



	void print() const { //функция вывода, требующая перегруженный оператор вывода
		for (auto i = 0; i != _count; ++i) {
			std::cout << "[" << i + 1 << "]: ";
			std::cout << _graph[i].vertex;
			std::cout << "->";
			auto tmp = _graph[i].edges;
			while (tmp) {
				cout << tmp->edge.dstVertex;
				cout <<  "(";
				cout << tmp->edge.edge;
				cout << " km)->";
				tmp = tmp->next;
			}
			cout << "|";
			std::cout << std::endl;
		}
	}
};

template <typename TVertex, typename TEdge, typename TFunctional>
void depthFirstSearch(const Graph<TVertex, TEdge>& graph, TVertex begin, TFunctional f) {
	const auto n = graph.getVertexCount();
	auto visited = new bool[n];
	auto stack = new std::size_t[n];
	std::size_t stackSize = 0;
	for (std::size_t i = 0; i < n; ++i) {
		visited[i] = false;
	}

	try {
		const auto beginIndex = graph.getVertexIndexOrThrow(begin);
		stack[stackSize++] = beginIndex;
		visited[beginIndex] = true;

		while (stackSize > 0) {
			const auto vertexIndex = stack[--stackSize];
			const auto vertex = graph.getVertex(vertexIndex);
			f(vertex);
			const auto edgeCount = graph.getEdgeCount(vertex);
			for (std::size_t edgeIndex = 0; edgeIndex < edgeCount; ++edgeIndex) {
				const auto dstIndex = graph.getVertexIndexOrThrow(graph.getEdge(vertex, edgeIndex).dstVertex);
				if (!visited[dstIndex]) {
					stack[stackSize++] = dstIndex;
					visited[dstIndex] = true;
				}
			}

		}
	}
	catch (...) {
		delete[] visited;
		delete[] stack;
		throw;
	}
	delete[] visited;
	delete[] stack;
}

template<typename TVertex, typename TEdge, typename TFunctional>
void recursiveDepthFirstSearch(const Graph<TVertex, TEdge>& graph, TVertex begin, bool* visited, TFunctional f) { //рекурсивная версия
	try {
		const auto beginIndex = graph.getVertexIndexOrThrow(begin);//запрашивем индекс этой вершины
		visited[beginIndex] = true;//начальная вершина посещена
		f(begin);//делаем какой-то функционал
		const int edgeCount = graph.getEdgeCount(begin);//получаем кол-во смежных ребер(вершин)
		for (int edgeIndex = edgeCount - 1; edgeIndex >= 0; --edgeIndex) { //обходим все эти ребра
			const auto dstIndex = graph.getVertexIndexOrThrow(graph.getEdge(begin, edgeIndex).dstVertex);//индекс очередного ребенка
			if (!visited[dstIndex]) {//если смежная вершина не посещена,то помещаем ее в стэк
				TVertex beg = graph.getVertex(dstIndex);
				recursiveDepthFirstSearch(graph, beg, visited, f);
			}
		}
	}
	catch (...) { //если возникло исключение чистим память и бробрасываем искл наверх
		throw; //попадаем в мэйн
	}
}



template<typename TVertex, typename TEdge, typename TFunctional>
void breadthFirstSearch(const Graph<TVertex, TEdge>& graph, TVertex begin, TFunctional f) {
	const auto n = graph.getVertexCount();
	auto visited = new bool[n];
	auto queue = new std::size_t[n];
	std::size_t push = 0;
	std::size_t pop = 0;
	for (std::size_t i = 0; i < n; ++i) {
		visited[i] = false;
	}

	try {
		const auto beginIndex = graph.getVertexIndexOrThrow(begin);
		queue[push++] = beginIndex;
		visited[beginIndex] = true;

		while (push != pop) {
			const auto vertexIndex = queue[pop++];
			const auto vertex = graph.getVertex(vertexIndex);
			f(vertex);
			const auto edgeCount = graph.getEdgeCount(vertex);
			for (std::size_t edgeIndex = 0; edgeIndex < edgeCount; ++edgeIndex) {
				const auto destinationIndex = graph.getVertexIndexOrThrow(graph.getEdge(vertex, edgeIndex).dstVertex);
				if (!visited[destinationIndex]) {
					queue[push++] = destinationIndex;
					visited[destinationIndex] = true;
				}
			}

		}
	}
	catch (...) {
		delete[] visited;
		delete[] queue;
		throw;
	}
	delete[] visited;
	delete[] queue;
}

template<typename TEdge>
struct defaultEdgeWeight {
	float operator()(TEdge edge) {
		return static_cast<float>(edge);
	}
};

const auto INFINITY_DISTANCE = std::numeric_limits<float>::infinity();

template<typename TVertex, typename TEdge, typename TEdgeWeight = defaultEdgeWeight<TEdge>>
float dijkstra(const Graph<TVertex, TEdge> & graph, TVertex begin, TVertex end, TVertex * path,
	std::size_t * pathLength) {
	const auto n = graph.getVertexCount();
	auto d = new float[n];
	auto u = new bool[n];
	auto p = new std::size_t[n];
	for (std::size_t i = 0; i < n; ++i) {
		d[i] = INFINITY_DISTANCE;
		u[i] = false;
		p[i] = n;
	}

	try {
		const auto beginIndex = graph.getVertexIndexOrThrow(begin);
		d[beginIndex] = 0;

		for (std::size_t i = 0; i < n; ++i) {
			// ЭТАП 1: Выбрать непомеченную вершину с минимальными расстоянием
			std::size_t selectedIndex = n;
			float selectedDistance = INFINITY_DISTANCE;
			for (std::size_t j = 0; j < n; ++j) {
				if (!u[j] && d[j] < selectedDistance) {
					selectedIndex = j;
					selectedDistance = d[j];
				}
			}
			if (selectedIndex == n)
				break;
			u[selectedIndex] = true;

			// ЭТАП 2: Для всех смежных ребёр выбранной вершины провести релаксацию
			const auto selectedVertex = graph.getVertex(selectedIndex);
			const auto edgeCount = graph.getEdgeCount(selectedVertex);
			for (std::size_t j = 0; j < edgeCount; ++j) {
				const auto edge = graph.getEdge(selectedVertex, j);
				const auto dstVertex = edge.dstVertex;
				const auto destinationIndex = graph.getVertexIndexOrThrow(dstVertex);
				const auto distance = d[selectedIndex] + TEdgeWeight()(edge.edge);
				if (distance < d[destinationIndex]) {
					d[destinationIndex] = distance;
					p[destinationIndex] = selectedIndex;
				}
			}
		}

		const auto endIndex = graph.getVertexIndexOrThrow(end);
		const auto distance = d[endIndex];
		*pathLength = 0;
		if (distance != INFINITY_DISTANCE && path != nullptr) {
			auto currentIndex = endIndex;
			while (currentIndex != beginIndex) {
				path[(*pathLength)++] = graph.getVertex(currentIndex);
				currentIndex = p[currentIndex];
			}
			path[(*pathLength)++] = begin;
			std::reverse(path, path + *pathLength);
		}
		delete[] d;
		delete[] u;
		delete[] p;
		return distance;
	}
	catch (...) {
		delete[] d;
		delete[] u;
		delete[] p;
		throw;
	}
}

template<typename TVertex, typename TEdge, typename TEdgeWeight = defaultEdgeWeight<TEdge>>
float bellmanFord(const Graph<TVertex, TEdge> & graph,
	TVertex begin,
	TVertex end,
	TVertex * path,
	std::size_t * pathLength) {
	const auto n = graph.getVertexCount();
	auto d = new float[n];
	auto p = new std::size_t[n];
	for (std::size_t i = 0; i < n; ++i) {
		d[i] = INFINITY_DISTANCE;
		p[i] = n;
	}

	try {
		const auto beginIndex = graph.getVertexIndexOrThrow(begin);
		d[beginIndex] = 0;

		for (std::size_t i = 0; i < n - 1; ++i) { //перебираем все вершины и их ребра
			for (std::size_t vertexIndex = 0; vertexIndex < n; ++vertexIndex) {
				const auto vertex = graph.getVertex(vertexIndex);
				const auto edgeCount = graph.getEdgeCount(vertex);
				for (std::size_t edgeIndex = 0; edgeIndex < edgeCount; ++edgeIndex) {
					const auto edge = graph.getEdge(vertex, edgeIndex);
					const auto dstVertex = edge.dstVertex;
					const auto destinationIndex = graph.getVertexIndexOrThrow(dstVertex);
					const auto distance = d[vertexIndex] + TEdgeWeight()(edge.edge);
					if (distance < d[destinationIndex]) {
						d[destinationIndex] = distance;
						p[destinationIndex] = vertexIndex;

					}
				}
			}
		}

		const auto endIndex = graph.getVertexIndexOrThrow(end);
		const auto distance = d[endIndex];
		*pathLength = 0;
		if (distance != INFINITY_DISTANCE && path != nullptr) {
			auto currentIndex = endIndex;
			while (currentIndex != beginIndex) {
				path[(*pathLength)++] = graph.getVertex(currentIndex);
				currentIndex = p[currentIndex];
			}
			path[(*pathLength)++] = begin;
			std::reverse(path, path + *pathLength);
		}
		delete[] d;
		delete[] p;
		return distance;
	}
	catch (...) {
		delete[] d;
		delete[] p;
		throw;
	}
}