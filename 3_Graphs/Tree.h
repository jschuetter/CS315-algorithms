/*
* Header file for binary tree:node object-based implementation
* Jacob Schuetter
* Created 11 October 2023
*/

#include <stdlib.h>
#include <string>
#include "Node.h"
using namespace std;

#ifndef TREE_H
#define TREE_H
template <class T>
class Tree {
public:

	//Default constructor
	Tree();
	//Alternative constructors
	Tree(Node* rt);

	void ins(T val);
	void del(Node* n);

	//Setter functions
	void setRoot(Node* rt);

	//Getter functions
	Node* getRoot();

private:
	Node* root;
};
#endif