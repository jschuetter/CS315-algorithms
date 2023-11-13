/*
* Header file for Graph data structure
* Adjacency list implementation
* Takes string as node identifier
* Jacob Schuetter
* 3 Nov 2023
* History: 
*	3-Nov: Removed template class and specified node type as 'string'
*	6-Nov: Restored template class
*	* Decided not to implement inQueue member for each node - too complex with array implemented tree
*/

#include <stdlib.h>
#include <unordered_map>
#include <utility>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

template <class T = string>
class Graph {
public:
	//Constructor
	Graph();

	//Member functions
	//Unweighted graphs
	void bfs(T src);
	vector<T> bfs_findPath(T src, T dest);
	vector<vector<T>> bfs_findPath(T src, vector<T> dest);

	//Weighted graphs
	void dijkstra(T src);
	vector<T> dijkstra_findPath(T src, T dest);
	vector<vector<T>> dijkstra_findPath(T src, vector<T> dest);

	//Find MSTs
	void prim(T src);

	//Misc. member functions
	void printPaths(vector<T> path);
	void printPaths(vector<vector<T>> paths);

	void build(string vertPath, string edgePath);
	void print();
	void insEdge(T srcKey, T destKey, int wt);
	void insNode(T key);
	int delEdge(T srcKey, T destKey, bool delBoth = true);
	int findEdge(T srcKey, T destKey);

	//Getter functions
	unordered_map<T, unordered_map<T, int>> getEdges();
	unordered_map<T, T> getPredecessors();
	unordered_map<T, int> getDistance();
	//Delete node (& corresponding edges)?

private:
	unordered_map<T, unordered_map<T, int>> edges; //Map of vertices to list of edges (listed as pair of destination, weight)

	unordered_map<T, T> pre;  //Stores predecessor node of each node according to last-run algorithm
	unordered_map<T, int> d;  //Stores length of shortest path to each node according to last-run algorithm

	vector<T> bfs_findPath(T src, T dest, vector<T> p); //Private version of bfs_findPath function - run in recursive calls
	vector<T> dijkstra_findPath(T src, T dest, vector<T> p);

	void setWeight(T src, T dest);  //Helper function for Dijkstra algorithm
};

#endif