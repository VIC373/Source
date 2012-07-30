#include "stdafx.h"
#include <iostream>
using namespace std;

typedef unsigned int UI;
const UI MAX_LEN = 100;

class Stack
{
private:
	Stack& operator=(const Stack&);
	Stack(const Stack&);   
	char* data;
	UI size;
public:
	Stack();
	~Stack();
	bool PushBack(char);
	bool PopBack();
	inline char Top() const;
	inline bool Empty() const;
};

Stack::Stack()
{
	size = 0;
	data = (char*)malloc(sizeof(char));
}

Stack::~Stack()
{
	free(data);
}

inline bool Stack::Empty() const
{
	return ( size == 0) ? true : false;
}

bool Stack::PushBack(char b)
{
	data = (char*)realloc(data,sizeof(char)*(++size));
	if (data)
	{
		data[size-1] = b;
		return true;
	}
	else
	{
		return false;
	}
}

bool Stack::PopBack()
{
	if (size > 0)
	{
		data = (char*)realloc(data,sizeof(char)*(--size));
		if (data)
		{
			return true;
		}
	}
return false;
}

inline char Stack::Top() const
{
	if (size > 0)
	{
		return data[size-1];
	}
	else
	{
		return -1;
	}
}

bool CorrectBr(Stack& stack, char* str)
{
	if (!str)
	{
		return false;
	}

	for ( UI i = 0; i < strlen(str); ++i )
	{
		if ( ( str[i] == ')' ) && ( stack.Top() == '(' ) )
		{
			stack.PopBack();
		}
		else if ( ( str[i] == ']' ) && ( stack.Top() == '[' ) )
		{
			stack.PopBack();
		}
		else if ( ( str[i] == '}' ) && ( stack.Top() == '{' ) )
		{
			stack.PopBack();
		}
		else if (	( str[i] == ')' ) || ( str[i] == '(' ) 
					|| ( str[i] == ']' ) || ( str[i] == '[' ) 
					|| ( str[i] == '}' ) || ( str[i] == '{' ) )
		{
			stack.PushBack( str[i] );
		}
	}
	if ( stack.Empty() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void main(void)
{
	Stack stack;
	char* line;

	try
	{
		line = new char[MAX_LEN];
	}
	catch(bad_alloc& ba)
	{
		cerr << ba.what();
		exit(0);
	}
	cout << "Please enter line vs brackets" << endl;
	cin >> line;

	if ( CorrectBr(stack,line) )
	{
		cout << "Correct" << endl;
	}
	else
	{
		cout << "Incorrect" << endl;
	}

	delete[] line;
	system("@pause");
}