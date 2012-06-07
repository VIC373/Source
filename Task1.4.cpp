/*
* Using only bit and arithmetic operations, write a function 
* that returns the next even number for a given unsigned long integer.
*/
#include "stdafx.h"
#include <iostream>
using namespace std;
typedef unsigned long int ULI;

extern void DecToBin(unsigned long int number); /*Function from DecToBin.cpp*/

/*
* This function return next even number
*/
ULI NextEvenNumber (ULI& number)
{
	return (number & ~(0x1) ) + 0x2;
}

void main (void)
{
	cout << "Press number ";
	ULI number;
	cin >> number;
	DecToBin(number); /*Conversion from decimal to binary*/
	ULI number2 = NextEvenNumber(number);
	cout << "\nNext even number will be\n";
	DecToBin(number2);

	system ("@pause");
}