#include "stdafx.h"
#include <iostream>
using namespace std;
typedef unsigned int UI;


template<typename T>
class List
{
private:
	struct Node
	{
		Node* pNext;			//one connection
		T value;
	}*pFirst, *pLast;
public:
	List();
	List(const List&);
	~List();
	List& operator=(const List&);
	void Clear();
	bool PushBack(const T&);
	bool PushFront(const T&);
	inline const T& Top() const;
	bool DelByVal(T);
	bool PopBack();
	bool PopFront();
	T GetMaxEl() const;
	bool AddAfter(T,UI);
	void Show() const;
};

template<typename T>
List<T>::List() //default constructor
{
	pFirst = pLast = NULL;
}

template<typename T>
List<T>::List(const List<T>& list)
{
	pFirst = pLast = NULL;
	Node* tmp = list.pFirst;
	while (tmp != NULL)
	{
		PushBack(tmp->value);
		tmp = tmp->pNext;
	}
}

template<typename T>
List<T>::~List()
{
	Clear();
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& list)
{
	if (this != &list)
	{
		Clear();
		Node* tmp = list.pFirst;
		while (tmp != NULL)
		{
			PushBack(tmp->value);
			tmp = tmp->pNext;
		}
	}
	return *this;
}

template<typename T>
void List<T>::Clear()
{
	Node* tmp;
	while ( pFirst != NULL )
	{
		tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
	pFirst = pLast = NULL;
}

template<typename T>
bool List<T>::PushBack(const T& v)
{
	Node* tmp;
	try
	{
		tmp = new Node;
	}
	catch(bad_alloc)
	{
		return false;
	}
	tmp->value = v;
	tmp->pNext = NULL;

		if (pFirst == NULL)
		{
			pFirst = tmp;
			pLast = tmp;
		}
		else
		{
			pLast->pNext = tmp;	
			pLast = pLast->pNext; //last will be new element
		}
		return true;
}

template<typename T>
bool List<T>::PushFront(const T& v)
{
	Node* tmp;
	try
	{
		tmp = new Node;
	}
	catch(bad_alloc)
	{
		return false;
	}
	tmp->value = v;
	tmp->pNext = pFirst;
	pFirst = tmp;
	return true;
}

template<typename T>
inline const T& List<T>::Top() const
{
	if (pLast)
	{
		return pLast->value;
	}
	else
	{
		/*NULL*/
	}
}

template<typename T>
bool List<T>::DelByVal(T v)
{
	if (!pFirst)	// list is empty?
	{
		return false;
	}

	if (pFirst->value == v )	//we should delete first element?
	{	
		return PopFront(); //we use PopFront() because: if in a List we have 1 element (PopFront chack this)
	}

	Node* tmp = pFirst;
	while ( ( tmp->pNext->value != v ) //we should chack value from prev element
			&& ( tmp->pNext->pNext != NULL ) )
	{
		tmp = tmp->pNext;
	}
	if ( tmp->pNext->value == v ) // we have finded ? 
	{
		if ( tmp->pNext->pNext == NULL ) //we should delete last elem
		{
			delete tmp->pNext;  //we do not use PopBack() : because 3 lines work faster than function call
			tmp->pNext = NULL;
			pLast = tmp;
		}
		else
		{	//we should delete not last elem
			Node* del = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
			delete del;
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool List<T>::PopBack()
{
	if (!pFirst) // list is empty?
	{
		return false;
	}
	else
	{
		if (pFirst == pLast) // 1 element in list
		{
			delete pFirst;
			pFirst = pLast = NULL;
		}
		else
		{
			Node* tmp = pFirst;

			while (tmp->pNext->pNext != NULL)
			{
				tmp = tmp->pNext;
			}

			delete tmp->pNext;
			tmp->pNext = NULL;
			pLast = tmp;
		}
	}
	return true;
}

template<typename T>
bool List<T>::PopFront()
{
	if (!pFirst) // list is empty?
	{
		return false;
	}
	else
	{
		if (pFirst == pLast) //1 element in list
		{
			delete pFirst;
			pFirst = pLast = NULL;
		}
		else
		{
			Node* del = pFirst;
			pFirst = pFirst->pNext;
			delete del;
		}
	}
	return true;
}

template<typename T>
T List<T>::GetMaxEl() const
{
	T val;
	Node* tmp = pFirst;
	val = tmp->value;

	while (tmp != NULL)
	{
		if ( val < tmp->value )
		{
			val = tmp->value;
		}
		tmp = tmp->pNext;
	}
	return val; //return by value
}

template<typename T>
bool List<T>::AddAfter(T el, UI i)
{
	Node* tmp = pFirst;
	while ( ( --i ) && ( tmp->pNext != NULL ) )
	{
		tmp = tmp->pNext;
	}
	if (i)
	{
		return false;
	}
	else
	{	//after tmp we should insert new element
		if (tmp == pLast)
		{
			PushBack(el);
		}
		else
		{
			Node* buf = new Node;
			buf->value = el;
			buf->pNext = tmp->pNext;
			tmp->pNext = buf;
		}
		return true;
	}
}

template<typename T>
void List<T>::Show() const
{
	Node* tmp = pFirst;
	while (tmp != NULL)
	{
		cout << tmp->value << endl;
		tmp = tmp->pNext;
	}
}

void main(void)
{
	List<int> data;
	data.PushBack(1);			// 1

	data.PopBack();				
	data.PopBack();
	data.PopFront();

	data.PushBack(2);			// 2
	data.PushBack(3);			// 2 3

	data.PushFront(-1);			// -1 2 3
	data.PushFront(-5);			// -5 -1 2 3

	data.PushBack(100);			// -5 -1 2 3 100

	data.Show();

	cout << "Last TOP = " << data.Top() << endl;
	data.DelByVal(-5); //del like first
	data.DelByVal(100); //del like last
	cout << "first & last were deleted" << endl;
	
	data.Show();				//	-1 2 3 
	int max = data.GetMaxEl();
	cout << endl << "MAX element = " << max << endl;

	data.AddAfter(555,2);		// -1 2 555 3
	data.Show();

	List<int> data2;
	data2 = data;
	cout << "Show data2 after operator = " << endl;
	data2.Show();


	List<int>* data3 = new List<int>(data2);
	cout << "Show data3 after copy constructor " << endl;
	data3->Show();

	system("@pause");
}