/*
* CS 315 Programming Assignment 1
* Sort Pokemon!
*
* Jacob Schuetter
* Created 20 September 2023
* Revised 21 September 2023
*/

#include <stdlib.h>
#include <array>
#include <string>
#include <fstream>
#include <utility>
#include <iostream>
#include <queue>

using namespace std;

const int MAX_SIZE = 1000;
const float MIN_NUM = 1; 
const float MAX_NUM = 200;
const string PATH = "C:/Users/Jayb3/Downloads/data/";  //Set this to the path of the folder containing the dataset .csv files
const string OUT_PATH = "sortOutput.txt";   //This is the title of the output file that stores the enumeration of the unsorted and sorted datasets
const string DATA_FILE = "algorithmData.csv";  //This is the name of the output file that records the number of comparisons for each dataset

/*
* ReadFile
* @brief Reads data from .csv file and writes to array
* @param fileIn is path of .csv file to read from
* @param output is array of pairs to write to
*			pair.first is Pokemon number
*			pair.second is total power
* @param size: number of elements read
*/
void ReadFile(string fileName, pair<float, int>* output, int& size) {


	ifstream stream;
	stream.open(PATH + fileName);

	bool reading = true;
	int i = 0;
	//Eliminate titles of columns
	string str;
	getline(stream, str);
	while (true) {
		//Get first element
		string first, second;
		getline(stream, first, ',');
		getline(stream, second);
		//cout << "File read strings\n" << first << " | " << second << endl;

		if (first == "" || second == "" || stream.eof()) break;

		output[i].first = stod(first);
		output[i].second = stoi(second);
		//cout << output[i].first << " | " << output[i].second << endl;
		i++;
	}
	//cout << "Read " << i << " elements\n";

	stream.close();
	size = i; //Write number of elements
}

/*
* ReadFile
* @brief Reads data from .csv file and writes to array
* @param fileIn is path of .csv file to read from
* @param output is array of pairs to write to
*			pair.first is Pokemon number
*			pair.second is total power
* @param size: number of elements read
*/
void ReadFileQueue(string fileName, queue<pair<float, int>>& output, int& size) {
	ifstream stream;
	stream.open(PATH + fileName);

	bool reading = true;
	int i = 0;
	//Eliminate titles of columns
	string str;
	getline(stream, str);
	while (true) {
		//Get first element
		string first, second;
		getline(stream, first, ',');
		getline(stream, second);
		//cout << first << second << endl;

		if (first == "" || second == "" || stream.eof()) break;

		output.push(pair<float, int>(stod(first), stoi(second)));
		//cout << output.back().first << " | " << output.back().second << " // " << output.size() << endl;
		i++;
	}

	stream.close();
	size = i;
}

/*
* PrintArray
* @brief prints array values
* @param input is array of pair<float, int>
*/
void PrintArray(pair<float, int>* input, ofstream& outStream) {
	//outStream.open(OUT_PATH, ios_base::app);

	int i = 0;
	int j = 0;
	while (i<MAX_SIZE) { 
		if (input[i].first <= MAX_NUM && input[i].first >= MIN_NUM) {//Limit printing to properly assigned elements of array
			outStream << input[i].first << " | " << input[i].second << endl;
			j++;
		}
		i++;
	}
	
	outStream << endl;
	//write.close();
	//write << j << " elements total. \n";
}

/*
* PrintQueue
* @brief prints array values
* @param input is array of pair<float, int>
*/
void PrintQueue(queue<pair<float, int>> input, ofstream& outStream) {
	queue<pair<float, int>> q = input; //Copy queue in order not to disrupt elements

	//ofstream write;
	//write.open(OUT_PATH, ios_base::app);

	for (int i = 0; i < input.size(); i++) {
		outStream << q.front().first << " | " << q.front().second << endl;
		q.pop();
	}
	
	outStream << endl;
	outStream.close();
}

/*
* CountArray
* @brief Counts number of assigned elements in array (of type pair<float, int>)
* @param input: array to count
* @return number of elements
*/
int CountArray(pair<float, int>* input) {
	int i = 0;
	while (input[i].second != NULL) i++;
	return i;
}

/*
* Swap
* @brief Swaps two elements of an array of type pair<float, int>
* @param input: parent array
* @param first: index of first element to swap
* @param second: index of second element to swap
*/
void Swap(pair<float, int>* input, int first, int second) {
	pair<float, int> temp = input[first];
	input[first] = input[second];
	input[second] = temp;
}


/*
* InsertionSort
* @brief sorts data in descending order using insertion sort algorithm
* @param input: data in array of pair<float, int>
* @param comparCnt: integer counter for number of comparisons
*/
/*
* Notes: 
* Incorporated all operations into one loop rather than separate loops
*/
void InsertionSort(pair<float, int>* input, int& comparCnt) {
	int i = 1; //Counter for current element of array (first unsorted element)

	while (input[i].second != NULL && i < MAX_SIZE) {

		if (i >= MAX_SIZE - 1) cout << "MAX REACHED" << endl; //Debug flag

		int j = i; 
		while (input[j].second >= input[j-1].second && j > 0) {//Swap input[j] and preceding element if input[j] is less
			comparCnt++;
			Swap(input, j, j - 1);
			j--;
		}

		i++;
	}

}

/*
* QsPartition
* @brief sorts (descending) one element of the given array by placing between 
*		two partitions: one of elements greater and one of elements lesser
* @param input: array to partition
* @param size: index of last assigned element of array
* @param comparCnt: integer counter for number of comparisons
* @return index of middle (sorted) value
*/
int QsPartition(pair<float, int>* input, int start, int last, int& comparCnt) {
	int j = start; //Last element of lesser portion
	int partValue = input[last].second; //Value to sort by (pivot value)
	//cout << "Value: " << partValue << endl;
	for (int k = start; k < last; k++) {
		if (input[k].second >= partValue) { //If value at index i is less than partValue, move to 'smaller' partition and increment position of end of partition
			Swap(input, k, j);
			j++;
		}
		comparCnt++;  //Increment comparison count
	}
	Swap(input, last, j);

	return j;
}
/*
* QuickSort
* @brief Sort input data items (descending) using quicksort algorithm
* @param input: array to sort
* @param start: index of element to start sort
* @param end: index of element to end sort
* @param comparCnt: integer counter for number of comparisons
*/
void QuickSort(pair<float, int>* input, int start, int end, int& comparCnt) {
	if (start < end) {

		//cout << "Start: " << start << ", end: " << end << endl;
		int part = QsPartition(input, start, end, comparCnt);
		//cout << "Part: " << part << endl;

		QuickSort(input, start, part - 1, comparCnt);
		QuickSort(input, part + 1, end, comparCnt);
	}
}

/*
* MergeSort
* @brief Uses merge sort to sort input data items (descending order)
* @param input: array to sort
* @param start: index of first element to sort
* @param end: index of last element to sort
* @param comparCnt: integer counter for number of comparisons
* @return index of start of partition (to aid in recombining in order)
*/
queue<pair<float, int>> MergeSort(queue<pair<float, int>> input, int& comparCnt) {
	if (input.size() <= 1) return input;

	//Split queue into subqueues
	int split = input.size()/2; //Number of elements to split into second array
	int rem = input.size() - split; //Number of elements remaining after split is removed
	queue<pair<float, int>> subA, subB;
	for (int i = 0; i < split; i++) {
		subA.push(input.front());
		input.pop();
	}
	for (int i = 0; i < rem; i++) {
		subB.push(input.front());
		input.pop();
	}
	
	//Sort subqueues
	subA = MergeSort(subA, comparCnt);
	subB = MergeSort(subB, comparCnt);

	//Reassemble subqueues
	queue<pair<float, int>> output;
	int totSize = subA.size() + subB.size();
	for (int i = 0; i < totSize; i++) {
		if (subA.size() == 0 && subB.size() == 0) {
			cout << "Both subarrays empty\n";
		}
		else if (subA.size() == 0) {
			output.push(subB.front());
			subB.pop();
		}
		else if (subB.size() == 0) {
			output.push(subA.front());
			subA.pop();
		}	
		else if (subA.front().second > subB.front().second) {
			output.push(subA.front());
			subA.pop();
		}
		else {
			output.push(subB.front());
			subB.pop();
		}
		comparCnt++;
	}

	return output;
}

string RunSorts(string inFile, bool printArrays = false) {
	pair<float, int> emptyPair(0.0, 0);

	ofstream write;
	write.open(OUT_PATH, ios_base::app);

	write << "Current dataset: " << inFile << endl;

	//Insertion Sort
	int insertionComparCnt = 0, insertionSize = 0;  //Initialize variables to store number of comparisons and input size for algorithm
	pair<float, int> insertionArr[MAX_SIZE] = { emptyPair };
	ReadFile(inFile, insertionArr, insertionSize);
	if (printArrays) {
		write << "Insertion sort\nBefore sorting: \n";
		PrintArray(insertionArr, write);
		write << endl;
	}

	InsertionSort(insertionArr, insertionComparCnt);

	if (printArrays) {
		write << "After sorting: \n";
		PrintArray(insertionArr, write);
		write << endl;
	}
	cout << "Insertion sort: " << insertionSize << " elements, " << insertionComparCnt << " comparisons\n";

	//Quicksort
	int quickComparCnt = 0, quickSize = 0;
	pair<float, int> quickArr[MAX_SIZE] = { emptyPair };
	ReadFile(inFile, quickArr, quickSize);
	//cout << "Quicksort, 0, " << CountArray(quickArr) - 1 << endl;
	if (printArrays) {
		write << "Quicksort\nBefore sorting: \n";
		PrintArray(quickArr, write);
		write << endl;
	}

	QuickSort(quickArr, 0, CountArray(quickArr) - 1, quickComparCnt);

	if (printArrays) {
		write << "After sorting: \n";
		PrintArray(quickArr, write);
		write << endl;
	}
	cout << "Quicksort: " << quickSize << " elements, " << quickComparCnt << " comparisons\n";

	//Merge Sort
	int mergeComparCnt = 0, mergeSize = 0;
	queue<pair<float, int>> mergeArr;
	ReadFileQueue(inFile, mergeArr, mergeSize);
	if (printArrays) {
		write << "Merge sort\nBefore sorting: \n";
		PrintQueue(mergeArr, write);
		write << endl;
	}

	queue<pair<float, int>> q = MergeSort(mergeArr, mergeComparCnt);

	if (printArrays) {
		write << "After sorting: \n";
		PrintQueue(q, write);
		write << endl;
	}
	cout << "Merge sort: " << mergeSize << " elements, " << mergeComparCnt << " comparisons\n";

	write.close();
	return inFile + ", " + to_string(insertionSize) + ", " + to_string(insertionComparCnt) + ", " + to_string(quickComparCnt) + ", " + to_string(mergeComparCnt);
}

int main() {
	//Store paths of all data files
	string filePaths[] = {"pokemonRandomLarge.csv", "pokemonRandomMedium.csv", "pokemonRandomSmall.csv",
	"pokemonReverseSortedLarge.csv", "pokemonReverseSortedMedium.csv", "pokemonReverseSortedSmall.csv", 
	"pokemonSortedLarge.csv", "pokemonSortedMedium.csv", "pokemonSortedSmall.csv"};
	int setSizes[] = { 800, 432, 166 };

	//Clear existing data in output file
	ofstream write;
	write.open(OUT_PATH, ios_base::trunc);
	write.close();

	//Create filestream for storing input size & runtime data
	ofstream writeCsv(DATA_FILE);
	//Create csv file headers
	writeCsv << "Dataset, n, Insertion sort, Quicksort, Merge sort\n";
	
	cout << "\nRandom sorted input: \n";
	for (int i = 0; i <= 2; i++) {
		writeCsv << RunSorts(filePaths[i], true) << endl;
	}

	cout << "\nReverse sorted input: \n";
	for (int i = 3; i <= 5; i++) {
		writeCsv << RunSorts(filePaths[i], true) << endl;
	}

	cout << "\nSorted input: \n";
	for (int i = 6; i <= 8; i++) {
		writeCsv << RunSorts(filePaths[i], true) << endl;
	}

	writeCsv.close();
	return 0;
}