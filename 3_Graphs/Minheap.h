/*
* Header file for Minheap class 
* Description: Tree data structure such that the root of any given subtree is less than all of its descendants
* Jacob Schuetter
* Created 3 Nov 2023
*/

#include <stdlib.h>
#include <vector>
#include <utility>
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
	int count(T val);
	void ins(T val, int key);
	//Delete node function?
	void decKey(int index, int key);
	//IncreaseKey function?
	T getMin();
	void clear();

	//Getter functions
	int p(int e);
	int l(int e);
	int r(int e);
	int size();
	int weight(T val);

	void print();
	bool isEmpty();

private:
	vector<pair<T, int>> vals;
	void Swap(int i1, int i2);
};

#endif
