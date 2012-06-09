/*
* Using only bit operation, write a function that changes the places 
* adjacent groups with 4-bit unsigned long integer number.
*/
#include "stdafx.h"
#include <iostream>
using namespace std;
typedef unsigned long int ULI;

extern void DecToBin(unsigned long int number); /*Function from DecToBin.cpp*/

/*
* This function change nyble in unsigned long integer number
*/
void ChangeNyble (ULI& number)
{
	number = ( (number & 0x0F0F0F0F) << 4 ) | ( (number & 0xF0F0F0F0) >> 4 );
}

void main (void)
{
	cout << "Press number ";
	ULI number;
	cin >> number;
	DecToBin(number); /*Conversion from decimal to binary*/
	ChangeNyble(number);
	cout << endl << "Number after nyble changing" << endl;
	DecToBin(number);

	system ("@pause");
}