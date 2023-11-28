/*
* This program is designed to implement a "longest common subsequence" function
* Author: Jacob Schuetter
* Created: 22 Nov 2023
* History:
*	22-Nov: Updated str.at calls - subtracted 1 from all indices to account for pad layer
*			Swapped str1 and str2 in nested for loops in find()
*			Flipped comparator in nested for in find()
*/

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

const string IN_PATH = "dna.txt"; //Txt file containing strings to compare, newline-delimited

class LCS {
public:
	//Constructors
	LCS();
	LCS(string in1, string in2);

	//Member functions
	void setStrings(string in1, string in2);
	int length();
	void print();

	//Debug
	void printMatrices();

private:
	string str1, str2; //Strings of which to find subsequence
	vector<vector<int>> len; //Matrix for storing length of current LCS
	vector<vector<int>> src; //Matrix for storing direction of LCS "path" in matrix len
	/*
	* 0 = null
	* 1 = diagonal
	* 2 = left
	* 3 = up
	* n.b. defaults to up when up/left are tied
	*/
	bool updated; //Bool to note when find() needs to be run before printing length or sequence
	void find(); //Private member function to find LCS
	void print(int i, int j); //Helper function for print() recursive calls)
};


int main() {
	ifstream inFile;
	inFile.open(IN_PATH);
	string in1, in2;
	getline(inFile, in1);
	getline(inFile, in2);
	cout << in1 << endl << in2 << endl;

	LCS common(in1, in2);
	int longest = common.length();
	cout << "Length: " << longest << endl;
	//common.printMatrices();
	common.print();

	return 0;
}


//Default constructor
LCS::LCS()
{
	updated = false;
}

/*
* Alternative constructor
* @param string in1: first string
* @param string in2: second string
*/
LCS::LCS(string in1, string in2)
{
	str1 = in1;
	str2 = in2;
	updated = false;
}

/*
* Sets string member functions to new input
* @param string in1: first string
* @param string in2: second string
*/
void LCS::setStrings(string in1, string in2)
{
	str1 = in1; 
	str2 = in2;
	updated = false;
}

//Returns length of longest subsequence (stored in last element of len[][] matrix)
int LCS::length()
{
	if (!updated) find();
	int size = len[str1.length() - 1][str2.length() - 1];
	return size;
}

//Prints longest common subsequence (defaults to using first string member)
void LCS::print()
{
	if (!updated) find();

	print(str1.length(), str2.length()); //Print LCS from last element in both strings

	cout << endl;
}


void LCS::printMatrices()
{
	//len
	for (int i = 0; i < len.size(); i++) {
		for (int j = 0; j < len[i].size(); j++) {
			cout << len[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	//src
	for (int i = 0; i < len.size(); i++) {
		for (int j = 0; j < len[i].size(); j++) {
			cout << src[i][j] << " ";
		}
		cout << endl;
	}
}

//Prints longest common subsequence (defaults to using first string member)
//Helper function (for recursive calls)
void LCS::print(int i, int j)
{
	//Print common characters, else follow path in src
	//Base case when pad row/column is reached
	if (i == 0 || j == 0) return;
	if (src[i][j] == 1) {
		print(i - 1, j - 1);
		cout << str1.at(i-1);
	}
	else if (src[i][j] == 3) print(i - 1, j);
	else print(i, j - 1);
}

//Primary method used for finding LCS
void LCS::find()
{
	//Set matrices to zeros, add 1 row & 1 column of pad
	vector<int> z(str2.length()+1, 0); //Create vector of 0s of length str1.length
	for (int i = 0; i <= str1.length(); i++) { //Push z into len and src for each character in str2
		len.push_back(z);
		src.push_back(z);
	}

	//Iterate through entire matrix, fill in values
	//N.B. loops start at 1, iterate through str length to preserve pad
	for (int i = 1; i <= str1.length(); i++) {
		for (int j = 1; j <= str2.length(); j++) {
			//If characters at i, j are the same, set value to diagonal + 1
			if (str1.at(i-1) == str2.at(j-1)) {
				len[i][j] = len[i - 1][j - 1] + 1;
				src[i][j] = 1; //Set src to diagonal
			}
			//Default to up for tiebreaker
			else if (len[i - 1][j] >= len[i][j - 1]) {
				len[i][j] = len[i - 1][j];
				src[i][j] = 3;
			}
			else {
				len[i][j] = len[i][j - 1];
				src[i][j] = 2;
			}
		}
	}
	updated = true;
}

