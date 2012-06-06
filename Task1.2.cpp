/*
* Using only bit operation, write a function that changes the places of bits in 2 set positions 
* in unsigned long integer number.
*/
#include "stdafx.h"
#include <iostream>
using namespace std;
typedef unsigned long int ULI;

void ChangeBits(ULI& num, const int& pos1, const int& pos2)
{
	bool bit1 = (num >> pos1 & 0x1); //bit1 from pos1
	bool bit2 = (num >> pos2 & 0x1); //bit2 from pos2
	num = (num & ~(1 << pos1)) | (bit2 << pos1); //set bit2 to pos1
	num = (num & ~(1 << pos2)) | (bit1 << pos2); //set bit1 to pos2
}

extern void DecToBin(int number);

void main (void)
{
	cout << "Press number ";
	ULI number;
	cin >> number;
	DecToBin(number);
	cout << "\nPress two positions separated by space ";
	int pos1, pos2;
	cin >> pos1 >> pos2;

	ChangeBits(number,pos1,pos2);

	DecToBin(number);
	cout<< endl << number << endl;

	system ("@pause");
}