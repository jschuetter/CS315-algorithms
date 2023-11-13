/*
* Implementation for Priority Queue class - minimum priority
* Jacob Schuetter
* Created 6 Nov 2023
* History:
*	9-Nov: added member functions 'count' and 'getPriority'
*/

#include <stdlib.h>
#include <vector>
#include "PQueue.h"
#include "Minheap.h"

using namespace std;

template<class N>
PQueue<N>::PQueue()
{
}

/*
* Adds a new element to the queue and reorganizes by priority
* @param val: value of new element
* @param priority: priority value of element
*/
template<class N>
void PQueue<N>::enqueue(N val, int priority)
{
	queue.ins(val, priority);
}

//Dequeues the top element in the priority queue and returns the value
template<class N>
N PQueue<N>::dequeue()
{
	return queue.getMin();
}

//Changes the key value for an element in the queue
template<class N>
void PQueue<N>::decKey(N val, int key)
{
	int index = queue.find(val); //N.B. inefficient (linear search) - is there a better way to do this?
	
	//Break function if index is not in queue
	if (index == -1) return;
	queue.decKey(index, key);
}

/*
* Returns the number of elements matching the given key
* @param type val: key to find
* @return int: number of element matching val (0 if not in queue)
*/
template<class N>
int PQueue<N>::count(N val)
{
	int cnt = queue.count(val);
	return cnt;
}

/*
* Returns the priority of a given element in the queue
* @param type val: key to find
* @return int: priority of val in queue (-1 if not found)
*/
template<class N>
int PQueue<N>::getPriority(N val)
{
	int p = queue.weight(val);
	return p;
}

//Returns true if queue is empty
template<class N>
bool PQueue<N>::isEmpty()
{
	if (queue.isEmpty()) return true;
	else return false;
}

//Removes all items from queue
template<class N>
void PQueue<N>::clear()
{
	queue.clear();
}

//Prints all elements in queue
template<class N>
void PQueue<N>::print()
{
	queue.print();
}
