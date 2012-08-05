#include "stdafx.h"
#include <iostream>
using namespace std;
typedef unsigned int UI;

template <typename T>
class List
{
private:
	struct Node
	{
		Node* pNext;							//one connection
		T value;
	}*pNode,*pHead;
	inline bool CreateBaseNode(T val);
	inline void Clear();
public:
	explicit List(T);
	List(const List&);
	List& operator=(const List&);
	~List();
	bool PushBack(T);
	bool PushAfter(T,UI);
	bool DelByVal(T);
	bool PopBack();
	T Top() const;
	void Show() const;
};

template<typename T>
inline bool List<T>::CreateBaseNode(T val)
{
	try
	{
		pNode = new Node; 
	}
	catch(bad_alloc)
	{
		return false;
	}
	pNode->pNext = NULL;
	pNode->value = val;
	pHead = pNode;
	return true;
}

template<typename T>
inline void List<T>::Clear()
{
	while (pHead != NULL)					//pHead != NULL - we should delete ALL
	{
		Node* tmp = pHead;
		pHead = pHead->pNext;
		delete tmp;
	}
}

template<typename T>
List<T>::List(T val)					
{
	CreateBaseNode(val);
}

template<typename T>
List<T>::List(const List<T>& list)
{
	if (list.pHead != NULL)					// source is not empty?
	{
		Node* tmp = list.pHead;
		CreateBaseNode(tmp->value);
		tmp = tmp->pNext;

		while ( tmp != NULL )				//cicle througth src
		{	
			PushBack(tmp->value);
			tmp = tmp->pNext;				//next el in src
		}	
	}
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& list)
{
	if (&list == this)
	{
		return *this;
	}
	else
	{
		if (list.pHead != NULL)
		{
			Clear();						//Clear prev list
			Node* tmp = list.pHead;
			CreateBaseNode(tmp->value);		//Create Base node
			tmp = tmp->pNext;

			while (tmp != NULL)				//Create list
			{
				PushBack(tmp->value);
				tmp = tmp->pNext;
			}
		}
		return *this;
	}
}

template<typename T>
List<T>::~List()
{
	Clear();
}

template<typename T>
bool List<T>::PushBack(T val)
{
	while ( pNode->pNext != NULL )		
	{
		pNode = pNode->pNext;
	}
	
	try
	{
		pNode->pNext = new Node;
	}
	catch(bad_alloc)
	{
		return false;
	}

	pNode->pNext->pNext = NULL;
	pNode->pNext->value = val;
	return true;
}

template<typename T>
bool List<T>::PushAfter(T val, UI n)
{
	Node* el = pHead;
	for (UI i = 1; i < n; ++i)
	{
		el = el->pNext;
	}							// after "el" we should push new element

	try
	{
		Node* element = new Node;	//create new element
	}
	catch(bad_alloc)
	{
		return false;
	}
	element->value = val;

	element->pNext = el->pNext;	//change connection
	el->pNext = element;
	return true;
}

template<typename T>
bool List<T>::DelByVal(T val)
{
	Node* tmp = pHead;
	while (tmp->pNext->value != val) //we need value in next node
	{
		tmp = tmp->pNext;
		if (tmp->pNext == NULL)
		{
			return false;
		}
	}

	Node* del = tmp->pNext;			 //we should delete next element
	tmp->pNext = tmp->pNext->pNext;	//change connection
	delete del;
	return true;
}

template<typename T>
bool List<T>::PopBack()
{
	Node* tmp = pHead;
	while(tmp->pNext->pNext != NULL)
	{
		tmp = tmp->pNext;
	}
	delete tmp->pNext;
	tmp->pNext = NULL;
	pNode = tmp;
	return true;
}

template<typename T>
T List<T>::Top() const
{
	return pNode->pNext->value;
}

template<typename T>
void List<T>::Show() const
{
	Node* tmp = pHead;			//пробігаємо від першого до останнього - не перезаписуючи перший, тому використовємо tmpHead
	while (tmp != NULL)
	{
		cout << tmp->value << endl;
		tmp = tmp->pNext;
	}
}

int main(void)
{
	
	List<int>* list = new List<int>(1);
	
	list->PushBack(2);
	list->PushBack(3);
	list->PushBack(4);
	list->PushBack(5);
	list->PopBack();
	list->PopBack();
	list->PushBack(9);
	list->PushBack(10);
	list->Show();

	List<int>* list2 = new List<int>(*list);	// Copy constructor
	cout << "New List after copy constructor and PushBack" << endl;
	list2->PushBack(100);
	list2->PushBack(101);
	list2->PushBack(102);
	list2->PushBack(103);
	list2->Show();

	List<int>* list3 = new List<int>(1);		
	
	*list3 = *list; //operator =
	
	cout << "New List (base list1) after operator = " << endl;
	list3->Show();

	cout << "Top of List3 :" << list3->Top() << endl;

	delete list;
	delete list2;
	delete list3;

	system("@pause");
}
