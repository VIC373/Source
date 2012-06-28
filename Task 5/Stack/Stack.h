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
	Stack(void);
	~Stack(void);
	/*
	* @brief Function add new element to Stack
	* @param [in] stackData - object, that will be add to Stack
	* return true (when add was complete)
	*/
	bool Push(const stackData&);
	/*
	* @brief Function delete element from head of Stack
	* return element value
	*/
	stackData Pop(void);
	/*
	* @brief Function show element from head of Stack
	* return element value
	*/
	stackData Top(void) const;
	/*
	* @brief Function check is Stack empty or not
	* return true when Stack is empty
	*/
	bool Empty(void) const;
	/*
	* @brief Function delete all elements from Stack
	*/
	void Clear(void);
	/*
	* @brief Function for show elements of Stack through console
	* @param [in] ostream - object through will be output
	* @param [in] Stack& - reference to Stack
	*/
	friend 	ostream& operator << (ostream&, const Stack&);
	/*
	* @brief Function show size of Stack
	* return int - size of Stack
	*/
	int Size(void) const;
};

#endif /*STACK_H*/