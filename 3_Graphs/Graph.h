/*
* Header file for Graph data structure
* Adjacency list implementation
* Takes string as node identifier
* Jacob Schuetter
* 3 Nov 2023
* History: 
*	3-Nov: Removed template class and specified node type as 'string'
*/

#include <stdlib.h>
#include <unordered_map>
#include <list>
#include <utility>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

//MODIFY FOR TEMPLATE CLASS!
template <class T = string>
class Graph {
public:
	//Constructor
	Graph();

	//Member functions
	//Unweighted graphs
	void bfs(T src, unordered_map<T, T>& pre, unordered_map<T, int>& d);
	vector<T> bfs_findPath(T src, T dest);
	vector<vector<T>> bfs_findPath(T src, vector<T> dest);
	void printPaths_unweighted(vector<T> path);
	void printPaths_unweighted(vector<vector<T>> paths);

	//Weighted graphs
	void dijkstra(T src, unordered_map<T, T>& pre, unordered_map<T, int>& d);
	void setWeight(T src, T dest, int weight, unordered_map<T, T>& pre, unordered_map<T, int>& d);


	void build(string vertPath, string edgePath);
	void print();
	void insEdge(T srcKey, T destKey, int wt);
	void insNode(T key);
	int delEdge(T srcKey, T destKey, bool delBoth = true);
	int findEdge(T srcKey, T destKey);

	//Delete node (& corresponding edges) ???

private:
	unordered_map<T, list<pair<T, int>>> edges; //Map of vertices to list of edges (listed as pair of destination, weight)
	//unordered_map<T, T> pre;  //Stores predecessor node of each node according to last-run algorithm
	//unordered_map<T, int> d;  //Stores length of shortest path to each node according to last-run algorithm
	vector<T> bfs_findPath(T src, T dest, unordered_map<T, T>& pre, unordered_map<T, int>& d, vector<T> p);
};

#endif