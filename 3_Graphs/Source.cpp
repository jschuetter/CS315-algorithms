/*
* CS 315 Programming Assignment 3: Graphs
* Description: Implements Dijkstra's algorithm, along with Graph and minheap implementation
* Jacob Schuetter
* Created 3 Nov 2023
* History: 
*	3-Nov: Implemented testHeap function to ensure functionality
*	6-Nov: Implemented testGraph function with BFS functionality to test Graph class and current member functions
*	8-Nov: Implemented Dijkstra functionality into testGraph function
*/

#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include "Graph.h"
#include "Graph.cpp""
#include "Minheap.h"
#include "Minheap.cpp"
#include "PQueue.h"
//#include "PQueue.cpp"

using namespace std;

const string NODES_PATH = "RomaniaVertices.txt";
const string EDGES_PATH = "RomaniaEdges.txt";

void testHeap(int size);
void testGraph();

int main() {

	//testHeap(10);

	testGraph();

	return 0;
}

//Test heap class - draw trees!
void testHeap(int size) {
	//Generate random vector of numbers
	vector<int> values;
	Minheap<int> heap;
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		int r = rand() % 100;
		values.push_back(r);
		heap.ins(r, r);
	}
	cout << "Values generated: \n";
	for (auto i = values.begin(); i != values.end(); i++) {
		cout << *i << ", ";
	}
	cout << endl;
	heap.print();
}

//Test graph class - all algorithm member functions
void testGraph() {
	Graph<string> romania;
	romania.build(NODES_PATH, EDGES_PATH);
	//cout << "Initial construction\n";
	romania.print();
	cout << endl;

	//Determine which edges to test
	vector<string> destinations = { "Sibiu", "Craiova", "Bucharest" };

	vector<vector<string>> paths = romania.bfs_findPath("Arad", destinations);

	//Print out shortest paths
	cout << "Shortest paths (unweighted): " << endl;
	romania.printPaths(paths);

	//Test Dijkstra's algorithm
	vector<string> pathDijkstra = romania.dijkstra_findPath("Arad", "Bucharest");

	cout << "Shortest path (weighted): " << endl;
	romania.printPaths(pathDijkstra);

	//Test Prim's Algorithm
	romania.prim("Arad");
	unordered_map<string, string> pred = romania.getPredecessors();
	cout << "Prim's Minimum Spanning Tree\n";
	cout << "Source node: Arad\n";
	cout << setw(15) << "Vertex: " << " | Predecesor: \n";
	for (auto it = pred.begin(); it != pred.end(); it++) {
		cout << setw(15) << it->first << " | " << it->second << endl;
	}

}