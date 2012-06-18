/*
* With the keyboard to enter a sequence of data structures in the form <Numeric Code> <Message>.
* Sort entered records in descending order codes and print the sorted array.
* Determine the count of messages in code which is near two similar numbers.
*/

#include "stdafx.h"
#include <iostream>

using namespace std;
const int TEXT_SIZE = 20;

struct Data
{
	int key;
	char value[TEXT_SIZE];
};

/*
* @brief Function show elements from array of Data
* @param [in] Data - array with Data
* @param [in] int - size of array, only > 0
*/
void Show(Data *&, int);

/*
* @brief Function sort elements from array of Data (by Key)
* @param [in,out] Data - array with Data
* @param [in] int - size of array, only > 0
*/
void BubbleSorting(Data *&, int);

/*
* @brief Function get as count of records that may have near a repetitive numbers in key
* @param [in] Data - array with Data
* @param [in] int - size of array, only > 0
* @return int
*/
int RepetitionInArray(Data *&,int);

void main(void)
{
	cout << "Plase enter size of array " << endl;
	int size;
	cin >> size;
	while (size <= 0)
	{
		cout << "Size should be > 0" << endl;
		cin >> size;
	}
	Data* mas;
	try
	{
		mas = new Data[size];
	}
	catch(bad_alloc& ba)
	{
		cout << ba.what();
		system("@pause");
		exit(1);
	}
	
	cout << "Please enter <Key> <Text value> " << size << " times" << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> mas[i].key >> mas[i].value;
	}

	Show(mas,size);
	BubbleSorting(mas,size);
	Show(mas,size);

	cout << "Records vs repetition in code : " << RepetitionInArray(mas,size) << endl;

	delete[] mas;
	system("@pause");
}

void Show(Data *& mas, int size)
{
	cout << "========================" << endl
		 << "<KEY>  <VALUE>" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << mas[i].key << "\t" << mas[i].value << endl;
	}
	cout << "========================" << endl;
}

void BubbleSorting(Data *& mas, int size)
{
	cout << "Sorting by key" << endl;
	Data temp;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size-1; j++)
		{
			if (mas[j].key < mas[j+1].key)
			{
				temp = mas[j];
				mas[j] = mas[j+1];
				mas[j+1] = temp;
			}	
		}
	}
}

int RepetitionInArray(Data *& mas, int size)
{
	int keyVsRep = 0;	/*count of key that have repetition*/
	for (int i = 0; i < size; i++)	
	{
		char* temp = new char[TEXT_SIZE];
		temp[TEXT_SIZE - 1] = '\0';

		itoa(mas[i].key,temp,10);			/*get a key like a sequence of ASCII code*/
	
		for (int i = 0; i < strlen(temp) - 1; i++)
		{
			if ((int)temp[i] == (int)temp[i+1])
			{
				keyVsRep++;
				break; /*If there is repetition - all numbers are not run*/
			}
		}
		delete[] temp; /*keys can have different lengths so - remove buffer*/
	}
	return keyVsRep;
}