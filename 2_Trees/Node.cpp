/*
* Purpose: implement nodes objects for use in tree class
* Jacob Schuetter
* Created 11 October 2023
*/

#include <stdlib.h>
#include <iostream>
#include "Node.h"

using namespace std;

//Default ructor
Node::Node()
{
	value = -1;
	p = nullptr;
	l = nullptr;
	r = nullptr;
	black = false;
}
//Alternate ructors
Node::Node(int val)
{
	value = val;
	p = nullptr;
	l = nullptr;
	r = nullptr;
	black = false;
}
Node::Node(int val, Node* parent)
{
	value = val;
	p = parent;
	l = nullptr;
	r = nullptr;
	black = false;
}
Node::Node(int val, Node* parent, Node* left, Node* right)
{
	value = val;
	p = parent;
	l = left;
	r = right;
	black = false;
}

//Setter functions for data members
void Node::setL(Node* newNode)
{
	l = newNode;
}
void Node::setR(Node* newNode)
{
	r = newNode;
}
void Node::setP(Node* newNode)
{
	p = newNode;
}
void Node::setVal(int newVal)
{
	value = newVal;
}
void Node::setBlack(bool col)
{
	black = col;
}

//Getter functions for data members
int Node::getValue()
{
	return value;
}
Node* Node::left()
{
	return l;
}
Node* Node::right()
{
	return r;
}
Node* Node::parent()
{
	return p;
}
bool Node::isBlack()
{
	return black;
}

//Prints value of Node
void Node::printValue()
{
	cout << value << endl;
}
