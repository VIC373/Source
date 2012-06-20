/*
* Create a function that performs the replacement in a given sentence all small letters to capital letters
* Function should returns the number of words per sentence.
* Based on the developed function to print all sentences with all capital letters.
* Identify which of the sentences has the maximum number of words.
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
* @brief Function return count of words in a sentences and change letter to capital letter
* @param [in,out] string
* return int - count of words
*
* in ASCII table different between Little and Capital letter only in one bit
* **0* **** // Capital letter
* **1* **** // Little letter
*/

int CapitalLetter(string& text);


void main(void)
{
	cout << "Enter sentences" << endl;
	string text;
	vector<string> data;


	while (1)
	{
		text.clear();
		getline(cin,text);
		if (text == "")
		{
			break;
		}
		data.push_back(text); // Sequence of sentences
	}


	int maxCountW = 0;
	vector<string>::iterator index;
	for (auto i = data.begin(); i != data.end(); ++i)
	{
		int a = CapitalLetter(*i);
		if (maxCountW < a)
		{
			maxCountW = a;
			index = i;
		}
		cout << *i << endl;
	}

	cout << "=====================================" << endl
		 << "Max count of words : " << maxCountW 
		 << " in sentencese " << endl << *index << endl;

	system("@pause");
}

int CapitalLetter(string& text)
{
	int count = 0;
	for (int i = 0; i < text.length(); ++i)
	{
		if (text[i] == ' ')
		{
			count++;
		}
		if ( (int)text[i] > 96 && (int)text[i] < 123 ) //ASCII code a ... z
		{
			text[i] = (char)((int)text[i] & 0xDF); //mask for Capital letter 1101 1111 = 0xDF
		}
	}
	return ++count;
}
