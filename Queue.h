#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

template <class T>
class QueueNode{
	public:
		T value;
		QueueNode<T> *next;
		QueueNode(T nodeValue){			//Declare a value and next pointer for queueNode
			value = nodeValue;
			next = NULL;
		}
};

template <class T>
class DynamicQueue{
	private:
		QueueNode<T> *front;	//The front of the queue
		QueueNode<T> *rear;		//The rear of the queue
		int numItems = 0;			//Number of items in the queue
	
	public:
		DynamicQueue (){		//Constructor for DynamicQueue
			front = NULL;
			rear = NULL;
			numItems = 0;
		}	
		DynamicQueue (const DynamicQueue<T>&);
		~DynamicQueue ();		//Destructor for DynamicQueue
		void enqueue(T);
		void dequeue(T &);
		bool isEmpty() const;
		bool isFull() const;
		void clear();
		int numOfItems();
		T frontValue();
		void copyQueue(const DynamicQueue<T>&);
};

template <class T>
DynamicQueue<T>::DynamicQueue(const DynamicQueue<T>& otherQueue){		//Alternate constructor for DynamicQueue
	front = NULL;
	copyQueue(otherQueue);	
}

template <class T>
DynamicQueue<T>::~DynamicQueue(){		//Destructor
	clear();
}

template <class T>
void DynamicQueue<T>::enqueue(T item){			//Enqueue an item to front of the queue
	QueueNode<T> *newNode = NULL;
	
	newNode = new QueueNode<T>(item);
	if (isEmpty()){
		front = newNode;
		rear = newNode;
	}
	else{
		rear->next = newNode;
		rear = newNode;
	}
	numItems++;				//Add 1 to numItems
}

template <class T>
void DynamicQueue<T>::dequeue(T &item){				//Dequeue an item from the front of the list
	QueueNode<T> *temp = NULL;
	
	if (isEmpty()){
		cout << "The queue is empty.\n";
	}
	else{
		item = front->value;
		temp = front;
		front = front->next;
		delete temp;			//Deallocate memory for an item in the queue
		numItems--;				//Decrease the numItems by 1
	}
}

template <class T>
bool DynamicQueue<T>::isEmpty() const{			//Check if the queue is empty
	bool status;
	
	if (numItems > 0)
		status = false;
	else
		status = true;
	return status;
}

template <class T>
void DynamicQueue<T>::clear(){				//Destroy the queue
	T value;
	
	while(!isEmpty())
		dequeue(value);
}

template <class T>
int DynamicQueue<T>::numOfItems(){			//Return number of items in the queue
	return numItems;
}

template <class T>
T DynamicQueue<T>::frontValue(){			//Return the item in front of the list
	return front->value;
}

template <class T>
void DynamicQueue<T>::copyQueue(const DynamicQueue<T> &otherQueue){			//Copy the queue to a another queue
	QueueNode<T> *newNode, *current;
	
	if (front != NULL)
		clear();
	if (otherQueue.front == NULL){
		front = NULL;
		rear = NULL;
	}
	else{
		current = otherQueue.front;
		front = new QueueNode<T>(current->value);
		rear = front;
		current = current->next;
		numItems++;
		while (current != NULL){
			newNode = new QueueNode<T>(current->value);			//Add a newnode to the rear of the queue
			rear->next = newNode;
			rear = newNode;
			current = current->next;
			numItems++;
		}
	}
}
#endif
