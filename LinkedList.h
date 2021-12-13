#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "Queue.h"
using namespace std;

void SetColor(int);
void title();
void sortArr(string [], int);

template <class S>
int anagram(DynamicQueue<S>&, string);

template <class S>
class ListNode{
	public:
	S value;
	ListNode<S> *next;
	ListNode (S nodeValue){			//Declare a value and next pointer for a listNode
		value = nodeValue;
		next = nullptr;
	}
};

template <class S>
class LinkedList{
	private:
		ListNode<S> *head; 
  
	public:
		LinkedList(){			//Constructor for LinkedList
			head = nullptr; 
		}
		~LinkedList();			//Destructor for LinkedList
		void appendNode(S);
		void insertNode(S, ListNode<S>*);		//Insert node with a pointer parameter as location pointer
		void deleteNode(S); 
		void displayList() const;
		void displayListAna() const;		//Display all words with its anagram
		void destroyList();
		bool search(S);			//Search a word in the Linkedlist and return bool value
		void removeDuplicate(int&);
		ListNode<S>* searchPointer(string word);			//Search a word in the linkedlist and return pointer
		void sortA(int);		//Sort the linkedlist
		void outputFile(int);		//Output a file to store words and anagrams
};

template <class S>
LinkedList<S>::~LinkedList(){
	ListNode<S> *nodePtr, *nextNode;
	
	destroyList();		//call destroyList function
}

template <class S>
void LinkedList<S>::appendNode(S newValue){
	ListNode<S> *newNode, *nodePtr;

	newNode = new ListNode<S>(newValue);		//declare a newnode with newValue
	if (!head)
		head = newNode;
	else {
    	nodePtr = head;
		while (nodePtr->next)
			nodePtr = nodePtr->next;
    	nodePtr->next = newNode;
   }
}

template <class S>
void LinkedList<S>::displayList() const{			//display all words in the linkedlist
	ListNode<S> *nodePtr;
	string line = "---------------------------------------------------------------------";
	int i = 1;
	
	nodePtr = head;
	if (nodePtr == NULL){
		SetColor(12);
		cout << "No words stored from text file..." << endl;
		SetColor(11);
	}
	else {
		while (nodePtr){
			cout << "|  " << i << "  | " << nodePtr->value << endl;
			nodePtr = nodePtr->next;
			i++;
		}
	}
	cout << line << endl;
}

template <class S>
void LinkedList<S>::displayListAna() const{			//display all words and its anagrams 
	ListNode<S> *nodePtr;
	string line = "---------------------------------------------------------------------";
	string ana = "";
	int i = 1, j = 1, totalAna = 0;
	
	nodePtr = head;
	if (nodePtr == NULL){
		SetColor(12);
		cout << "No words stored from text file..." << endl;
		SetColor(11);
	}
	else {
		while (nodePtr){
			DynamicQueue<string> queue;			//declare a queue to store all anagrams
			SetColor(15);
			cout << "|  " << i << "  | " << nodePtr->value << endl;
			cout << line << endl;
			SetColor(11);
			totalAna = anagram(queue,nodePtr->value);		//anagram function return total number of anagrams generated
			while (!queue.isEmpty()){			//while queue is not empty
				queue.dequeue(ana);			//dequeue the queue n store the value in variable ana
				cout << "    " << ana;
				j++;
				if ((j-1)%6 == 0){
					cout << endl;
				}
			}
			if ((j-1) %6 != 0){
				cout << endl;
			}
			cout << line << endl;
			SetColor(3);
			cout << "TOTAL ANAGRAM FOR WORD '";
			SetColor(7);
			cout << nodePtr->value;
			SetColor(3);
			cout << "': " << totalAna << endl;		//display total number of anagrams generated
			SetColor(11);
			cout << line << endl;
			nodePtr = nodePtr->next;
			i++;
		}
	}
}

template <class S>
void LinkedList<S>::destroyList(){		//destroy the whole linked list
	ListNode<S> *nodePtr, *nextNode;
	
	nodePtr = head;
	while (nodePtr != nullptr){
		nextNode = nodePtr->next;
		delete nodePtr;					//deallocate the memory for each node in the linkedlist
		nodePtr = nextNode;
	}
	head = NULL;
}

template <class S>
bool LinkedList<S>::search(S search) {			//search a word and return bool value
	ListNode<S> *nodePtr;
	bool found=false;

	nodePtr = head;
	while (nodePtr &&!found){
		if(nodePtr->value==search)
        	found=true;					//found = true if nodePtr->value = searched word
		else
			nodePtr = nodePtr->next;
	}
	if (found)
		return true;
    else 
		return false;
}

template <class S>
void LinkedList<S>::insertNode(S newValue, ListNode<S> *temp){		//insert a newNode with newValue and *temp as location pointer
	ListNode<S> *newNode, *nodePtr;
	ListNode<S> *previousNode = nullptr;
	
	newNode = new ListNode<S>(newValue);
	if (!head){
		head = newNode;
		newNode->next = nullptr;
	}
	else {
		nodePtr = head;
		previousNode = nullptr;
		int j = 0;
		while (nodePtr != nullptr && previousNode != temp){ 		//exit while loop if previousNode = temp
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (previousNode == nullptr){
			head = newNode;
			newNode->next = nodePtr;
		}
		else{
			previousNode->next = newNode;			//add newNode after previousNode
			newNode->next = nodePtr;
		}
	}
}

template <class S>
void LinkedList<S>::deleteNode(S searchValue){			//delete a node holding same word as searchValue
	ListNode<S> *nodePtr, *previousNode; 
	
	if (!head){
		SetColor(12);
		cout << "List is empty\n";
		SetColor(11);
	}
	if (head->value == searchValue){
		nodePtr=head;
		head=head->next;
		delete nodePtr;
	}
	else{
		nodePtr = head;
		while (nodePtr != nullptr && nodePtr->value != searchValue){  		//Continuing looping until nodePtr->value == searchValue
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;							//deallocate the node pointed by nodePtr
		}
	}
}

template <class S>
void LinkedList<S>::removeDuplicate(int& total){			//Remove duplicate if there are repeated words found in the array
	ListNode<string> *nodePtr, *temp;
	
	nodePtr = head;
	while (nodePtr->next!=NULL){
		if(nodePtr->value == (nodePtr->next->value)){
			temp = nodePtr->next;
			nodePtr->next = temp->next;
			delete temp;
			total--;
		}
		else
			nodePtr = nodePtr->next;
	}
}

template <class S>
ListNode<S>* LinkedList<S>::searchPointer(string word){			//search a word and return the pointer pointing the word
	ListNode<S> *search;
	bool found=false;

	search = head;
	while (search &&!found){
		if(search->value==word)
        	found=true;
		else
			search = search->next;
	}
	if (found)
		return search;
}

template <class S>
void LinkedList<S>::sortA(int total){		//Sort the linkedlist containing all words alphabetically
	ListNode<S> *nodePtr, *previousNode;
	string word1 = "", word2 = "";
	
	for (nodePtr = head; nodePtr->next != NULL;){
		word1 = nodePtr->value;
		word2 = nodePtr->next->value;
		int j = 0;
		while (word1[j] == word2[j]){
			j++;
		}
		if(word1[j] > word2[j]){			//If the char in word1[j] larger than word2[j] then swap their position in list
			nodePtr->value = word2;
			nodePtr->next->value = word1;
			nodePtr = head;
		}
		else{
			nodePtr = nodePtr->next;
		}
	}
	SetColor(11);
	if (total != 0){
		cout << "List sorted according to alphabetical order..." << endl;
	}
	system("pause");
	system("CLS");
}

template <class S>
void LinkedList<S>::outputFile(int total){			//Output a file containing all words and anagrams
	ofstream word;
	string choice = "", fileName = "", fileExt = ".txt", tempWord = "", ana = "";
	string line = "---------------------------------------------------------------------";
	int choice2 = 0, i = 1, k = 1, totalAna = 0;
	ListNode<string> *nodePtr;
	
	title();
	SetColor(11);
	cout << "Do you wish to make a output file? (YES/NO)\nChoice: ";
	cin >> choice;
	while (choice != "YES" && choice != "yes" && choice != "Yes" && choice != "NO" && choice != "no" && choice != "No"){		//Input validation
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
	if (choice == "YES" || choice == "yes" || choice == "Yes"){			//Input validation
		cout << "Create a text file containing:\n"<< line << "\n|  1  | All words and their anagrams\n|  2  | Only words\n";
		SetColor(11);
		cout << line << "\nChoice: ";
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
		SetColor(11);
		cout << "Enter the text file name: ";
		cin.ignore(INT_MAX, '\n');
		getline(cin, fileName);
		for (int j = 0; fileName[j] != '\0'; j++) {
			if (ispunct(fileName[j]) != 0) {		//Input validation
				SetColor(12);
				cout << "Invalid filename format input! Please enter a valid filename: ";
				cin.clear();
				getline(cin, fileName);
				j = -1;
				SetColor(11);
			}
		}
		fileName += fileExt;
		word.open(fileName.c_str(), ios::out);
		nodePtr = head;
		if (choice2 == 1){
			word << line << endl;
			word << "|                    ANAGRAM GENERATOR                              |" << endl;
			word << line << endl;
			while (nodePtr){
				DynamicQueue<string> queue;
				word << "|  " << i << "  | " << nodePtr->value << endl;			//Extract all words from linked list one by one
				word << line << endl;
				totalAna = anagram(queue,nodePtr->value);			//Calculate total number of anagrams
				while (!queue.isEmpty()){
					queue.dequeue(ana);				//Dequeue all content in the queue
					word << "    " << ana;
					k++;
					if ((k-1)%6 == 0){
						word << endl;
					}
				}
				if((k-1)%6 != 0){
					word << endl;
				}
				word << line << endl;
				word << "TOTAL ANAGRAM FOR WORD '" << nodePtr->value << "': " << totalAna << endl;
				word << line << endl;
				nodePtr = nodePtr->next;
				i++;
			}
		}
		else {
			while (nodePtr){
				word << nodePtr->value;			//Extract only words to textfile
				if (i < total){
					word << endl;
					i++;
				}
				nodePtr = nodePtr->next;
			}
		}
		word.close();
		SetColor(11);
		cout << "Word output into file '" << fileName << "'..." << endl;
		system("pause");
		system("CLS");
	}
}
#endif
