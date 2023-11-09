/*
* Priority queue header file
* Implemented using binary minheap
* Jacob Schuetter
* Created 3 Nov 2023
*/

#include <stdlib.h>
#include <vector>
#include <utility>
#include "Minheap.h"


using namespace std;

#ifndef PQUEUE_H
#define PQUEUE_H

template <class N>
class PQueue {
public:
	//Constructors
	PQueue();
	//PQueue(vector<pair<N, int>> input);

	//Member functions
	void enqueue(N val, int priority = 0);
	N dequeue();

	void decKey(N val, int key);

	int count(N val);
	int getPriority(N val);

	bool isEmpty();
	void clear();

	void print();
private:
	Minheap<N> queue;
};

#endif