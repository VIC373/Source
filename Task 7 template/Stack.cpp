#include "stdafx.h"
#include <iostream>

using namespace std;
typedef unsigned int UI;
							
template<typename T>
class Stack
{
private:
	UI size;
	T* data;
public:
	Stack();
	Stack(const Stack&);
	Stack& operator=(const Stack&);
	~Stack();
	bool PushBack(T);
	bool PopBack();
	inline T Top() const;
	inline UI Size() const;
	inline bool IsEmpty() const;
	void Clear();
	void Show() const;
};

template<typename T>
Stack<T>::Stack()
{
	size = 0;
	data = (T*)malloc(sizeof(T));
}

template<typename T>
Stack<T>::Stack(const Stack<T>& stack)
{
	size = stack.size;
	if (size > 0)
	{
		data = (T*)malloc(sizeof(T)*size);
		memcpy(data,stack.data,sizeof(T)*size);
	}
	else
	{
		data = (T*)malloc(sizeof(T));
	}
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
	if ( this != &stack )
	{
		this->Clear();
		if ( stack.size )
		{
			size = stack.size;
			data = (T*)realloc(data,sizeof(T)*size);
			memcpy(data,stack.data,sizeof(T)*size);
		}
	}
	return *this;
}

template<typename T>
Stack<T>::~Stack()
{
	free(data);
}

template<typename T> 
bool Stack<T>::PushBack(T val)
{
	data = (T*)realloc(data,sizeof(T)*(++size));
	if ( data )
	{
		data[size - 1] = val;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Stack<T>::PopBack()
{
	if ( size > 0)
	{
		data = (T*)realloc(data,sizeof(T)*(--size));
		if ( data )
		{
			return true;
		}
	}
	return false;
}

template<typename T>
inline T Stack<T>::Top() const
{
	return (size > 0) ? data[size - 1] : -1;
}

template<typename T>
inline UI Stack<T>::Size() const
{
	return size;
}

template<typename T>
inline bool Stack<T>::IsEmpty() const
{
	return (size == 0) ? true : false;
}

template<typename T>
void Stack<T>::Clear()
{
	size = 0;
	data = (T*)realloc(data,sizeof(T));
}

template<typename T>
void Stack<T>::Show() const
{
	for (UI i = 0; i < size; ++i)
	{
		cout << data[i] << endl;
	}
}

void main(void)
{
	Stack<int> stack;

	stack.PushBack(1);
	stack.PushBack(2);
	stack.PushBack(3);
	stack.PushBack(4);
	stack.PushBack(5);

	cout << "Stack size : " << stack.Size() << endl;
	cout << "Top element : " << stack.Top() << endl;
	
	stack.PopBack();
	stack.PopBack();

	cout << "Stack size : " << stack.Size() << endl;

	stack.Show();

	stack.Clear();
	if ( stack.IsEmpty() )
	{
		cout << "Stack is empty" << endl;
	}
	else
	{
		cout << "Stack is not empty" << endl;
	}
	system("@pause");
}
