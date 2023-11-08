/*
* Header file for binary search tree:node object-based implementation
* Jacob Schuetter
* Created 11 October 2023
*/

#include <stdlib.h>
#include <string>
#include "Node.h"
using namespace std;

#ifndef BSTREE_H
#define BSTREE_H

class BSTree {
public:
	friend class Node;

	//Default constructor
	BSTree();
	//Alternative constructors
	BSTree(Node* rt);

	void ins(int val);
	//void ins(Node* n);
	void del(Node* n);
	void del(int val);
	void graft(Node* n, Node* subRt);

	Node* find(int val);
	Node* find(int val, Node* start);
	Node* max();
	Node* max(Node* start);
	Node* min();
	Node* min(Node* start);

	//Setter functions
	void setRoot(Node* rt);

	//Getter functions
	Node* getRoot();

private:
	Node* root;  //Ptr to root of tree
};

#endif