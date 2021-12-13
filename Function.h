#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <windows.h>
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
using namespace std;

//Function Prototypes
void SetColor(int);
void title();
void title2(string);
void menu(int&);
void menu2(int&);
bool validWord(string);
int factorial(string);
bool search(string, string [], int);
string mapWord(string [], string);

template <class S>
void inputFile(LinkedList<S>&, int&);
template <class S>
void displayA(LinkedList<S>&);
template <class S>
void displayAna(LinkedList<S>&);
template <class S>
void searchA(LinkedList<S>&, int&);
template <class S>
void searchFunction(LinkedList<S>&, int&, string&);
template <class S>
void addA(LinkedList<S>&, int&);
template <class S>
void updateA(LinkedList<S>&, int&);
template <class S>
void deleteA(LinkedList<S>&, int&);
template <class S>
int anagram(DynamicQueue<S>&, string);
template <class S>
void display1(DynamicQueue<S>&, string, int);
template <class S>
void display2(DynamicQueue<S>&, string);
template <class S>
void editS(LinkedList<S>&, int, DynamicQueue<S>&, string&);
template <class S>
void addS(LinkedList<S>&, int&, DynamicQueue<S>&, string);
template <class S>
void deleteS(LinkedList<S>&, int&, DynamicQueue<S>&, string&, bool&);

template <class T>
string copyWord(DynamicStack<T>&, int);
template <class T>
void swap2(DynamicStack<T>&, int);

void SetColor(int f) {			    //Function use to set colour of the word
    unsigned short ForeColor = f;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}

void title(){
	SetColor(9);
	cout << "---------------------------------------------------------------------" << endl;
	cout << "|                    ANAGRAM GENERATOR                              |" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	SetColor(11);
}

void title2(string word){
	SetColor(9);
	cout << "---------------------------------------------------------------------" << endl;
	cout << "|                    ANAGRAM GENERATOR                              |" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "                     WORD: " << word << endl;
	cout << "---------------------------------------------------------------------" << endl;
	SetColor(11);
}

template <class S>
void inputFile(LinkedList<S> &list, int &total) {				//Function to input textfile
	ifstream word;
	string fileName = "", fileExt = ".txt", data = "", *tempArr, tempWord = "";			//Initialisation of variables
	
	title();
	cout << "Enter the file name: ";
	getline(cin, fileName);		//Enter text file name specified by user to input all words
	fileName += fileExt;
	word.open(fileName.c_str(), ios::in);
	while (!word) { 		//while-loop to test valid text file name
		SetColor(12);
		cout << "Word file not found! Please enter again: ";
		getline(cin, fileName);
		fileName += fileExt;
		word.open(fileName.c_str(), ios::in);
		SetColor(11);
	}
	system("CLS");
	title();
	tempArr = new string [200];
	while (!word.eof()) {		//while-loop to test end-of-file to input data from text file
		getline(word, tempWord, '\n');
		if (validWord(tempWord) == true || tempWord[0] == '\n') {
			list.appendNode(tempWord);			//Store the words into temp array
			total++;
		}
	}
	word.close();
	list.sortA(total);			//Sort the words
	list.removeDuplicate(total);		//Remove duplicate words
	if (total == 0){
		SetColor(12);
		cout << "'" << fileName << "' contain no words..." << endl;
		SetColor(11);
		system("pause");
		system("CLS");
	}
	delete [] tempArr;
}

bool validWord(string s){
	for (int j = 0; s[j] != '\0'; j++) {		//Input validation for words
		if (isdigit(s[j]) != 0 || ispunct(s[j]) != 0 || isspace(s[j]) || s.length() > 10) {
			return false;
		}
	}
	return true;
}

void menu(int &choice){
	SetColor(7);
	cout << "|  1  | DISPLAY ALL WORDS                                           |" << endl;
	cout << "|  2  | DISPLAY ALL ANAGRAMS                                        |" << endl;
	cout << "|  3  | SORT THE WORDS STORED                                       |" << endl;
	cout << "|  4  | SEARCH A WORD                                               |" << endl;
	cout << "|  5  | ADD A WORD                                                  |" << endl;
	cout << "|  6  | UPDATE A WORD                                               |" << endl;
	cout << "|  7  | DELETE A WORD                                               |" << endl;
	cout << "|  8  | EXIT                                                        |" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	SetColor(11);
	cout << "Choice: ";
	cin >> choice;
}

template <class S>
void displayA(LinkedList<S>& list){			//Display all words
	string line = "---------------------------------------------------------------------";
	
	cout << "|                    DISPLAY ALL WORDS                              |" << endl;
	SetColor(11);
	cout << line << endl;
	list.displayList();			//Call displayList method
	system("pause");
	system("CLS");
}

template <class S>
void displayAna(LinkedList<S>& list){			//Display all words with anagrams
	string line = "---------------------------------------------------------------------";
	
	cout << "|                    DISPLAY ALL ANAGRAMS                           |" << endl;
	SetColor(11);
	cout << line << endl;
	list.displayListAna();		//Call displayListAna method
	system("pause");
	system("CLS");
}

template <class S>
void searchA(LinkedList<S>& list, int& total){
	string line = "---------------------------------------------------------------------";
	string word = "", choice = "";
	bool found = false;
	
	cout << "|                    SEARCH A WORD                                  |" << endl;
	SetColor(11);
	cout << line << endl;
	list.displayList();			//Preview all words for user to search
	cout << "Type the word you want to search (MAX 7 CHAR): ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, word);
	while (found == false) {
		if (validWord(word)){			//Validation for words
			if (list.search(word)) {		//Find the word
				found = true;
				system("CLS");
				searchFunction(list, total, word);		//Call searchFunction 
				break;
			}
			else {		//Word not exists in the list
				SetColor(12);
				cout << "Word input not exists, please re-enter a valid word (MAX 7 CHAR): ";
				cin.clear();
				getline(cin, word);
				SetColor(11);
			}
		}
		else{
			SetColor(12);
			cout << "Invalid word! Please enter a valid word (MAX 7 CHAR): ";		//Invalid word input
			cin.clear();
			getline(cin, word);
			SetColor(11);
		}
	}
}

int factorial(string word){			//Return the factorial of the words
	int num = 1;
	for (int i = 0; i < word.length(); i++){
		num*=(i+1);
	}
	return num;
}

bool search(string item, string check[], int total){		//Search a words if it exists in the array
	for (int i = 0; i < total ; i++){
		if (check[i] == item){
			return true;
		}
	}
	return false;
}

template <class T>
string copyWord(DynamicStack<T> &stack, int length){			//Return the copy stored char by char in stack
	string temp = "";
	char alpha = '\0';
	DynamicStack<T> tempStack;
	
	tempStack.copyStack(stack);
	for (int j = 0; j < length; j++){
		tempStack.pop(alpha);
		temp=alpha+temp;
	}
	tempStack.initialiseStack();
	return temp;
}

template <class T>
void swap2(DynamicStack<T> &stack, int num){			//Swap the top two item in the stack
	string temp = "";
	char alpha = '\0';
	
	for (int j = 0; j < num; j++){
		stack.pop(alpha);
		temp=alpha+temp;
	}
	for (int j = temp.length(); j>0; j--){
		stack.push(temp[j-1]);
	}
}

string mapWord(string temp[], string word){			//Map the word into its anagram
	string ans = "";
	int j = 0;
	
	while(j < word.length()){
		int num = word[j]-'0';
		ans+=temp[num-1];
		j++;
	}
	return ans;
}

template <class T>
int anagram(DynamicQueue<T> &queue, string word){			//Anagram function to generate anagrams
	int i = 0, counter = 1, totalPer = 0, k = 0, realTotal = 0;
	string *check, *result, item2 = "", testWord = "", testAdd = "", item = "", number = "0123456789", temp[word.length()];
	char alpha = '\0';
	bool highSwap = false;
	DynamicStack<char> stack;
	
	queue.clear();
	while(k < word.length()){
		temp[k] = word[k];			//Map the word into an array
		k++;
	}
	for (int i = 0; i <= word.length(); i++){
		stack.push(number[i]);				//push number into stack
	}
	totalPer = factorial(word);				//Get the factorial of the word
	check = new string [totalPer];			//Create a dynamic array for the number anagrams
	result = new string [totalPer];			//Create a dynamic array for the word anagrams
	check[i] = copyWord(stack,word.length());		//Store the number into array
	result[realTotal] = mapWord(temp, check[i]);		//Store the anagram into array
	i++;
	realTotal++;
	while(i<totalPer){		//Continue while loop if i less than totalPer
		if (highSwap){
			check[i] = copyWord(stack,word.length());
			item2 = mapWord(temp, check[i]);
			if(!search(item2, result, realTotal)){		//If the word anagram not exist in the array then store the word into the array
				result[realTotal] = item2;
				realTotal++;
			}
			i++;
			highSwap = false;
		}
		swap2(stack,2);				//Swap the top 2 item in stack
		item = copyWord(stack,word.length());
		if(!search(item, check, i)){			//If the number anagram not exist in the array then store the word into the array
			check[i] = copyWord(stack,word.length());
			item2 = mapWord(temp, check[i]);
			if(!search(item2, result, realTotal)){		//If the word anagram not exist in the array then store the word into the array
				result[realTotal] = item2;
				realTotal++;
			}
			i++;
		}
		else {
			swap2(stack,2);		//Swap the top 2 item in stack
			do{
				counter+=1;
				testAdd = "";
				testWord = "";
				highSwap = true;
				testWord = copyWord(stack,word.length());
				testAdd = testWord;
				testWord = testWord.erase(0, (testWord.length()-counter-1));
				testAdd = testAdd.substr(0, testAdd.length()-counter-1);
				for (int j = 0; j < testWord.length()/2; j++){
					swap(testWord[j], testWord[testWord.length()-1-j]);
				}
				testAdd+=testWord;
			}while(search(testAdd, check, i));			//Get the real number of top items needed to reverse in the stack
			swap2(stack,counter+1);			//Reverse the top (counter+1) items in stack
			counter = 1;
		}
	}
	for (int j = 0; j < realTotal; j++){
		queue.enqueue(result[j]);			//Store all anagrams into queue
	}
	delete [] result;
	delete [] check;
	return realTotal;
}

void menu2(int& choice){
	SetColor(7);
	cout << "|  1  | DISPLAY ANAGRAMS                                            |" << endl;
	cout << "|  2  | ANAGRAMS(CHOSEN 1ST CHAR)                                   |" << endl;
	cout << "|  3  | EDIT THE WORD                                               |" << endl;
	cout << "|  4  | ADD A WORD AFTER THIS WORD                                  |" << endl;
	cout << "|  5  | DELETE THIS WORD                                            |" << endl;
	cout << "|  6  | BACK TO MAIN MENU                                           |" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	SetColor(11);
	cout << "Choice: ";
	cin >> choice;
}

template <class S>
void searchFunction(LinkedList<S>& list, int& total, string& word){
	int choice = 0, totalAna = 0;
	DynamicQueue<string> queue;
	bool confirmDelete = false;
	
	totalAna = anagram(queue, word);		//Get the number of anagrams generated
	do {
		system("CLS");
		title2(word);
		menu2(choice);		//Call menu2 function
		while (cin.fail() || choice > 6 || choice <= 0) {	//Input validation
			SetColor(12);
			cout << "Invalid input! Please enter a valid choice: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> choice;
			SetColor(11);
		}
		system("CLS");
		title2(word);
		SetColor(7);
		switch (choice) {
		case 1: {display1(queue, word, totalAna);			//Call to display all anagrams
			break;
		}
		case 2: {display2(queue, word);			//Call to display all anagrams with chosen first alphabet
			break;
		}
		case 3: {editS(list, total, queue, word);			//Edit the word
				totalAna = anagram(queue, word);			//Call anagram again to generate anagrams for new word
			break;
		}
		case 4: {addS(list, total, queue, word);			//Add a word after this word
			break;
		}
		case 5: {deleteS(list, total, queue, word, confirmDelete);			//Delete this word
			if (confirmDelete == true){
				choice = 6;
			}
			break;
		}
		case 6: {
			break;
		}
		}
	} while (choice != 6 && confirmDelete == false);
	system("CLS");
}

template <class S>
void display1(DynamicQueue<S> &queue, string word, int total){
	string line = "---------------------------------------------------------------------";
	string ana = "";
	DynamicQueue<string> tempQueue(queue);			//Copy the queue to tempQueue
	int j = 1;
	
	cout << "|                    DISPLAY ANAGRAMS                               |" << endl;
	SetColor(11);
	cout << line << endl;
	while (!tempQueue.isEmpty()){
		tempQueue.dequeue(ana);				//Dequeue tempQueue to extract all anagrams
		cout << "    " << ana;
		j++;
		if ((j-1)%6 == 0){
			cout << endl;
		}
	}
	if((j-1)%6 != 0){
		cout << endl;
	}
	cout << line << endl;
	cout << "TOTAL ANAGRAM FOR WORD '" << word << "': " << j-1 << endl;
	cout << line << endl;
	system("pause");
	system("CLS");
}

template <class S>
void display2(DynamicQueue<S> &queue, string word){
	string line = "---------------------------------------------------------------------";
	string ana = "";
	int choice = 0, total = 1;
	DynamicQueue<string> tempQueue(queue);			//Copy the queue to tempQueue
	
	cout << "|                    ANAGRAMS(CHOSEN 1ST CHAR)                      |" << endl;
	SetColor(11);
	cout << line << endl;
	cout << "Choose one alphabet:\n";
	for (int j = 0; j < word.length(); j++){
		cout << "| " << j+1 << " | '" << word[j] << "'\n";
	}
	cout << "Choice (no.): ";
	cin >> choice;
	while (cin.fail() || choice > word.length() || choice <= 0) {	//Input validation
		SetColor(12);
		cout << "Invalid input! Please enter a valid choice: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choice;
		SetColor(11);
	}
	cout << line << endl;
	while (!tempQueue.isEmpty()){
		tempQueue.dequeue(ana);
		if (ana[0] == word[choice-1]){			//Extract only word that has same first alphabet as the chosen alphabet
			cout << "    " << ana;
			total++;
			if ((total-1)%6 == 0){
				cout << endl;
			}
		}
	}
	if((total-1)%6 != 0){
		cout << endl;
	}
	cout << line << endl;
	cout << "TOTAL ANAGRAM FOR WORD '" << word << "' start with '"<< word[choice-1] << "': " << total-1 << endl;
	cout << line << endl;
	system("pause");
	system("CLS");
}

template <class S>
void editS(LinkedList<S>& list, int total, DynamicQueue<S> &queue, string &word){
	string line = "---------------------------------------------------------------------";
	string newWord = "", choice = "";
	ListNode<string> *temp;
	bool found = true;
	
	cout << "|                    EDIT THE WORD                                  |" << endl;
	SetColor(11);
	cout << line << endl;
	cout << "Current word: " << word << endl;
	cout << "New Word (MAX 7 CHAR): ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, newWord);
	while (found == true) {
		if (validWord(newWord)){
			system("CLS");
			title();
			cout << "|                    EDIT THE WORD                                  |" << endl;
			cout << line << endl;
			if (!list.search(newWord)) {		//Find the word to edit
				found = false;
				SetColor(4);
				cout << "Are you sure you want to edit the word '" << word << "' to '"<< newWord << "'?" << " (YES/NO)\nChoice: ";
				cin >> choice;
				SetColor(11);
				while (choice != "YES" && choice != "yes" && choice != "Yes" && choice != "NO" && choice != "no" && choice != "No"){		//Input validation
					SetColor(12);
					cout << "Invalid input! Please enter a valid choice: ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> choice;
					SetColor(11);
				}
				if (choice == "YES" || choice == "yes" || choice == "Yes"){
					temp = list.searchPointer(word);			//Search the word and get its pointer
					list.insertNode(newWord, temp);				//Insert the newWord after this current word
					list.deleteNode(word);						//Delete the old word
					cout << "\nWord '" << word << "' edited to '" << newWord << "'...\n";
				}
				else{
					cout << "\nBack to search menu..." << endl;
				}
				break;
			}
			if (found == true) {		//Word entered repeated, ask user to input again
				SetColor(12);
				cout << "Word edited is repeated, please re-enter a valid word (MAX 7 CHAR): ";
				cin.clear();
				getline(cin, newWord);
				SetColor(11);
			}
		}
		else{
			SetColor(12);
			cout << "Invalid word! Please enter a valid word (MAX 7 CHAR): ";
			cin.clear();
			getline(cin, newWord);
			SetColor(11);
		}
	}
	word = newWord;
	system("pause");
	system("CLS");
}

template <class S>
void addS(LinkedList<S>& list, int &total, DynamicQueue<S> &queue, string word){
	string line = "---------------------------------------------------------------------";
	string newWord = "", choice = "";
	ListNode<string> *temp;
	bool found = true;
	
	cout << "|                    ADD A WORD AFTER THIS WORD                     |" << endl;
	SetColor(11);
	cout << line << endl;
	cout << "Type the word you want to add (MAX 7 CHAR): ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, newWord);
	while (found == true) {
		if (validWord(newWord)){
			system("CLS");
			title();
			cout << "|                    ADD A WORD AFTER THIS WORD                     |" << endl;
			cout << line << endl;
			if (!list.search(newWord)) {		//Check if the word added is repeated
				found = false;
				SetColor(4);
				cout << "Are you sure you want to add the word '" << newWord << "' after '"<< word << "'?" << " (YES/NO)\nChoice: ";
				cin >> choice;
				SetColor(11);
				while (choice != "YES" && choice != "yes" && choice != "Yes" && choice != "NO" && choice != "no" && choice != "No"){
					SetColor(12);
					cout << "Invalid input! Please enter a valid choice: ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> choice;
					SetColor(11);
				}
				if (choice == "YES" || choice == "yes" || choice == "Yes"){
					temp = list.searchPointer(word);		//Search the word and get its pointer	
					list.insertNode(newWord, temp);			//Insert the newWord after this current word
					total++;								//Add the total by 1
					cout << "\nWord '" << newWord << "' added after '" << word << "'...\n";
				}
				else{
					cout << "\nBack to search menu..." << endl;
				}
				break;
			}
			if (found == true) {		//Word entered found, ask user to input again
				SetColor(12);
				cout << "Word found, please re-enter a valid word (MAX 7 CHAR): ";
				cin.clear();
				getline(cin, newWord);
				SetColor(11);
			}
		}
		else{
			SetColor(12);
			cout << "Invalid word! Please enter a valid word (MAX 7 CHAR): ";
			cin.clear();
			getline(cin, newWord);
			SetColor(11);
		}
	}
	system("pause");
	system("CLS");
}

template <class S>
void deleteS(LinkedList<S>& list, int &total, DynamicQueue<S> &queue, string &word, bool &confirmDelete){
	string line = "---------------------------------------------------------------------";
	string choice = "";
	
	cout << "|                    DELETE THE WORD                                |" << endl;
	SetColor(11);
	cout << line << endl;
	SetColor(4);
	cout << "Are you sure you want to delete the word '" << word << "'?" << " (YES/NO)\nChoice: ";
	cin >> choice;
	SetColor(11);
	while (choice != "YES" && choice != "yes" && choice != "Yes" && choice != "NO" && choice != "no" && choice != "No"){
		SetColor(12);
		cout << "Invalid input! Please enter a valid choice: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choice;
		SetColor(11);
	}
	if (choice == "YES" || choice == "yes" || choice == "Yes"){
		confirmDelete = true;
		SetColor(4);
		cout << "\nDeleting the word'" << word << "'..." << endl;
		list.deleteNode(word);			//Delete the word from the linkedlist
		total--;
		SetColor(11);
	}
	else{
		cout << "\nBack to search menu..." << endl;
	}
	system("pause");
	system("CLS");
}

template <class S>
void addA(LinkedList<S>& list, int& total){
	string line = "---------------------------------------------------------------------";
	string word = "", choice = "", searchWord = "";
	bool found = true;
	int choice2 = 0;
	ListNode<string> *temp;
	
	cout << "|                    ADD A WORD                                     |" << endl;
	SetColor(11);
	cout << line << endl;
	list.displayList();
	cout << "Type the word you want to add (MAX 7 CHAR): ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, word);
	while (found == true) {
		if (validWord(word)){
			system("CLS");
			title();
			SetColor(7);
			cout << "|                    ADD A WORD                                     |" << endl;
			SetColor(11);
			cout << line << endl;
			list.displayList();
			if (!list.search(word)) {		//Ensure the word added not exists in list
				found = false;
				SetColor(7);
				cout << "Add word '" << word << "' to:\n"<< line << "\n|  1  | End of the list\n|  2  | After a word\n" << line;
				SetColor(11);
				cout << "\nChoice: ";
				cin >> choice2;
				while (cin.fail() || choice2 > 2 || choice2 <= 0) {	//Input validation
					SetColor(12);
					cout << "Invalid input! Please enter a valid choice: ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> choice2;
					SetColor(11);
				}
				system("CLS");
				title();
				SetColor(7);
				cout << "|                    ADD A WORD                                     |" << endl;
				SetColor(11);
				cout << line << endl;
				if (choice2 == 1){
					SetColor(4);
					cout << "Are you sure you want to add the word '" << word << "' to the end of the list? (YES/NO)\nChoice: ";
					cin >> choice;
					SetColor(11);
					while (choice != "YES" && choice != "yes" && choice != "Yes" && choice != "NO" && choice != "no" && choice != "No"){
						SetColor(12);
						cout << "Invalid input! Please enter a valid choice: ";
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cin >> choice;
						SetColor(11);
					}
					if (choice == "YES" || choice == "yes" || choice == "Yes"){
						cout << "\nAdding the word to the end of the list..." << endl;
						list.appendNode(word);			//Adding the word to the end of the list
						total++;						//Add total by 1
					}
					else if (choice == "NO" || choice == "no" || choice == "No"){
						cout << "\nBack to main menu..." << endl;
					}
					break;
				}
				else{
					list.displayList();
					SetColor(11);
					cout << "Type the word you want to add '" << word << "' after it: ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					getline(cin, searchWord);
					while (!validWord(searchWord) || list.search(searchWord) == false){
						SetColor(12);
						cout << "Invalid word input, please re-enter a valid word (MAX 7 CHAR): ";
						cin.clear();
						getline(cin, searchWord);
						SetColor(11);
					}
					SetColor(4);
					cout << "\nAre you sure you want to add the word '" << word << "' after '"<< searchWord << "'?" << " (YES/NO)\nChoice: ";
					cin >> choice;
					SetColor(11);
					while (choice != "YES" && choice != "yes" && choice != "Yes" && choice != "NO" && choice != "no" && choice != "No"){
						SetColor(12);
						cout << "Invalid input! Please enter a valid choice: ";
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cin >> choice;
						SetColor(11);
					}
					if (choice == "YES" || choice == "yes" || choice == "Yes"){
						temp = list.searchPointer(searchWord);			//Search the word and get its pointer	
						list.insertNode(word, temp);					//Insert the newWord after this current word
						total++;										//Add total by 1
						cout << "\nWord '" << word << "' added after '" << searchWord << "'...\n";
					}
					else if (choice == "NO" || choice == "no" || choice == "No"){
						cout << "\nBack to main menu..." << endl;
					}
					break;
				}	
			}
			if (found == true) {		//Word exists in the list
				SetColor(12);
				cout << "Word input already exists, please re-enter a valid word (MAX 7 CHAR): ";
				cin.clear();
				getline(cin, word);
				SetColor(11);
			}
		}
		else{
			SetColor(12);
			cout << "Invalid word! Please enter a valid word (MAX 7 CHAR): ";
			cin.clear();
			getline(cin, word);
			SetColor(11);
		}
	}
	system("pause");
	system("CLS");
}

template <class S>
void updateA(LinkedList<S>& list, int& total){
	string line = "----------------------------------------------------------------";
	string word = "", choice = "", newWord = "";
	ListNode<string> *temp;
	bool found = false;
	
	cout << "|                    UPDATE A WORD                                  |" << endl;
	SetColor(11);
	cout << line << endl;
	list.displayList();
	cout << "Type the word you want to edit: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, word);
	while (found == false) {
		if (validWord(word)){
			system("CLS");
			title();
			SetColor(7);
			cout << "|                    UPDATE A WORD                                  |" << endl;
			SetColor(11);
			cout << line << endl;
			list.displayList();
			if (list.search(word)) {		//Find the word to edit
				found = true;
				SetColor(4);
				cout << "Are you sure you want to edit the word '" << word << "'? (YES/NO)\nChoice: ";
				cin >> choice;
				while (choice != "YES" && choice != "yes" && choice != "Yes" && choice != "NO" && choice != "no" && choice != "No"){
					SetColor(12);
					cout << "Invalid input! Please enter a valid choice: ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> choice;
					SetColor(11);
				}
				if (choice == "YES" || choice == "yes" || choice == "Yes"){
					SetColor(11);
					cout << "\nType the new word (MAX 7 CHAR): ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					getline(cin, newWord);
					while (!validWord(newWord) || list.search(newWord) == true){
						SetColor(12);
						cout << "Invalid word input, please enter a valid word (MAX 7 CHAR): ";
						cin.clear();
						getline(cin, newWord);
						SetColor(11);
					}
					temp = list.searchPointer(word);				//Search the word and get its pointer			
					list.insertNode(newWord, temp);					//Insert the newWord after this current word
					list.deleteNode(word);							//Delete the old word
					cout << "\nWord '" << word << "' edited to '" << newWord << "'...\n";
				}
				else{
					cout << "\nBack to main menu..." << endl;
				}
				break;
			}
			if (found == false) {		//Word entered not found, ask user to input again
				SetColor(12);
				cout << "Word not found, please re-enter a valid word (MAX 7 CHAR): ";
				cin.clear();
				getline(cin, word);
				SetColor(11);
			}
		}
		else{
			SetColor(12);
			cout << "Invalid word! Please enter a valid word: ";
			cin.clear();
			getline(cin, word);
			SetColor(11);
		}
	}
	system("pause");
	system("CLS");
}

template <class S>
void deleteA(LinkedList<S>& list, int &total){
	string line = "---------------------------------------------------------------------";
	string word = "", choice = "";
	bool found = false;
	
	cout << "|                    DELETE A WORD                                  |" << endl;
	SetColor(11);
	cout << line << endl;
	list.displayList();
	cout << "Type the word you want to delete: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, word);
	while (found == false) {
		if (validWord(word)){
			system("CLS");
			title();
			cout << "|                    DELETE A WORD                                  |" << endl;
			SetColor(11);
			cout << line << endl;
			list.displayList();
			if (list.search(word)) {		//Find the word to delete
				found = true;
				SetColor(4);
				cout << "Are you sure you want to delete the word '" << word << "'? (YES/NO)\nChoice: ";
				cin >> choice;
				SetColor(11);
				while (choice != "YES" && choice != "yes" && choice != "Yes" && choice != "NO" && choice != "no" && choice != "No"){
					SetColor(12);
					cout << "Invalid input! Please enter a valid choice: ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> choice;
					SetColor(11);
				}
				if (choice == "YES" || choice == "yes" || choice == "Yes"){
					SetColor(4);
					cout << "\nDeleting the word'" << word << "'..." << endl << endl;
					list.deleteNode(word);					//Delete the word from the list
					total--;
					SetColor(11);
				}
				else{
					cout << "\nBack to main menu..." << endl << endl;
				}
				break;
			}
			if (found == false) {		//Word entered not found, ask user to input again
				SetColor(12);
				cout << "Word not found, please re-enter a valid word: ";
				cin.clear();
				getline(cin, word);
				SetColor(11);
			}
		}
		else{
			SetColor(12);
			cout << "Invalid word! Please enter a valid word: ";
			cin.clear();
			getline(cin, word);
			SetColor(11);
		}
	}
	system("pause");
	system("CLS");
}
#endif
