/*
* Implementation of Minheap class
* Implemented using array-based tree implementation
* Jacob Schuetter
* Created 3 Nov 2023
* History:
*	3-Nov: Switched from Node-based to array-based implementation
*	8-Nov: Changed return condition in Minheap::find to it == vals.end() to handle null iterator runtime exception
*	9-Nov: Added member functions 'weight' and 'count'
*/

#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>
#include "Minheap.h"

using namespace std;

//Constructors
template<class T>
Minheap<T>::Minheap()
{
	vals;
	//s = 0;
}
template<class T>
Minheap<T>::Minheap(T rt, int key)
{
	vals.push_back(make_pair(rt, key));
	//s = 1;
	//root->left = next;
}

/*
* Iterates over all elements in input array to build minheap
* @param input: vector of elements composing minheap
*/
template<class T>
void Minheap<T>::build(vector<T> input)
{
	double val = vals.size() - 1;
	int start = floor(val / 2);
	for (int i = vals.size() - 1; i > 0; i--) {
		fix(i);
	}
}

/*
* Restores minheap properties to subset of unorganized array
* Used in building and extracting from heap
* @param rt: index of root node of subtree to fix
*/
template<class T>
void Minheap<T>::fix(int rt)
{
	int left = l(rt);
	int right = r(rt);
	int indSmallest;
	
	if (left < vals.size() && vals[left].second < vals[rt].second) indSmallest = left;
	else indSmallest = rt;

	if (right < vals.size() && vals[right].second < vals[rt].second) indSmallest = right;
	
	if (indSmallest != rt) {
		Swap(rt, indSmallest);
		fix(indSmallest);
	}
}

/*
* Returns the index of an element in the heap
* @param type val: element to find
* @return int: index of val
*/
template<class T>
int Minheap<T>::find(T val)
{
	auto it = vals.begin();
	int i = 0; //Store index of value
	while (it != vals.end() && it->first != val) {
		it++;
		i++;
	}

	if (it == vals.end()) return -1;
	else return i;
}

/*
* Returns the number of elements matching the given key
* @param type val: key to find
* @return int: number of element matching val (0 if not in queue)
*/
template<class T>
int Minheap<T>::count(T val)
{
	int cnt = 0;
	for (auto it = vals.begin(); it != vals.end(); it++) {
		if (it->first == val) cnt++;
	}
	return cnt;
}

/*
* Inserts a new node into the heap
* @param val: value to be inserted
*/
template<class T>
void Minheap<T>::ins(T val, int key)
{
	vals.push_back(make_pair(val, INT_MAX));
	decKey(vals.size() - 1, key);
}

/*
* Increases the value of some member of the heap
* @param index: index of element to change
* @param key: new value of element
*/
template<class T>
void Minheap<T>::decKey(int index, int key)
{
	vals[index].second = key;
	while (index > 0 && vals[index].second < vals[p(index)].second) {
		Swap(index, p(index));
		index = p(index);
	}
}


//Returns and removes minimum value element from heap
template<class T>
T Minheap<T>::getMin()
{
	T min = vals.front().first;
	vals.front() = vals.back();
	vals.pop_back();
	fix(0);
	return min;
}

//Removes all elements from heap
template<class T>
void Minheap<T>::clear()
{
	vals.clear();
}

/*
* Gets parent index of given index
* @param e: index of child element
* @return int: index of parent element (-1 if not found)
*/
template<class T>
int Minheap<T>::p(int e)
{
	int p = (e - 1) / 2;
	if (p >= 0 && p < vals.size()) return p;
	else return -1;
}

/*
* Gets left child index of given index
* @param e: index of parent element
* @return int: index of child element (-1 if not found)
*/
template<class T>
int Minheap<T>::l(int e)
{
	int l = (2 * e) + 1;
	if (l >= 0 && l < vals.size()) return l;
	else return -1;
}

/*
* Gets right child index of given index
* @param e: index of parent element
* @return int: index of child element (-1 if not found)
*/
template<class T>
int Minheap<T>::r(int e)
{
	int r = (2 * e) + 2;
	if (r >= 0 && r < vals.size()) return r;
	else return -1;
}

//Returns size of value vector
template<class T>
int Minheap<T>::size()
{
	return vals.size();
}

/*
* Gets the weight of a given term in the heap.
* @param type val: element to find
* @return int: weight of val; -1 if not found
*/
template<class T>
int Minheap<T>::weight(T val)
{
	int index = find(val);
	if (index == -1) return -1;
	int wt = vals[index].second;
	return wt;
}

//Prints all elements in heap (\n-delimited) with weights in parentheses
template<class T>
void Minheap<T>::print()
{
	cout << "Heap values: \n";
	for (auto it = vals.begin(); it != vals.end(); it++) {
		cout << it->first << " (" << it->second << "), ";
	}
	cout << endl;
}

//Returns true if heap is empty
template<class T>
bool Minheap<T>::isEmpty()
{
	if (vals.empty()) return true;
	else return false;
}

//Swaps two elements of the vector
template<class T>
void Minheap<T>::Swap(int i1, int i2)
{
	pair<T, int> temp = vals[i1];
	vals[i1] = vals[i2];
	vals[i2] = temp;
}
