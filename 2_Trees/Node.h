/*
* Header file for Node class
* Jacob Schuetter
* Created 11 October 2023
*/

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
public:
	friend class BSTree;
	friend class RBTree;

	//Default constructor
	Node();
	//Alternative constructors
	Node(int val);
	Node(int val, Node* parent);
	Node(int val, Node* parent, Node* left, Node* right);

	//Setter functions
	void setL(Node* newNode);
	void setR(Node* newNode);
	void setP(Node* newNode);
	void setVal(int newVal);
	void setBlack(bool col);

	//Getter functions
	int getValue();
	Node* left();
	Node* right();
	Node* parent();
	bool isBlack();
	void printValue();

private:
	int value;
	Node* p;  //Parent Node
	Node* l;  //Left child Node
	Node* r;  //Right child Node
	bool black;	 //Color of node - only used in RBTree
	//false = red  |  true = black
};

#endif