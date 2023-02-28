//Write the Train class here and implement in main.cpp or in a Train.cpp file
#include <iostream>
#include <fstream>
#include <string>
#include "Wagon.h"

using namespace std;

int getRandomNum(int min = 0, int max = 1); //Prototype for random num generation

class Train
{
public:

	Train(int);				//constructor

	//accesor function
	Wagon* getWagonAt(int);

	void display();			//display nodes
	void sortBubble();		
	void sortInsertion();
	int compare(const Wagon*, const Wagon*);    //greater than operator
	void swap(Wagon*, Wagon*);					//swaps

	~Train();				//destructor


private:

	Wagon* head;			//points to compartment at front
	Wagon* tail;			//points to compartment at back
	int length = 0;				//keeps track of items in linked list
	int tons_low;         //lowest possible weight to carry
	int tons_high;			//highest possible weight to carry
};


//constructor
Train::Train(int numWagon)
{
	//opening file from command line argument, already checked for error in main
	ifstream inFile;
	string f = "train_companies.txt";
	inFile.open(f);	
	string arrSize;      //array size of names
	string copyArr;      //extra if needed
	string low;          //convert to int later
	string high;         //convert to int later

	//grabbing file info
	getline(inFile, arrSize, ';');
	string* arr = new string[stoi(arrSize)];			//new array of size
	getline(inFile, low, ';');		//grabbing lower bound
	getline(inFile, high, ';');		//grabbing upper bound
	getline(inFile, copyArr);       //fixes input issues

	//string to int
	tons_low = stoi(low);
	tons_high = stoi(high);
		
	//grabbing names and inserting them into the array
	for (int x = 0; x < stoi(arrSize) && !inFile.eof(); x++) {

		getline(inFile, arr[x]);
	}
	
	inFile.close(); //close file, end of read

	//Creation of linked list
	//first wagon, node
	Wagon* new_wagon = new Wagon();  //new wagon
	head = new_wagon; //sets head to be this wagon, start
	tail = new_wagon; //sets tail at this wagon, end

	//set fields of wagon
	int easyinput = stoi(arrSize);

	//randomizing data
	new_wagon->company = arr[getRandomNum(0, easyinput)];
	new_wagon->load = getRandomNum(tons_low, tons_high);

	//linked list sort
	for (int i = 0; i < numWagon; i++) 
	{
		Wagon* insert_wagon = new Wagon();
		int getHere = getRandomNum(0, easyinput);

		insert_wagon->company = arr[getHere];
		insert_wagon->load = getRandomNum(tons_low, tons_high);
 
		tail->next = insert_wagon;   //puts next wagon after tail
		tail = insert_wagon;		 //updates tail
		
		length++;
	}
	
}

//destructor
Train::~Train()
{
	Wagon* last = NULL;
	Wagon* current = head;

	//deallocated linked list
	for (int i = 0; i < length; i++)
	{
		last = current;
		current = current->next;
		delete last;
	}

}

//display the wagons
void Train::display() 
{
	Wagon* last = NULL;
	Wagon* current = head;

	//list each wagon
	for (int j = 0; j < length ; j++)
	{
		last = current;
		current = current->next;

		cout << last->company << " " << last->load << ", ";
	}
}

//get wagon at a specified index
Wagon* Train::getWagonAt(int index)
{
	Wagon* current = head;

	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current;

}

void Train::sortBubble()
{
	//bubble sort
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			Wagon* a = getWagonAt(j);
			Wagon* b = getWagonAt(j + 1);
			if ((compare(a, b)) == 1)
			{
				swap(getWagonAt(j), getWagonAt(j + 1));
			}
		}
	}
}

void Train::sortInsertion()
{
	bool inPlace = true;  //for checking if the list is sorted
	int j;				  //loop param
	for (int i = 1; i < length; i++)
	{
		inPlace = false;
		j = i;
		while (!inPlace && j >= 0) {

			Wagon* a = getWagonAt(j);
			Wagon* b = getWagonAt(j - 1);
			if ((compare(a, b)) == -1)
			{
				swap(getWagonAt(j), getWagonAt(j - 1));
				inPlace = false;
			}
			else {
				inPlace = true;
			}

			j--;
		}
	}
}

//compare loads and send back result of comparison, true false, same
int Train::compare(const Wagon* a, const Wagon* b)
{
	if (a->load < b->load) { return -1; }
	else
	{
		if (a->load == b->load) { return 0; }
		else { return 1; }

	}
}



