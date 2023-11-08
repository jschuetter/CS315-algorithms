/*
* CS 315 Programming Assignment 2
* Trees
* Jacob Schuetter
* Purpose: implement a variety of trees
*/

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Node.h"
#include "BSTree.h"
#include "RBTree.h"

using namespace std;

const static string FILES[2] = { "testrandom.csv", "testBad.csv"};
const static string DEL_FILE = "deleteNodes.csv";

template <typename Tree> void TestTree(Tree& tree, string input, bool print = true);
template <typename Tree> void ReadFile(Tree& tree, string path);
int RouteTree(BSTree& tree, Node* n, bool showOutput = true);
int RouteTree(RBTree& tree, Node* n, bool showOutput = true);
template <typename Tree> int RouteTree(Tree& tree, bool showOutput = true);

int main()
{
	bool printTrees = true; //Set to false to hide sorted trees in terminal output
	
	cout << "BSTrees: \n";
	BSTree bstree;
	cout << "Random data: \n";
	TestTree(bstree, FILES[0], printTrees);
	BSTree bstree2;
	cout << "\nBad data: \n";
	TestTree(bstree2, FILES[1], printTrees);

	cout << "\nRBTrees: \n";
	RBTree rbtree;
	cout << "Random data: \n";
	TestTree(rbtree, FILES[0], printTrees);
	RBTree rbtree2;
	cout << "\nBad data: \n";
	TestTree(rbtree2, FILES[1], printTrees);
	
	return 0;
}

/*
* Runs a tree object through insertion and deletion tests for given input file and constant delete file
* @param tree: tree object to use
* @param input: file path of input file
* @param print: shows/hides inorder printing of tree (default = true)
*/
template<typename Tree>
void TestTree(Tree& tree, string input, bool print)
{
	int height = 0;
	ReadFile(tree, input);
	height = RouteTree(tree, print);
	if (print) cout << endl << "Height: " << height << endl;
	if (print) cout << "Deleting...\n";
	
	ifstream fileIn;
	fileIn.open(DEL_FILE);
	if (fileIn.fail()) cout << "Bad deletion file\n";
	string line = "";

	while (getline(fileIn, line)) {
		tree.del(stoi(line));
	}
	if (print) cout << "After deleting: \n";
	height = RouteTree(tree, print);
	if (print) cout << endl << "Height: " << height << endl;
	fileIn.close();
}

/*
* Creates a tree from a given .csv file
* @param tree: tree object to add Nodes to
* @param path: path of input .csv file
*/
template <typename Tree>	//Allow either BSTree or RBTree
void ReadFile(Tree& tree, string path) {
	ifstream fileIn;
	fileIn.open(path);
	if (fileIn.fail()) cout << "Bad file\n";

	string line = "";  //Store output from input file
	while (getline(fileIn, line)) {
		tree.ins(stoi(line));
	}

	fileIn.close();
}

/*
* Prints tree using inorder traversal and counts height of tree. 
* N.B. Does not include newline character at end
* @param tree: tree to print
* @param n: root Node of particular subtree to print (root by default)
* @return int; height of tree
*/
int RouteTree(BSTree& tree, Node* n, bool showOutput) {
	int cntL = 0;
	int cntR = 0;

	if (n != nullptr) {
		if (n->left() != nullptr) cntL = RouteTree(tree, n->left(), showOutput);
		if (showOutput) cout << n->getValue() << ", ";
		if (n->right() != nullptr) cntR = RouteTree(tree, n->right(), showOutput);
	}

	if (cntL > cntR) {
		cntL++;
		return cntL;
	}
	else {
		cntR++;
		return cntR;
	}

	return -1;  //Return -1 if error occurs
	
}

/*
* Prints tree using inorder traversal and counts height of tree.
* N.B. Does not include newline character at end
* @param tree: tree to print
* @param n: root Node of particular subtree to print (root by default)
* @return int; height of tree
*/
int RouteTree(RBTree& tree, Node* n, bool showOutput) {
	int cntL = 0;
	int cntR = 0;

	if (n != nullptr) {
		if (n->left() != tree.getLeaf()) cntL = RouteTree(tree, n->left(), showOutput);
		if (showOutput) cout << n->getValue() << ", ";
		if (n->right() != tree.getLeaf()) cntR = RouteTree(tree, n->right(), showOutput);
	}

	if (cntL > cntR) {
		cntL++;
		return cntL;
	}
	else {
		cntR++;
		return cntR;
	}

	return -1;  //Return -1 if error occurs

}

/*
* Prints tree using inorder traversal and counts height of tree. 
* N.B. Does not include newline character at end
* @param tree: tree to print
* @param n: root Node of particular subtree to print (root by default)
* @return int: height of tree
*/
template<typename Tree>
int RouteTree(Tree& tree, bool showOutput)
{
	return RouteTree(tree, tree.getRoot(), showOutput);
}