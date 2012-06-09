/*
* Using only bit operation, write a function that returns a value 
* (0 - with a negative value of the parameter x, the value x - in other case); x - long integer.
*/
#include "stdafx.h"
#include <iostream>
using namespace std;
typedef long int LI;

/*
* Function return "0" when number is negative or number in other case
*/
LI MaxValue (const LI& number)
{
	LI signOfNumber = number & 0x80000000; /*the sign of number*/
	signOfNumber |= signOfNumber >> 1;
	signOfNumber |= signOfNumber >> 2;
	signOfNumber |= signOfNumber >> 4;
	signOfNumber |= signOfNumber >> 8;
	signOfNumber |= signOfNumber >> 16; /*we will have sign like: "000...00" or "111...11"*/
	return (number & ~signOfNumber);
}

void main (void)
{
	cout << "Press number ";
	LI number;
	cin >> number;
	cout << MaxValue(number);
	system ("@pause");
}