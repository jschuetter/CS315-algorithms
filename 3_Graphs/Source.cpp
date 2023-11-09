/*
* CS 315 Programming Assignment 3: Graphs
* Description: Implements Dijkstra's algorithm, along with Graph and minheap implementation
* Jacob Schuetter
* Created 3 Nov 2023
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

	/*Graph<string> romania;
	romania.build(NODES_PATH, EDGES_PATH);
	romania.print();*/

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
	/*vector<pair<string, string>> testEdges;
	testEdges.push_back(make_pair("Arad", "Sibiu"));
	testEdges.push_back(make_pair("Arad", "Craiova"));
	testEdges.push_back(make_pair("Arad", "Bucharest"));*/
	vector<string> destinations = { "Sibiu", "Craiova", "Bucharest" };

	vector<vector<string>> paths = romania.bfs_findPath("Arad", destinations);

	//Print out shortest paths
	cout << "Shortest paths (unweighted): " << endl;
	romania.printPaths_unweighted(paths);


}