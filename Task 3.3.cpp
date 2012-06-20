/*
* Create a function that removes from the string all numeric characters and returns the count of deleted digits.
* Enter the sequence of strings. Use this function for print all strings without numbers.
* Indicate from which string removed most characters.
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
* @brief Function delete all numbers from string
* @param [in,out] string
* return int - count of numbers that were deleted
*/
int DeleteNumber(string&);

void main(void)
{
	cout << "Enter sequence of lines separated by enter. For complete the entry, enter again " << endl;
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
		data.push_back(text);
	}

	int max = 0;
	vector<string>::iterator index;
	for (auto i = data.begin(); i != data.end(); ++i)
	{
		int a = DeleteNumber(*i);	/*delete numbers from string*/
		if ( max < a )
		{
			max = a;
			index = i;
		}
		cout << *i << endl; /*show string without numbers*/
	}
	cout << "==========================================" << endl
		 << "Max count of numbers : " << max << " was in line" << endl;
	cout << *index << endl;

	system("@pause");
}

int DeleteNumber(string& text)
{
	int count = 0;
	for (int i = 0; i < text.length(); ++i)
	{
		if ( (int)text[i] < 58 && (int)text[i] > 47 ) /*ASCII code 0,1,2,3,4,5,6,7,8,9*/
		{
			memmove(&text[i],&text[i+1],text.length() - i);
			i--;	 /*checking symbol that stay in this position*/
			count++;
			text.pop_back(); /*after deleting size--*/
		}
	}
	return count;
}

