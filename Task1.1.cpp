/*
* Using only bit operation, write a function that returns the 1 
* if the bits in the 2 specified positions unsigned long integer number are different.
*/
#include "stdafx.h"
#include <iostream>
using namespace std;
typedef unsigned long int ULI;
/*
* Function return 1 when operation "or" between bits will be true
* We get bit by operation ">>" and mask with this bit and 0x1
*/
int DifferentBits (const ULI& num, const int& pos1, const int& pos2)
{
	return (num >> pos1 & 0x1) || (num >> pos2 & 0x1);
}

void main (void)
{
	cout << "Press number ";
	ULI number;
	cin >> number;
	cout << "Press two positions separated by space ";
	int pos1, pos2;
	cin >> pos1 >> pos2;

	cout << DifferentBits(number,pos1,pos2);//Example for 10 = 1010. Position 0 and 3 are different - result will be 1

	system("@pause");
}