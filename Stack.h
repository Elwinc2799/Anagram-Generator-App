#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

template <class T>
class StackNode{
	public:
	T value;
	StackNode<T> *next;
	StackNode (T nodeValue){		//Declare a value and next pointer for stackNode
		value = nodeValue;
		next = nullptr;
	}
};

template <class T>
class DynamicStack{
	private:
		StackNode<T> *stackTop;		//Pointer to the stack top
	public:
		DynamicStack(){			//Constructor for DynamicStack
			stackTop = nullptr;
		}
		~DynamicStack();		//Destructor for DynamicStack
		void push (T);
		void pop (T &);
		bool isEmpty();
		bool isFull();
		void initialiseStack();
		void copyStack(const DynamicStack<T>&);
};

template <class T>
DynamicStack<T>::~DynamicStack(){
	StackNode<T> *temp = nullptr;
	
	while (stackTop != NULL) {		//while there are elements in the stack
		temp = stackTop; 
		stackTop = stackTop->next; 
		delete temp;		//deallocate memory occupied by temp
	}
}

template <class T>
void DynamicStack<T>::push(T num){
	StackNode<T> *newNode = nullptr;	
	
	newNode = new StackNode<T>(num);	
	if (isEmpty()){					//push newNode holding num into top of the stack
		stackTop = newNode;
		newNode->next = nullptr;	
	}
	else{
		newNode->next = stackTop;		
		stackTop = newNode;		
	}
}

template <class T>
void DynamicStack<T>::pop(T &num){
	StackNode<T> *temp = nullptr;	
	
	if (isEmpty()){
		cout << "The stack is emtpy.\n";
	}
	else{						//pop value off top of stack
		num = stackTop->value;
		temp = stackTop->next;
		delete stackTop;
		stackTop = temp;
	}
}

template <class T>
bool DynamicStack<T>::isEmpty(){
	bool status;
	
	if(!stackTop){			//return true if stackTop point to NULL
		status = true;
	}
	else{
		status = false;
	}
	return status;
}

template <class T>
bool DynamicStack<T>::isFull(){
	return false;			//stack always not full
}

template <class T>
void DynamicStack<T>::initialiseStack(){
	StackNode<T> *temp = nullptr;
	
	while (stackTop != NULL){
		temp = stackTop; 
		stackTop = stackTop->next; 
		delete temp; 			//deallocate memory for each node in a stack
	}
}

template <class T>
void DynamicStack<T>::copyStack(const DynamicStack<T> &otherStack){
	StackNode<T> *newNode, *current, *last;
	
	if(stackTop != nullptr)
		initialiseStack();
	if (otherStack.stackTop == NULL)
		stackTop = NULL;
	else{
		current = otherStack.stackTop;
		stackTop = new StackNode<T>(current->value);
		stackTop->next = nullptr;
		last = stackTop;
		current = current->next;
		while (current != nullptr){
			newNode = new StackNode<T>(current->value);
			newNode->next = nullptr;
			last->next = newNode;
			last = newNode;
			current = current->next;
		}
	}
}
#endif
