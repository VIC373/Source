/*
* Create a function that generates a character string corresponding to the binary code of a given integer.
* The vector preset sequence entered from the keyboard as much as natural numbers (a sign of completion - enter "0").
* Based on the developed functions to print the table numbers and put their binary values.
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

typedef unsigned long int ULI;
using namespace std;

/*
* @brief Function generates a character string corresponding to the binary code of a given integer.
* @param [in] unsigned long integer number
* return string
*/
string DecToBin(ULI);

/*
* @brief Example: Pow (5,2) = 2*2*2*2*2 = 32
* @param [in] int exponent 
* @param [in] int number
* return double
*/
double Pow (int, int);


void main(void)
{
	cout << "Enter integer number separated by space or enter. For complete the entry, enter zero" << endl;

	vector<int> data;
	ULI number = 1;
	
	while (number != 0)
	{
		cin >> number;
		data.push_back(number);
	}

	for (auto i = data.begin(); i != data.end(); ++i)
	{
		cout << *i << "\t\t";
		cout << DecToBin(*i);
		cout << endl;
	}
	system("@pause");
}

double Pow (int exponent, int number = 2) 
{
	if (exponent == 0) /*(any number)^0 = 1*/
	{
		return 1; 
	}
	double result = number;
	exponent--;
	while (exponent != 0)
	{
		result *= number;     
		exponent--;
	}
	return result;
}

string DecToBin(ULI number)
{
	int p = 1; /*exponent*/
	string text;
	while (Pow(p) <= number)   /*Example for number "120" (128 > 120) "p" will be 7*/
	{
		p++;
	}
	while (p != 0) 
	{
		p--;
		bool a = (number >> p & 0x1);
		if (a)
			{
				text.push_back('1');
			}else 
			{
				text.push_back('0');
			}
	}
	return text;
}