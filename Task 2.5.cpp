/*
* Enter from the kayboard information <key> <Data>. Sort entered records in ascending key.
* In the sorted array insert 2 new records and save total ordering of the array.
* Print the resulting array.
*/
#include "stdafx.h"
#include <iostream>
using namespace std;
const int TEXT_SIZE = 30;
const int ADD_RECORDS = 2; 

struct Data
{
	int key;
	char value[TEXT_SIZE];
};

/*
* @brief Function insert elements in array of Data
* @param [in,out] Data - array with Data
* @param [in] Data - new element
* @param [in,out] int - size of array, only > 0 (after this operation size will be different)
*/
void Insert(Data *&, const Data&, int&);

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
	
	cout << "Please enter <Kay> <Text value> " << size << " times" << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> mas[i].key >> mas[i].value;
	}

	Show(mas,size);
	BubbleSorting(mas,size);
	Show(mas,size);

	cout << "Insert " << ADD_RECORDS << " records\n Please enter <Kay> <Text value>" << endl;
	for (int i = 0; i < ADD_RECORDS; i++)
	{
		Data temp;
		cin >> temp.key >> temp.value;
		Insert(mas,temp,size);
	}

	Show(mas,size);

	delete[] mas;
	system("@pause");
}

void Show(Data *& mas, int size)
{
	cout << "========================" << endl
		 << "<KAY>  <VALUE>" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << mas[i].key << "\t" << mas[i].value << endl;
	}
	cout << "========================" << endl;
}

void BubbleSorting(Data *& mas, int size)
{
	cout << "Sorting by kay" << endl;
	Data temp;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size-1; j++)
		{
			if (mas[j].key > mas[j+1].key)
			{
				temp = mas[j];
				mas[j] = mas[j+1];
				mas[j+1] = temp;
			}	
		}
	}
}

void Insert(Data *& mas, const Data& src, int& size)
{
	mas = (Data*)realloc(mas,(sizeof(Data)*size)+sizeof(Data)); /*example: mas[10] will be mas[11]*/
	size++; /*size of array ++*/

	int i = 0;
	while ( mas[i].key < src.key && i < size - 1 ) /*find position for insert*/
	{
		i++;  /*will be position*/
	}

	if ( i <  size - 1 )  /*less than last ?*/
	{
		/*from i to end -> shift by one element, and I will have an empty position for insert*/
		memmove(mas+i+1,mas+i,sizeof(Data)*(size-i-1));
		mas[i] = src; /*Insert*/
	}
	else
	{
		mas[size - 1] = src; /*Insert like last*/
	}
}
