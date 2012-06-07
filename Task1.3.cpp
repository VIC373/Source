/*
* Using only bit and arithmetic operations, write a function that performs cyclic shift 
* given an unsigned long integer to "r" bits to the right.
*/
#include "stdafx.h"
#include <iostream>
using namespace std;
typedef unsigned long int ULI;
const int SIZE = sizeof(ULI)*8; /*Identifier show how many bits need for unsigned long int*/

extern void DecToBin(unsigned long int number); /*Function from DecToBin.cpp*/

/*
* This function performs cyclic right shift number for "n" positions
*/
void CiclicShift (ULI& number, int pos)
{
	number = (number >> pos) | (number << (SIZE - pos));
}

void main (void)
{
	cout << "Press number ";
	ULI number;
	cin >> number;
	DecToBin(number); /*Conversion from decimal to binary*/
	cout<< "\nPress how many positions to right "<<endl;
	int p;
	cin>>p;

	CiclicShift(number,p);
	DecToBin(number);

	system ("@pause");
}