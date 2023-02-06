#pragma once
#include <iostream>
#include <string>

#include "Exceptions.h" // second Task of homework

using namespace std;

// Frankly, I was not so much doing the task itself, 
// but trying to understand the implementation of 
// a doubly linked list


class Node {
public:
	int data;
	Node* prev, * next;
	Node(int data);
};

Node::Node(int data) {
		this->data = data;
		this->prev = this->next = NULL;
}

class LinkedList {
	Node* head;
	Node* tail;
public:
	LinkedList();
	
	Node* push_front(int data); // Add element in front
	Node* push_back(int data); // Add element in back
	void pop_front(); // Delete element from front
	void pop_back(); // Delete element from back
	Node* getAt(int index); // find element

	// Return element with index
	Node* operator[](int index) {
		return getAt(index);
	}
	// Insert index beetwen two object
	Node* insert(int index, int data);
	// Delete object beetwen two other
	void erase(int index);
	// Show all list
	void show();

	~LinkedList();
};

LinkedList::LinkedList() : head { NULL }, tail{ NULL } {};

Node* LinkedList::push_front(int data) {
	Node* ptr = new Node(data); // Temp pointer
	ptr->next = head; 

	if (head != NULL)
		head->prev = ptr;
	if (tail == NULL) // If there is only one element in list
		tail = ptr;
	head = ptr;

	return ptr;
}

Node* LinkedList::push_back(int data) {
	Node* ptr = new Node(data); // Temp pointer
	ptr->prev = tail;

	if (tail != NULL)
		tail->next = ptr;
	if (head == NULL) // If there is only one element in list
		head = ptr;
	tail = ptr;

	return ptr;
}

void LinkedList::pop_back() {
	if (tail == NULL) return; // If there aren't any object in list

	Node* ptr = tail->prev; // Temp pointer

	if (ptr != NULL)
		ptr->next = NULL;
	else
		head = NULL;


	delete tail;
	tail = ptr;
}

void LinkedList::pop_front() {
	if (head == NULL) return; // If there aren't any object in list

	Node* ptr = head->next; // Temp pointer

	if (ptr != NULL)
		ptr->prev = NULL;
	else
		tail = NULL;


	delete head;
	head = ptr;
}

Node* LinkedList::getAt(int index) {
	
	// Example 4/4 (second Task)
	try {
		if (index < 0)
			throw NegativeIndex();
	}
	catch (NegativeIndex ex) {
		cout << ex.show();
		return nullptr;
	}

	Node* ptr = head; // Temp pointr
	int n = 0;

	while (n != index) {
		if (ptr == NULL)
			return NULL;
		ptr = ptr->next;
		n++;
	}
	return ptr;
}

Node* LinkedList::insert(int index, int data) {
	Node* right = getAt(index);

	if (right == nullptr)
		return NULL;

	// Example 2/4 (second Task)
	try {
		if (right == NULL)
			throw OutsideIndex();
	}
	catch (OutsideIndex ex) {
		cout << ex.show();
		return NULL;
	}

	Node* left = right->prev;
	if (left == NULL)
		return push_front(data);

	Node* ptr = new Node(data);

	ptr->prev = left;
	ptr->next = right;
	left->next = ptr;
	right->prev = ptr;

	return ptr;
}

void LinkedList::erase(int index) {
	Node* ptr = getAt(index);

	if (right == nullptr)
		return;

	// Example 3/4 (second Task)
	try {
		if (ptr == NULL) {
			throw OutsideIndex();
		}
	}
	catch (OutsideIndex ex) {
		cout << ex.show();
		return;
	}

	if (ptr->prev == NULL) {
		pop_front();
		return;
	}

	if (ptr->next == NULL) {
		pop_back();
		return;
	}
	
	Node* left = ptr->prev;
	Node* right = ptr->next;

	left->next = right;
	right->prev = left;
	
	delete[] ptr;
}

void LinkedList::show() {
	if (head) {
		for (Node* ptr = head; ptr != NULL; ptr = ptr->next) {
			cout << ptr->data << " ";
		}
		cout << endl;
	}
}

LinkedList::~LinkedList() {
	while (head != NULL)
		pop_front();
}









// Task 2 (header "Exceptions" can be use only in one file)

// I take part of this class from Homework 20 as an example

//Example 1/4 (other examples in class LinkedList)
class FileOb {
protected:
	int number_openings;
public:
	FileOb() : number_openings{ 0 } {};
	void display(const char* path) {

		FILE* out;
		char* tempStr = new char[126];
		// Open file
		if (!fopen_s(&out, path, "r")) {
			cout << "-----------\n";
			// While file didn't end
			while (!feof(out)) {
				// Read string from file
				fgets(tempStr, 126, out);
				cout << tempStr; // Print it in console
			}
			cout << "\n-----------\n";
			fclose(out);
			number_openings += 1;
		}
		else
			throw NotOpenFile(); // Exception
	}

	// Return number of openings file
	int getNumber_openings() {
		return number_openings;
	}
};