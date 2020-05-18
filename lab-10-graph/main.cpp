#include <iostream>
#include "graph.h"
#include "locality.h"

using namespace std;

int main() {
	Graph<Locality*, double> graph;

	Locality a("Togliatty", 700000);
	Locality b("Samara", 13000000);
	Locality c("Syzran", 173000);
	Locality d("Novokuibyshevsk", 100000);
	Locality e("Chapaevsk", 73000);
	Locality f("Zhigulevsk", 54000);


	try {
		graph.addVertex(&a);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addVertex(&b);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addVertex(&c);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addVertex(&d);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addVertex(&e);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addVertex(&f);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}


	try {
		graph.addEdge(&a, &b, 60);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&a, &c, 70);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&b, &c, 100);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&c, &a, 75);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&c, &d, 110);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&d, &e, 35);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&d, &f, 40);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&f, &c, 40);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&d, &b, 10);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&f, &d, 10);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.addEdge(&e, &f, 15);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}


	cout << "The graph will be look like:" << endl;
	try {
		graph.print();
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}


	try {
		cout << "Depth:" << endl;
		depthFirstSearch(graph, &a, [](auto vertex) {
			cout<<vertex<<endl;
			});
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}


	const auto n = graph.getVertexCount();
	auto visited = new bool[n]; //что уже посещено(посещена ли итая вершина или нет)
	for (size_t i = 0; i < n; ++i) { //изначально ничего не посещено
		visited[i] = false;
	}
	try {
		cout << "Depth (recursive):" << endl;
		recursiveDepthFirstSearch(graph, &a, visited, [](auto vertex) {
			cout<<vertex<<endl;
			});
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		cout << "Breadth: " << endl;
		breadthFirstSearch(graph, &a, [](auto vertex) {
			cout << vertex << endl;
			});
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	try {
		graph.editEdge(&a, &b, 50);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	
	const auto src = &a;
	const auto dst = &e;
	try {
		Locality* path[11];
		size_t length = 0;
		cout << dijkstra(graph, src, dst, path, &length) << ": ";
		for (size_t i = 0; i < length; ++i) {
			cout << path[i] << ' ';
		}
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}

	try {
		Locality* path[11];
		size_t length = 0;
		cout << bellmanFord(graph, src, dst, path, &length) << ": ";
		for (size_t i = 0; i < length; ++i) {
			cout << path[i] << ' ';
		}
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}

	cout << "The graph after changing the path between first and second elementss"<< endl;
	try {
		graph.print();
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	

	Locality w("Kinel", 35000);
	try {
		graph.editVertex(&a, &w);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	

	cout << "The graph after changing the first element" << endl;

	try {
		graph.print();
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	
	
	try {
		graph.eraseVertex(&c);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}

	cout << "The graph after erasing the 3rd element" << endl;
	
	try {
		graph.print();
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	
	
	
	try {
		graph.eraseEdge(&w, &b);
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
	
	cout << "The graph after erasing edge between 1std and 2nd element" << endl;
	
	try {
		graph.print();
		cout << endl;
	}
	catch (const exception& ex) {
		cout << ex.what();
	}
		return 0;
}
