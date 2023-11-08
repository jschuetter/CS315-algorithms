/*
* Header file for Minheap class 
* Description: Tree data structure such that the root of any given subtree is less than all of its descendants
* Jacob Schuetter
* Created 3 Nov 2023
*/

#include <stdlib.h>
#include <vector>
#include <utility>
#include "Node.h"
using namespace std;

#ifndef MINHEAP_H
#define MINHEAP_H

template <class T>
class Minheap {

	template <class N> friend class PQueue;

public:
	//Constructors
	Minheap();
	Minheap(T rt, int key);

	//Member functions
	void build(vector<T> input);
	void fix(int rt);
	int find(T val);
	void ins(T val, int key);
	//void del(T val);
	//void del(int index);
	//void del(Node<T>* nd);
	void decKey(int index, int key);
	//bool incKey(T value, int key);
	T getMin();
	void clear();

	//Getter functions
	int p(int e);
	int l(int e);
	int r(int e);
	int size();

	void print();
	bool isEmpty();

	//Node<T>* r(); //Returns ptr to root
	//Node<T>* end(); //Returns ptr to last

private:
	vector<pair<T, int>> vals;
	//int s;
	void Swap(int i1, int i2);
	//Node<T>* root; //Pointer to root of tree
	//Node<T>* last; //Pointer to last inserted node of tree
	//Node<T> next; //Node object holding next open spot
};

#endif
