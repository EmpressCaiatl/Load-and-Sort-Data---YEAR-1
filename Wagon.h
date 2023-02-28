//Write the Wagon class here and implement in main.cpp or in a Wagon.cpp file
#include<iostream>

using namespace std;

struct Wagon
{
	string company;		//company that owns the wagon
	int load;			//weight of cargo
	Wagon* next;		//pointer to next wagon

};