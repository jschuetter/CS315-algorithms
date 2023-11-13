/*
* Implementation of Graph class
* Adjacency list implementation
* Jacob Schuetter
* Created 3 Nov 2023
* History: 
*	6-Nov: added BFS
*	8-Nov: added bfs_printPath
*	8-Nov: added multiple overflow functions for bfs_printPath for ease of testing and general use
*	8-Nov: changed return type of bfs_printPath functions from void to vector<T> (or vector<vector<T>>) to aid with print formatting
*   8-Nov: changed bfs_printPath to bfs_findPath to avoid confusion; added additional helper function printPath_unweighted
*	8-Nov: changed predecessor and distance from function parameters to class data members
*	8-Nov: changed type of "edges" data member from unordered_map<T, list<pair<T, int>>> to unordered_map<T, unordered_map<T, int>>
*	8-Nov: added line to set distance to src node to 0 in dijkstra algorithm (*not in pseudocode!)
*	9-Nov: changed printPath_unweighted to printPath_weighted
*	9-Nov: added getter functions for all data members
*/

#include <stdlib.h>
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <utility>
#include "Graph.h"
#include "PQueue.h"
#include "PQueue.cpp"

using namespace std;

//Default constructor
template <class T>
Graph<T>::Graph()
{
}

/*
* Breadth-first search -- Iterates through an *unweighted* graph 
* and finds the shortest path from the given source node to all other nodes
* 
* @param type src: source node
* @param u_map<type, type>& pre: map of node to predecessor node (stores previous step in shortest path)
* @param u_map<type, int>& d: map of node to length of shortest path
*/
template<class T>
void Graph<T>::bfs(T src)
{
	//Initialize auxiliary data structures
	//Stores the color of each node: 
	//0 - white
	//1 - grey
	//2 - black
	unordered_map<T, int> color;

	pre.clear();
	d.clear();
	for (auto it = edges.begin(); it != edges.end(); it++) {
		color.insert(make_pair(it->first, 0));
		d.insert(make_pair(it->first, INT_MAX));
	}

	//Initialize at source node
	color[src] = 1;
	d[src] = 0;
	//Initialize source predecesor??

	//Initialize queue to iterate through each node
	queue<T> q;
	q.push(src);
	while (!q.empty()) {
		//Select next node in queue and get list of adjacent edges
		T nd = q.front();
		q.pop();

		//Iterate over all adjacent nodes
		for (auto it = edges[nd].begin(); it != edges[nd].end(); it++) {
			//If node is undiscovered, set color to grey and update distance/predecessor
			T cur = it->first;
			if (color[cur] == 0) {
				color[cur] = 1;
				d[cur] = d[nd] + 1;
				pre[cur] = nd;
				q.push(cur);
			}
		}
		//Set node color to black - now fully examined
		color[nd] = 2;
	}

}

/*
* Prints the shortest path between two given nodes, according to BFS function
* @param type src: source node key
* @param type dest: destination node key
* @return vector<T>: shortest path
*/
template<class T>
vector<T> Graph<T>::bfs_findPath(T src, T dest)
{
	//Call BFS to get paths
	bfs(src);

	//Create vector to store shortest path
	vector<T> p;

	if (src == dest) {
		//cout << "Shortest path: " << src;
		p.push_back(src);
	}
	else if (pre.count(dest) == 0) {
		cout << "No path from " << src << " to " << dest << " exists.\n";
	}
	else {
		p = bfs_findPath(src, pre[dest], p);
		p.push_back(dest);
		//cout << ", " << dest;
	}
}

/*
* Prints the shortest path between a source and each node in the destination vector, according to BFS function
* @param type src: source node key
* @param vector<type> dest: destination node keys
* @return vector<vector<type>>: vector of shortest paths
*/
template<class T>
vector<vector<T>> Graph<T>::bfs_findPath(T src, vector<T> dest)
{	
	//Call BFS to get paths
	bfs(src);

	//Create vector to store shortest path
	vector<vector<T>> paths;

	//Print paths for all destinations
	for (auto it = dest.begin(); it != dest.end(); it++) {
		vector<T> p;
		if (src == *it) {
			//cout << "Shortest path: " << src;
			p.push_back(src);
		}
		else if (pre.count(*it) == 0) {
			cout << "No path from " << src << " to " << *it << " exists.\n";
		}
		else {
			p = bfs_findPath(src, pre[*it], p);
			p.push_back(*it);
			//cout << ", " << *it;
		}
		paths.push_back(p);
	}

	return paths;
}

/*
* Prints the shortest path between two given nodes, according to BFS function --
* N.B. private function: only used in recursion for main bfs_findPath function
* @param type src: source node key
* @param type dest: destination node key
* @param vector<type> p: vector storing current shortest path
* @return vector<T>: shortest path
*/
template<class T>
vector<T> Graph<T>::bfs_findPath(T src, T dest, vector<T> p)
{
	if (src == dest) {
		//cout << "Shortest path: " << src;
		p.push_back(src);
	}
	else if (pre.count(dest) == 0) {
		cout << "No path from " << src << " to " << dest << " exists.\n";
	}
	else {
		p = bfs_findPath(src, pre[dest], p);
		p.push_back(dest);
		//cout << ", " << dest;
	}

	return p;
}

/*
* Prints the shortest path between two given nodes, according to Dijkstra function --
* N.B. private function: only used in recursion for main dijkstra_findPath function
* @param type src: source node key
* @param type dest: destination node key
* @param vector<type> p: vector storing current shortest path
* @return vector<T>: shortest path
*/
template<class T>
vector<T> Graph<T>::dijkstra_findPath(T src, T dest, vector<T> p)
{
	if (src == dest) {
		//cout << "Shortest path: " << src;
		p.push_back(src);
	}
	else if (pre.count(dest) == 0) {
		cout << "No path from " << src << " to " << dest << " exists.\n";
	}
	else {
		p = dijkstra_findPath(src, pre[dest], p);
		p.push_back(dest);
		//cout << ", " << dest;
	}

	return p;
}

/*
* Dijkstra's Algorithm -- Iterates through a *weighted* graph
* and finds the shortest path from the given source node to all other nodes
*
* @param type src: source node
* @param u_map<type, type>& pre: map of node to predecessor node (stores previous step in shortest path)
* @param u_map<type, int>& d: map of node to length of shortest path
*/
template<class T>
void Graph<T>::dijkstra(T src)
{
	//Initialize auxiliary data structures
	//Stores the color of each node: 
	//0 - white
	//1 - grey
	//2 - black
	unordered_map<T, int> color;

	pre.clear();
	d.clear();
	for (auto it = edges.begin(); it != edges.end(); it++) {
		color.insert(make_pair(it->first, 0));
		d.insert(make_pair(it->first, INT_MAX));
	}

	//Create priority minqueue and populate with every node, using initial weight INT_MAX
	PQueue<T> q;
	for (auto it = edges.begin(); it != edges.end(); it++) {
		q.enqueue(it->first, INT_MAX);
	}

	q.decKey(src, 0);

	while (!q.isEmpty()) {
		//Get current node from queue and find all adjacent nodes
		T nd = q.dequeue();
		//unordered_map<T, int> adj = edges[nd];

		//Iterate through adjacent nodes
		for (auto it = edges[nd].begin(); it != edges[nd].end(); it++) {
			T curNd = it->first;
			int edgeWeight = (edges[nd])[curNd];
			//cout << nd << "-" << curNd << ": " << edgeWeight << endl;

			//EDGE_RELAX method: 
			//If traversing through current node gives shorter path, update distance of neighbor
			if (d[curNd] > (d[nd] + edgeWeight)) {
				d[curNd] = d[nd] + edgeWeight;
				pre[curNd] = nd;
				q.decKey(curNd, d[curNd]);
			}
		}
	}
}

/*
* Prints the shortest path between a source and each node in the destination vector, according to Dijkstra's algorithm
* @param type src: source node key
* @param type dest: destination node key
* @return vector<type>: vector of nodes in shortest path
*/
template<class T>
vector<T> Graph<T>::dijkstra_findPath(T src, T dest)
{
	//Call Dijkstra's to get paths
	dijkstra(src);

	//Create vector to store shortest path and int to store weight
	vector<T> p;

	if (src == dest) {
		//cout << "Shortest path: " << src;
		p.push_back(src);
	}
	else if (pre.count(dest) == 0) {
		cout << "No path from " << src << " to " << dest << " exists.\n";
	}
	else {
		p = dijkstra_findPath(src, pre[dest], p);
		p.push_back(dest);
		//cout << ", " << dest;
	}
	return p;
}

/*
* Prints the shortest path between a source and each node in the destination vector, according to Dijkstra's algorithm
* @param type src: source node key
* @param vector<type> dest: destination node keys
* @return vector<vector<type>>: vector of shortest paths
*/
template<class T>
vector<vector<T>> Graph<T>::dijkstra_findPath(T src, vector<T> dest)
{
	//Call BFS to get paths
	dijkstra(src);

	//Create vector to store shortest path
	vector<vector<T>> paths;

	//Print paths for all destinations
	for (auto it = dest.begin(); it != dest.end(); it++) {
		vector<T> p;
		if (src == *it) {
			//cout << "Shortest path: " << src;
			p.push_back(src);
		}
		else if (pre.count(*it) == 0) {
			cout << "No path from " << src << " to " << *it << " exists.\n";
		}
		else {
			p = dijkstra_findPath(src, pre[*it], p);
			p.push_back(*it);
			//cout << ", " << *it;
		}
		paths.push_back(p);
	}

	return paths;
}


/* 
* Finds a minimum spanning tree (MST) using Prim's algorithm
* @param type src: source node for MST
*/
template<class T>
void Graph<T>::prim(T src)
{
	pre.clear();
	//Create priority minqueue and populate with every node, using initial weight INT_MAX
	PQueue<T> q;
	for (auto it = edges.begin(); it != edges.end(); it++) {
		q.enqueue(it->first, INT_MAX);
	}

	q.decKey(src, 0);

	while (!q.isEmpty()) {
		T nd = q.dequeue();
		for (auto it = edges[nd].begin(); it != edges[nd].end(); it++) {
			T curNd = it->first;
			int edgeWeight = (edges[nd])[curNd];
			//Set new precursor if weight is less than edge from previous precursor
			if (q.count(curNd) && edgeWeight < q.getPriority(curNd)) { //Change getPriority function?
				pre[curNd] = nd;
				q.decKey(curNd, edgeWeight);
			}
		}
	}
}

/*
* Prints a path as returned from bfs_findPaths
* @param vector<type> path: path vector from bfs_findPaths
*/
template<class T>
void Graph<T>::printPaths(vector<T> path)
{
	cout << path.front() << " -> " << path.back() << ": \n";
	cout << path.front();
	for (auto j = path.begin() + 1; j != path.end(); j++) {
		cout << ", " << *j;
	}
	cout << endl << endl;
}

/*
* Prints multiple paths as returned from bfs_findPaths
* @param vector<vector<type>> paths: vector of path vectors from bfs_findPaths
*/
template<class T>
void Graph<T>::printPaths(vector<vector<T>> paths)
{
	for (auto i = paths.begin(); i != paths.end(); i++) {
		cout << i->front() << " -> " << i->back() << ": \n";
		cout << i->front();
		for (auto j = i->begin() + 1; j != i->end(); j++) {
			cout << ", " << *j;
		}
		cout << endl << endl;
	}
}

/*
* Builds a graph from two .csv files
* @param string vertPath: path to .csv containing vertices (delim '\n')
* @param string edgePath: path to .csv containing edges (format: source,destination,weight)
*/
template <class T>
void Graph<T>::build(string vertPath, string edgePath)
{
	list<string> empty; //Empty list for initializing verts in Graph object

	ifstream vertIn(vertPath);
	ifstream edgeIn(edgePath);
	if (!vertIn.good() || !edgeIn.good()) {
		cout << "Bad file\n";
		return;
	}

	//Declare variables to hold vertex value and list of edges
	string vert;

	//Initialize all vertices in map
	while (!vertIn.eof()) {
		//Get vertex from input file 
		getline(vertIn, vert, '\n');
		edges[vert];
	}

string src, dest, weight;
int w;
//Initialize all edges
while (!edgeIn.eof()) {
	//Get edge source, destination, and weight from input file
	streamsize maxIn = 144;
	getline(edgeIn, src, ',');
	getline(edgeIn, dest, ',');
	getline(edgeIn, weight, '\n');
	w = stoi(weight);

	insEdge(src, dest, w);
	insEdge(dest, src, w);
}

}

//Prints Graph in adjacency list format
template <class T>
void Graph<T>::print()
{
	cout << setw(15) << "Vertices: " << " | Adjacent vertices (weight): \n";
	cout << endl;
	for (auto it = edges.begin(); it != edges.end(); it++) {
		cout << setw(15) << it->first << " | ";
		unordered_map<string, int> edgeLi = it->second;
		for (auto li = it->second.begin(); li != it->second.end(); li++) {
			string dest = li->first;
			int wt = li->second;
			cout << li->first << " (" << li->second << "), ";
		}
		cout << endl;
	}
}

/*
* Inserts a new edge into the graph. If the given source node does not exist, it is created.
* @param type srcKey: string key of source node
* @param type destKey: string key of destination node (n.b. may or may not exist!)
* @param int wt: weight of the edge being created
*/
template <class T>
void Graph<T>::insEdge(T srcKey, T destKey, int wt)
{
	edges[srcKey].insert(make_pair(destKey, wt));
}

/*
* Inserts a new node into the graph
* @param type key: value of new node to insert
*/
template <class T>
void Graph<T>::insNode(T key)
{
	edges[key];
}

/*
* Finds and deletes an edge in the graph
* @param type srcKey: key of edge source
* @param type destKey: key of edge destination
* @param bool delBoth: determines whether to edge in both directions (default = true)
* @return int: returns 0 if two edges are deleted, returns 1 if one is deleted, returns 2 if none are deleted
*/
template <class T>
int Graph<T>::delEdge(T srcKey, T destKey, bool delBoth)
{
	list<pair<T, int>> newEdges = edges[srcKey];
	int edge1, edge2 = 0;

	//Find edge to delete
	auto it = newEdges.begin();
	while (it->first != destKey && it != newEdges.end()) it++;
	//Delete edge if it exists
	if (it->first == destKey) {
		newEdges.erase(it);
		edges[srcKey] = newEdges;
		edge1 = 0;
	}
	else edge1 = 1;

	//Delete corresponding (reverse) edge if called for
	if (delBoth) edge2 = delEdge(destKey, srcKey, false);

	return edge1 + edge2;
}

/*
* Tests for existence of an edge
* @param type srcKey: key of edge source
* @param type destKey: key of edge destination
* @return int: returns weight of edge (if it exists), or -1 (if it does not exist)
*/
template <class T>
int Graph<T>::findEdge(T srcKey, T destKey)
{
	list<pair<T, int>> li = edges[srcKey];
	auto it = li.begin();
	while (it->first != destKey && it != li.end()) it++;
	
	//Return edge weight, if found
	if (it->first == destKey) return it->second;
	else return -1;
}

//Getter function for data member 'edges'
template<class T>
unordered_map<T, unordered_map<T, int>> Graph<T>::getEdges()
{
	return edges;
}

//Getter function for data member 'pre'
template<class T>
unordered_map<T, T> Graph<T>::getPredecessors()
{
	return pre;
}

//Getter function for data member 'd'
template<class T>
unordered_map<T, int> Graph<T>::getDistance()
{	
	return d;
}



//Changes the weight of the edge between the two given nodes
template<class T>
void Graph<T>::setWeight(T src, T dest)
{
	int edgeWeight = edges[src][dest];
	cout << src << "-" << dest << ": " << edgeWeight << endl;
	if (d[dest] > (d[src] + edgeWeight)) {
		d[dest] = d[src] + edgeWeight;
		pre[dest] = src;
	}
}
