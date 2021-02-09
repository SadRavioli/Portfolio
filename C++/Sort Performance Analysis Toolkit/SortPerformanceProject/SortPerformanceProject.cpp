#include <iostream>
#include <string>
#include <conio.h>
#include <array>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "Swap.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "ShellSort.h"
using namespace std; //Don't have to add 'std::' in front of objects//

int z = 0; //Variable to be used in main function//

const int a = 5; //Constant to be used throughout function
struct AlgorithmsTimes { //Struct for algorithm names, array sizes and associated times//
	string Algorithms[a] = { "Bubble Sort", "Quick Sort", "Insertion Sort", "Selection Sort", "Shell Sort" };
	int Sizes[a] = { 100, 500, 1000, 5000, 10000 };
	double Times[a] = {};
} alg;

void inputDB(string file_name, double time, int array_choice) { //Function to put the time taken for sorting in the database//
	array_choice -= 1;
	ifstream inFile; //Creats input file stream//
	file_name += ".txt"; //Creates file name//
	inFile.open(file_name); //Opens file//
	for (int i = 0; i < a; i++) { //Adds times from file to struct//
		if (inFile >> alg.Times[i]) {
		}
		else {
			alg.Times[i] = 0;
		}
	}
	inFile.close(); //Closes file//
	if (alg.Times[array_choice] == 0) { //Sets 0 value to new time//
		alg.Times[array_choice] = time;
	}
	else { //If time is not zero will get average of old and new times//
		alg.Times[array_choice] = (alg.Times[array_choice] + time) / 2;
	}
	ofstream outFile; //Creates output file stream//
	outFile.open(file_name); //Opens file//
	for (int j = 0; j < a; j++) { //Outputs times to file from struct//
		outFile << alg.Times[j] << endl;
	}
	outFile.close(); //Closes file//
}

void outputDB() { //Outputs database for user to view//
	system("cls"); //Clears console//
	ifstream inFile;
	cout << "Values of 0 correspond to a test that has not be carried out yet."; //Message for user//
	cout << "\n\n\t\t\t\t\t\t\tSize of Array";
	printf("\n\n\t\t%14i%15i%16i%15i%16i", alg.Sizes[0], alg.Sizes[1], alg.Sizes[2], alg.Sizes[3], alg.Sizes[4]); //Outputs array sizes formatted for table headings//
	cout << endl;
	for (int j = 0; j < a; j++) { //Opens file, outputs algorithm name and reads their associated times from file and outputs them into the table// 
		string file_name = alg.Algorithms[j] + ".txt"; //Using struct to create file names
		inFile.open(file_name);
		cout << "\n\t" << alg.Algorithms[j]; //Output algorithms on each row
		for (int i = 0; i < a; i++) { //Outputs times associated with each algorithm
			if (inFile >> alg.Times[i]) {
			}
			else {
				alg.Times[i] = 0;
			}
		}
		inFile.close();
		printf("\t%15e%15e%15e%15e%15e", alg.Times[0], alg.Times[1], alg.Times[2], alg.Times[3], alg.Times[4]);
		cout << endl;
	}
}

void outputChoices(string array[], int n) { //Outputs menus using arrays that include the menu title and menu choices
	cout << "\n\t\t\t\t" << array[0] << "\n" << endl; //Outputs title
	for (int i = 1; i < n; i++) { //Outputs numbered choices//
		cout << "\t\t\t" << i << " - " << array[i] << endl;
	}
	cout << "\n\t\tPlease choose an option ("; //Prompts user for input//
	for (int j = 1; j < n; j++) {
		if (j <= 1) {
			cout << " " << j;
		}
		else {
			cout << " | " << j;
		}
	}
	cout << " ): ";
}

void timer(int array_choice, int option2) { //Times sorting algorithms for sorting arrays//
	int size = alg.Sizes[array_choice - 1]; //Takes array size//
	srand((unsigned)time(0)); //Creates new seed using time in seconds since Unix epoch//
	int* tempArray = new int[size]; //Creates a dynamic array//
	for (int i = 0; i < size; i++) { //Adds random numbers to dynamic array//
		tempArray[i] = (rand() % 100) + 1;
	}
	auto start = chrono::high_resolution_clock::now(); //Starts timer//
	switch (option2 + 1) { //Picks case user has chosen and algorithm sorts the array and breaks//
	case 1:
		bubbleSort(tempArray, size); break;
	case 2:
		quickSort(tempArray, 0, (size - 1)); break;
	case 3:
		insertionSort(tempArray, size); break;
	case 4:
		selectionSort(tempArray, size); break;
	case 5:
		shellSort(tempArray, size); break;
	}
	auto finish = chrono::high_resolution_clock::now(); //Timer ends
	delete[] tempArray; //Deletes dynamic array//
	chrono::duration<double> elapsed = finish - start; //Calculates time passed during sort//
	cout << "Elapsed time: " << elapsed.count() << "s\n"; //Outputs time for user//
	inputDB(alg.Algorithms[option2], elapsed.count(), array_choice); //Inputs time into database//
}

int arraySizeChoice() { //Menu for choosing size of array//
	system("cls");
	int option = 0; //Declare variable for user input;
	string choice_array[7] = { "Array Size", "Extra Small ( 100 integers)", "Small (500 integers)", "Medium (1000 integers)", "Large (5000 integers)", "Extra Large (10000 integers)", "Main Menu" };
	//Array including features of the menu//
	outputChoices(choice_array, 7); //Output menu using array//
	cin >> option; //Take user input//
	while ((cin.fail()) || ((option != 1) && (option != 2) && (option != 3) && (option != 4) && (option != 5) && (option != 6))) { //Ensures user enters valid option//
		cout << "Please pick a valid option number: ";
		cin.clear(); //Clears cin
		cin.ignore(numeric_limits<int>::max(), '\n'); //Ignores rest of line
		cin >> option; //Takes new input//
	}
	return option; //returns user input//
}

int algChoice() {
	system("cls");
	int option = 0;
	string choice_array[7] = { "Algorithms", "Bubble Sort", "Quick Sort", "Insertion Sort", "Selection Sort", "Shell Sort", "Back" };
	outputChoices(choice_array, 7);
	cin >> option;
	while ((cin.fail()) || ((option != 1) && (option != 2) && (option != 3) && (option != 4) && (option != 5) && (option != 6))) {
		cout << "Please pick a valid option number: ";
		cin.clear();
		cin.ignore(numeric_limits<int>::max(), '\n');
		cin >> option;
	}
	return option;
}

int menu() {
	int option = 0;
	string choice_array[4] = { "Main Menu", "Choose Algorithms", "Check Database", "Exit" };
	outputChoices(choice_array, 4);
	cin >> option;

	while ((cin.fail()) || ((option != 1) && (option != 2) && (option != 3) && (option != 4))) {
		cout << "Please pick a valid option number: ";
		cin.clear();
		cin.ignore(numeric_limits<int>::max(), '\n');
		cin >> option;
	}
	return option;
}

int main() {
	if (z == 0) { //Will output message about program when first executed, will not when main menu next accessed//
		z++;
		cout << "\n\t\tWelcome to my Sort Performance Analysis Toolkit." << endl;
		cout << "\n\tIn this program you will be able to choose a sorting algorithm,\n\tand the size of a randomised array which the algorithm will sort." << endl;
		cout << "\n\tThe sorting will be timed, and this time will be uploaded into a database,\n\t\t\twhich can be accessed in the menu.\n\n" << endl;
		system("pause"); //Pauses program until user inputs key//
		system("cls");
	}
	int option1 = menu(); //Takes user input from main menu function
	switch (option1) { //Goes to algChoice menu, database, or exits//
	case 1:
	{

		int option2 = algChoice();
		option2 -= 1;
		if (option2 == 5) { //Will go back to main menu if back is chosen//
			option2 = -1;
			system("cls");
			main();
		}
		int array_choice = arraySizeChoice();
		if (array_choice == 6) { //Will go back to main menu if main menu is chosen//
			array_choice = 0;
			system("cls");
			main();
		}
		system("cls");
		timer(array_choice, option2); //Timer function called with parameters of the algorithm and array choice from the user//
		cout << endl;
		system("pause");
		system("cls");
		main(); //Goes back to main menu//
	} break; //breaks
	case 2:
	{
		outputDB(); //Outputs database
		cout << endl;
		system("pause");
		system("cls");
		main(); //Back to main menu//
		break;

	};
	case 3: 
		cout << endl; 
		exit(0); //Exits//
		break;
	}
	return 0;
}
