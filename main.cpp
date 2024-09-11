//Isabella
//FALL 2020 - December 12

#include <iostream>
#include <cstdlib> //Used for random number generation
#include <time.h>
#include "Train.h"
/*#include "Wagon.h" already included in Train.h*/

using namespace std;

int main(int argc, char *argv[]) 
{
	/*grabbing file name from command line arguments
	string filename = argv[1]; uncomment this for command line take*/

	//FILE NOT FOUND EXCEPTION
	try
	{
		ifstream inputFile;			//new input file
		inputFile.open("train_companies.txt");   //open the file

		cout << "Reading the \"train_companies.txt\" file..." << endl;

		//check if the file is open
		if (!inputFile.is_open()) {

			//if file is not open, throw the name
			throw "train_companies.txt";
		}
		inputFile.close();  //close file
	}
	catch (string filename)
	{
		//error message and code ends
		cout << "ERROR! The file " << filename << " was not found. Exiting..." << endl;
		return 0;
	}

	cout << "Done." << endl;
	// ask for the list size from the user

	int listLength;
	cout << "Enter list length: ";
	cin >> listLength;
	cout << endl;

	// create Train list using the constructor
	Train newTrain(listLength);
	cout << "List of size " << listLength << " has been created..." << endl;

	// ask for sorting method
	cout << "Please select sorting method: " << endl;
	cout << "1. Bubble Sort" << endl;
	cout << "2. Insertion Sort" << endl;
	int sortSelection;                    //variable for read in
	cout << "Select sorting algorithm: "; //prompt
	cin >> sortSelection;                 //read in

	
	//FOR TIME IF NEEDED
	//time_t* t;
	//time(t);

	// do the sort using selected method
	//for selection choice
	switch (sortSelection)
	{
	case 1:
		newTrain.sortBubble();
		break;

	case 2:
		newTrain.sortInsertion();
		break;
	}

	//FOR TIME IF NEEDED
	//time_t* t2;
	//time(t2);
	//cout << "List has been sorted in a time of " << (t2-t)/1000ul << " seconds" << endl;

	// print the list (optional) (each Wagon and its company and load)
	newTrain.display();

	//delete newTrain; if needed
}

//Gets a random integer on the interval [min, max)
int getRandomNum(int min, int max) { return min + (rand() % (max - min)); }

//Train member function to swap two Wagons
void Train::swap(Wagon* A, Wagon* B) {
	Wagon* x = head;
	Wagon* left = NULL, * right = NULL;
	if (A == head) {
		left = A;
		right = B;
		x = nullptr;
	}
	else if (B == head) {
		left = B;
		right = A;
		x = nullptr;
	}
	else {
		for (int i = 0; i < length; i++) {
			if (x->next == A) {
				left = A;
				right = B;
				break;
			}
			else if (x->next == B) {
				left = B;
				right = A;
				break;
			}
			else {
				x = x->next;
			}
		}
	}
	// X -> L -> ... -> R -> Y
	//------------------------
	// L -> Y
	left->next = right->next;
	// R -> L
	right->next = left;
	// X -> R
	if (x != nullptr) {
		x->next = right;
	}
	else {
		head = right;
	}
}
