#include <iostream>
#include "RBTree.h"

using namespace std;

//Default constructor
RBTree::RBTree()
{
	root = nullptr;
	nl = new Node();
}
//Alternate constructor
RBTree::RBTree(Node* rt)
{
	root = rt;
	nl = new Node();
	root->r = nl;
	root->l = nl;
}

/*
* Inserts given Node object into RBTree object
* @param n: ptr to Node to be inserted into tree
*/
//void RBTree::ins(Node* n)
//{
//	
//
//
//}

/*
* Inserts a new node of given value into RBTree object
* @param val: integer value to be inserted into tree
*/
void RBTree::ins(int val)
{
	//Create new Node using value
	Node* n = new Node(val);

	Node* curNode = root;
	Node* prev = nullptr;
	if (root == nullptr) {
		root = n;
		n->r = nl;
		n->l = nl;
		insFix(n);
		return;
	}
	while (curNode != nl) { //Find place for new node
		prev = curNode;
		if (n->value > curNode->value) curNode = curNode->r;
		else curNode = curNode->l;
	}

	n->p = prev;
	if (prev == nullptr) root = n; //Set root ptr to n if necessary
	else if (n->value > prev->value) prev->r = n;
	else prev->l = n;

	//Set children to null
	n->r = nl;
	n->l = nl;
	
	insFix(n);
}

/*
* Delete a given node from the tree
* @param n: ptr to Node to be deleted
*/
void RBTree::del(Node* n)
{
	Node* suc = n;
	bool ogColor = n->black; //Store original color of node
	Node* fixPtr; //Create ptr for later fixup function - initialized later

	//Cases 1-2: n has 0-1 children -- replace with appropriate subtree
	if (n->l == nl) {
		fixPtr = n->r;
		graft(n, n->r);
	}
	else if (n->r == nl) {
		fixPtr = n->l;
		graft(n, n->l);
	}
	else {
		//Case 3: n has 2 children -- isolate successor and replace (maintaining original colors) 
		suc = min(n->r);
		ogColor = suc->black;
		fixPtr = suc->r;



		if (suc->p == n) fixPtr->p = suc;  //CHECK THIS LINE -- fixptr parent should already be suc 




		else {
			graft(suc, suc->r);
			suc->r = n->r;
			suc->r->p = suc;
		}

		graft(n, suc);
		suc->l = n->l;
		suc->l->p = suc;
		suc->black = n->black;
	}
	
	//Run fixup if node removed was black (potential errors)
	if (ogColor) delFix(fixPtr);  
}
/*
* Delete a given value from the tree
* @param val: integer value to be deleted
*/
void RBTree::del(int val)
{
	Node* n = find(val);
	if (n == nl) return; //Break function if value is not in tree
	del(n);
}

/*
* Rotates tree left around given root node.
* Used as helper function for .ins and .del.
* @param rt: ptr to Node around which to rotate
*/
void RBTree::lRotate(Node* rt)
{
	Node* n = rt->r;
	rt->r = n->l;
	if (n->l != nl && n->l != nullptr) n->l->p = rt;
	n->p = rt->p;

	if (rt->p == nullptr) root = n;  //Set root ptr to n if rt is root of RBTree
	else if (rt == rt->p->l) rt->p->l = n;  //Replace rt with n
	else rt->p->r = n;
	n->l = rt;
	rt->p = n;
}
/*
* Rotates tree left around given root node.
* Used as helper function for .ins and .del.
* @param rt: ptr to Node around which to rotate
*/
void RBTree::rRotate(Node* rt)
{
	Node* n = rt->l;
	rt->l = n->r;
	if (n->r != nl && n->r != nullptr) n->r->p = rt;
	n->p = rt->p;

	if (rt->p == nullptr) root = n;  //Set root ptr to n if rt is root of RBTree
	else if (rt == rt->p->r) rt->p->r = n;  //Replace rt with n
	else rt->p->l = n;
	n->r = rt;
	rt->p = n;
}

void RBTree::insFix(Node* n)
{
	//Handle cases where n or n->p is root
	if (n == root) {
		n->black = true;
		return;
	}
//Had to add extra condition to handle case where moving up 2 generations lands on root
	while (n->p != nullptr && n->p->black == false) { //While parent is red - problem :(  
		//Find uncle Node
		Node* unc;
		if (n->p == n->p->p->l) {
			unc = n->p->p->r;

			//Case 1: uncle is red
			if (unc->black == false) {
				n->p->black = true;
				unc->black = true;
				n->p->p->black = false;
				n = n->p->p;  //Move active node up 2 generations for repeat
			}
			else {
				if (n == n->p->r) { //Case 2: uncle is black, n is right child
					n = n->p;
					lRotate(n);
				}
				//Case 3: uncle is black, n is right child
				n->p->black = true;
				n->p->p->black = false;
				rRotate(n->p->p);
			}
		}
		else { //Again!
			unc = n->p->p->l;

			//Case 1: uncle is red
			if (unc->black == false) {
				n->p->black = true;
				unc->black = true;
				n->p->p->black = false;
				n = n->p->p;  //Move active node up 2 generations for repeat
			}
			else {
				if (n == n->p->l) { //Case 2: uncle is black, n is left child
					n = n->p;
					rRotate(n);
				}
				//Case 3: uncle is black, n is right child
				n->p->black = true;
				n->p->p->black = false;
				lRotate(n->p->p);
			}
		}	

		//Ensure root is still black
		root->black = true;
	}

}

void RBTree::delFix(Node* n)
{
	
	while (n != root && n->black) {
		//Find sibling Node
		Node* sib;
		if (n == n->p->l) {
			sib = n->p->r;
			if (!sib->black) { //Case 1: sibling is red
				sib->black = true;
				n->p->black = false;
				lRotate(n->p);
				sib = n->p->r;
			}
			if (sib->l->black && sib->r->black) { //Case 2: nephews are black
				sib->black = false;
				n = n->p; //move up 1 generation
			}
			else {
				if (sib->r->black) { //Case 3: only right child is black
					sib->l->black = true;
					sib->black = false;
					rRotate(sib);
					sib = n->p->r;
				}

				sib->black = n->p->black;
				n->p->black = true;
				sib->r->black = true;
				lRotate(n->p);
				n = root; //Continue running on root node
			}
		} else { //Again!
			sib = n->p->l;
			if (!sib->black) { //Case 1: sibling is red
				sib->black = true;
				n->p->black = false;
				rRotate(n->p);
				sib = n->p->l;
			}
			if (sib->r->black && sib->l->black) { //Case 2: nephews are black
				sib->black = false;
				n = n->p; //move up 1 generation
			}
			else {
				if (sib->l->black) { //Case 3: only right child is black
					sib->r->black = true;
					sib->black = false;
					lRotate(sib);
					sib = n->p->l;
				}

				sib->black = n->p->black;
				n->p->black = true;
				sib->l->black = true;
				rRotate(n->p);
				n = root; //Continue running on root node
			}
		}
	}

	//Set root to black
	n->black = true;
}

/*
* Replaces a node with a subtree from another part of the tree.
* Used in .del function.
* @param n: ptr to Node being replaced
* @param subRt: ptr to root Node of subtree
*/
void RBTree::graft(Node* n, Node* subRt)
{
	if (n->p == nullptr) root = subRt;
	else if (n == n->p->l) n->p->l = subRt;
	else n->p->r = subRt;
	subRt->p = n->p;
}

/*
* Finds a specified value in the tree
* @param val: integer value to find
* @return: ptr to Node containing correct val
*/
Node* RBTree::find(int val)
{
	return find(val, root);
}
/*
* Finds a specified value in specific subtree
* @param val: integer value to find
* @param start: ptr to root Node of subtree to search
* @return: ptr to Node containing correct val
*/
Node* RBTree::find(int val, Node* start)
{
	Node* ret = start;
	while (ret != nl) {
		if (ret->value < val) ret = ret->r;
		else if (ret->value > val) ret = ret->l;
		else break;
	}
	return ret;
}

//Finds max node in tree
Node* RBTree::max()
{
	return max(root);
}
/*
* Finds max node in specific subtree
* @param start: ptr to root Node of subtree to search
*/
Node* RBTree::max(Node* start)
{
	Node* ret = start;
	while (ret->r != nullptr) ret = ret->r;
	return ret;
}

/*
* Prints entire tree inorder to standard output
*/
void RBTree::read()
{
	read(root);
	return void();
}
/*
* Prints tree inorder to standard output
* @param n: root Node of (sub)tree to print
*/
void RBTree::read(Node* n)
{
	if (n != nullptr) {
		read(n->l);
		cout << n->value << " " << endl;
		read(n->r);
	}
	return void();
}

//Finds min node in tree
Node* RBTree::min()
{
	return min(root);
}
/*
* Finds min node in specific subtree
* @param start: ptr to root Node of subtree to search
*/
Node* RBTree::min(Node* start)
{
	Node* ret = start;
	while (ret->l != nl) ret = ret->l;
	return ret;
}

//Sets value of root ptr
void RBTree::setRoot(Node* rt)
{
	root = rt;
}

//Returns root ptr
Node* RBTree::getRoot()
{
	return root;
}

//Returns pointer to null leaf node
Node* RBTree::getLeaf()
{
	return nl;
}

//Temp function for debugging
void RBTree::print(Node* n) {
	if (n != nl) {
		char color;
		if (n->black) color = 'B';
		else color = 'R';
		string rt = "";
		if (n == root) rt = "root: ";
		//cout << "(";
		cout << rt << n->value << color << ", ";  //preorder
		cout << "(";
		if (n->left() != nl) {
			//cout << "(";
			print(n->l);
		}
		else cout << "nl, ";
		//cout << rt << n->value << color << ", ";
		if (n->right() != nl) {
			print(n->r);
			//cout << ")";
		}
		else cout << "nl, ";
		cout << ")";
	}
}