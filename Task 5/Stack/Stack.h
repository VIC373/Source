/*
* @file Stack.h 
* @brief This file has declaration of functions for Stack
*/

#ifndef STACK_H
#define STACK_H

#include <iostream>
using std::ostream;
using std::endl;

typedef char stackData;		 /*type of element*/
typedef unsigned int UI;

/*
* @struct Node
* @brief struct for elements of Stack
* @param [in,out] stackData - data in element
* @param [in,out] Node - pointer to next element in Stack
*/
struct Node 
{
	stackData data;		
	Node* next;			
};

/*
* @class Stack
* @brief class realize Stack functionality for Nodes
*/

class Stack
{
private:
	Node* head;
	Stack(const Stack&){};
	Stack& operator = (const Stack&){};
	static UI size;
public:
	Stack(){ head = NULL; }
	~Stack(){ Clear(); }
	bool Push(stackData&);
	stackData Pop();
	stackData Top() const;
	bool Empty() const { return head == NULL; }
	void Clear();
	friend 	ostream& operator << (ostream&, const Stack&);
	int Size() const {return size;}
};

#endif /*STACK_H*/