/*
* Implementation of Tree class from header file Tree.h
* Jacob Schuetter
* Created 3 Nov 2023
*/

#include <stdlib.h>
#include "Tree.h"
using namespace std;

template<class T>
Tree<T>::Tree()
{
	root = nullptr;
}

template<class T>
Tree<T>::Tree(Node<T>* rt)
{
	root = rt;
}

/*
* Inserts a new node containing the given value at the next open position in the tree
*/
template<class T>
void Tree<T>::ins(T val)
{

}

