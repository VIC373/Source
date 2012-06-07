#include <iostream>
using std::cout;

/*
* Pow (5,2) = 2*2*2*2*2 = 32
*/
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
/*
* Function convert a number from decimal to binary
*/
void DecToBin(unsigned long int number)
{
	int p = 1; /*exponent*/

	while (Pow(p) <= number)   /*Example for number "120" (128 > 120) "p" will be 7*/
	{
		p++;
	}

	while (p != 0) 
	{
		p--;
		cout << (number >> p & 0x1); /*output by one character*/
	}
}