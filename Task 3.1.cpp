/*
* Create a function that generates a sentence with a new inverse word order.
* Enter from the keyboard sequence of sentences.
* Based on this function - introduce how it works with the sequence of sentences.
*/

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string ReverseWord(string&);

void main(void)
{
	cout << "Please enter sentences separate by '?' or '!' or '.' " << endl;
	string text,buf;
	getline(cin,buf);
	cout << endl;

	int pos = 0;

	for (int i = 0; i < buf.length(); ++i)
	{
		if (buf[i] == '?' || buf[i] == '!' || buf[i] == '.' )
		{
			for (int j = pos; j < i; ++j)
			{
				text.push_back(buf[j]);
			}
			pos = i; /*new senteces*/
			pos += 2;
			cout << ReverseWord(text);
			cout << buf[i] << " "; /*signe*/
			text.clear();
		}
	}
	cout << endl << endl;
	system("@pause");
}


string ReverseWord(string& text)
{
	string newText = text;
	
	for (int i = text.length(), j = 0; i > 0; --i, ++j) /*Reverse all*/
	{
		newText[j] = text[i-1];
	}
	newText.push_back(' ');

	char temp;
	char* pMain = &newText[0]; //the same newText
	char* pSpace;
	char* pfirst = &newText[0]; /*to first letter*/

	for (int i = 0; i < newText.length(); ++i)/*change letters in words*/
	{
		if (pMain[i] == ' ' ) /*space?*/
		{
			pSpace = pMain + i - 1; /*last symbol in each word*/
			char* plast = pSpace;

			while (plast != pfirst)
			{
				temp = *plast;
				*plast = *pfirst;
				*pfirst = temp;

				--plast; 
				if (plast == pfirst) break; /*when we have even number of letters*/
				++pfirst; 
			}
			pfirst = pSpace + 2; /*first symbol in next word*/
		}	
	}
	return newText;
}