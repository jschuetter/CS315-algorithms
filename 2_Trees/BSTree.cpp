#include <iostream>
#include "BSTree.h"
#include "TreeOps.h"

using namespace std;

//Default constructor
BSTree::BSTree()
{
	root = nullptr;
}

//Alternative constructor
BSTree::BSTree(Node* rt)
{
	root = rt;
}

/*
* Insert a new node of given value into BSTree object
* @param val: integer value to be inserted into tree
*/
void BSTree::ins(int val)
{
	Node* n = new Node(val);
	Node* curNode = root;
	Node* prev = nullptr;
	if (root == nullptr) {
		root = n;
		return;
	}
	while (curNode != nullptr) {
		prev = curNode;
		if (val > curNode->value) {
			curNode = curNode->r;
		}
		else {
			curNode = curNode->l;
		}
	}
	n->p = prev;
	if (n->value > prev->value) {
		prev->r = n;
	}
	else {
		prev->l = n;
	}
}

/*
* Delete a given node from the tree
* @param n: ptr to Node to be deleted
*/
void BSTree::del(Node* n)
{
	//Cases 1-2: if n has 0-1 children, replace with appropriate subtree
	if (n->l == nullptr) graft(n, n->r);
	else if (n->r == nullptr) graft(n, n->l);
	else {
		//Case 3: if n has 2 children, replace with successor
		Node* suc = min(n->r);  //Find min node of right subtree
		if (suc->p != n) {
			//If successor is not a child of n, replace suc with right subtree 
			//so that suc can be moved to n's place
			graft(suc, suc->r);
			suc->r = n->r;  //Replace right subtree of successor with right subtree of n
			suc->r->p = suc;
		}
		graft(n, suc);
		suc->l = n->l;
		suc->l->p = suc;
	}
}

/*
* Delete a given node from the tree
* @param val: integer value to be deleted
*/
void BSTree::del(int val)
{
	Node* n = find(val);
	if (n == nullptr) return void();  //Handle case where val is not in tree
	del(n);
}

/*
* Replaces a node with a subtree from another part of the tree.
* Used in .del function.
* @param n: ptr to Node being replaced
* @param subRt: ptr to root Node of subtree
*/
void BSTree::graft(Node* n, Node* subRt)
{
	if (root == n) root = subRt;
	else if (n == n->p->l) n->p->l = subRt;
	else n->p->r = subRt;
	if (subRt != nullptr) subRt->p = n->p;
}

/*
* Finds a specified value in the tree
* @param val: integer value to find
* @return: ptr to Node containing correct val; null if not found
*/
Node* BSTree::find(int val)
{
	return find(val, root);
}

/*
* Finds a specified value in specific subtree
* @param val: integer value to find
* @param start: ptr to root Node of subtree to search
* @return: ptr to Node containing correct val; null if not found
*/
Node* BSTree::find(int val, Node* start)
{
	Node* ret = start;
	while (ret != nullptr) {
		if (ret->value > val) ret = ret->l;
		else if (ret->value < val) ret = ret->r;
		else break; //If value equals search key
	}
	return ret;
}

//Finds max node in tree
Node* BSTree::max()
{
	return max(root);
}

/*
* Finds max node in specific subtree
* @param start: ptr to root Node of subtree to search
*/
Node* BSTree::max(Node* start)
{
	Node* ret = start;
	while (ret->r != nullptr) ret = ret->r;
	return ret;
}

//Finds min node in tree
Node* BSTree::min()
{
	return min(root);
}

/*
* Finds min node in specific subtree
* @param start: ptr to root Node of subtree to search
*/
Node* BSTree::min(Node* start)
{
	Node* ret = start;
	while (ret->l != nullptr) ret = ret->l;
	return ret;
}

void BSTree::setRoot(Node* rt)
{
	root = rt;
}

Node* BSTree::getRoot()
{
	return root;
}

