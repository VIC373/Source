#include "stdafx.h"
#include <iostream>
#include "Stack.h"

using namespace std;

/*
* @brief Function reverse Stack
* @param [in] Stack - stack for reverse
* return pointer to new initialized Stack
*/
Stack* Reverse(Stack&);

void main(void)
{
	Stack stack;

	char a = 'a';
	char b = 'b';
	char c = 'c';

	stack.Push(a);
	stack.Push(b);
	stack.Push(c);

	cout << stack << "=====" << endl;
	Stack* stack2 = Reverse(stack);
	cout << *stack2;

	delete stack2;
	system("@pause");
}

Stack* Reverse(Stack& src)
{
	Stack* stack = new Stack;
	while ( !src.Empty() )
	{
		stack->Push(src.Pop());
	}
	return stack;
}