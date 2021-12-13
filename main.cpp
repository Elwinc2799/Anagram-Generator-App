#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <windows.h>
#include "LinkedList.h"
#include "Stack.h"
#include "Function.h"
using namespace std;

int main(){
	int choice = 0, totalWords = 0;
	LinkedList<string> dataStorage;
	
	inputFile(dataStorage, totalWords);		//Call inputFile function
	
	do {
		title();
		SetColor(11);
		menu(choice);		//Call menu function
		while (cin.fail() || choice > 8 || choice <= 0) {	//Input validation
			SetColor(12);
			cout << "Invalid input! Please enter a valid choice: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> choice;
			SetColor(11);
		}
		system("CLS");
		title();
		SetColor(7);
		switch (choice) {
		case 1: {displayA(dataStorage);		//Call to display all words
			break;
		}
		case 2: {displayAna(dataStorage);		//Call to display all anagrams
			break;
		}
		case 3: {dataStorage.sortA(totalWords);		//Call to sort all words
			break;
		}
		case 4: {searchA(dataStorage, totalWords);		//Call to search a word
			break;
		}
		case 5: {addA(dataStorage, totalWords);		//Call to add a word
			break;
		}
		case 6: {updateA(dataStorage, totalWords);		//Call to update a word
			break;
		}
		case 7: {deleteA(dataStorage, totalWords);		//Call to delete a word
			break;
		}
		case 8: {
			break;
		}
		}
	} while (choice != 8);
	system("CLS");
	dataStorage.outputFile(totalWords);		//Call outputFile function
	title();
	SetColor(11);
	cout << "Thank you ~" << endl;
	cout << "Exiting program..." << endl;
	return 0;
}

