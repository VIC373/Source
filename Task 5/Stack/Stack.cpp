#include "Stack.h"

UI Stack::size = 0;

bool Stack::Push(stackData& data)
{
	try
	{
		Node* node = new Node;  //allocate memory for new element
		node->data = data;		//copy data to new element
		node->next = head;		//next in new element - will be head
		head = node;			//now head is new element
		size++;
	}
	catch(...)
	{
		return false;
	}
	return true;
}

stackData Stack::Pop()
{
	if ( ! Empty() )
	{
		Node* temp = head;				//get element from head
		head = head->next;				//now head will be next element
		stackData data = temp->data;	//get data from temp, and delete him
		delete temp;
		size--;
		return data;
	}
	else
	{
		return -1;
	}
}

stackData Stack::Top() const
{
	if ( !Empty() )
	{
		return head->data;
	}
	else
	{
		return -1;
	}
}

ostream& operator << (ostream& s, const Stack& stack)
{
	Node* ptr = stack.head;
	while ( ptr )
	{
		s << ptr->data << endl;
		ptr = ptr->next;
	}
	return s;
}

void Stack::Clear()
{
	while ( head )
	{
		Node* temp = head->next; //pointer for next element
		delete head;			 
		head = temp;			 //now head will be next element
		size--;
	}
}