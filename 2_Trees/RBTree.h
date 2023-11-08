/*
* Header file for Red-Black Tree implementation - using Node objects
* Jacob Schuetter
* Created 11 October 2023
*/

#include <stdlib.h>
#include "Node.h"

using namespace std;

#ifndef RBTREE_H
#define RBTREE_H

class RBTree {
public:
	friend class Node;

	//Default constructor
	RBTree();
	//Alternate constructor
	RBTree(Node* rt);

	//Insertion and deletion
	void ins(int val);
	void del(Node* n);
	void del(int val);

	//Helper functions
	void lRotate(Node* rt);
	void rRotate(Node* rt);
	void insFix(Node* n);
	void delFix(Node* n);
	void graft(Node* n, Node* subRt);

	//Searching
	Node* find(int val);
	Node* find(int val, Node* start);
	Node* min();
	Node* min(Node* rt);
	Node* max();
	Node* max(Node* rt);

	void read();
	void read(Node* n);

	//Setter function
	void setRoot(Node* rt);

	//Getter function
	Node* getRoot();
	Node* getLeaf();

	void print(Node* n);
	//int height();

private:
	Node* root;  //Ptr to root of tree
	Node* nl;  //Common null leaf node
};

#endif