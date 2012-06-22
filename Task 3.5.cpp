/*
* Develop a function that inserts into an array of real numbers, sorted in order of increasing values of elements
* the additional number and save ordering. Based on the developed functions in turn enter into the specified sorted 
* array of three real numbers. Print an array.
*/
#include "stdafx.h"
#include <iostream>

using namespace std;
/*
* @brief Function show elements from array of double
* @param [in] int - array with double
* @param [in] int - size of array, only > 0
* return '0' - ok, '-1' - error
*/
int ShowArray(double *&, int);

/*
* @brief Function insert elements in array of double
* @param [in,out] double - array with double
* @param [in] const double - new element
* @param [in,out] int - size of array, only > 0 (after this operation size will be different)
* return '0' - ok, '-1' - error
*/
int Insert(double *&, const double&, int&);

/*
* @brief Function sort elements from array of double
* @param [in,out] double - array with double
* @param [in] int - size of array, only > 0
* return '0' - ok, '-1' - error
*/
int SelectionSorting(double *&, int);


void main(void)
{
	cout << "How many elements you would like to have in your array?" << endl;
	
	int count;

	while (1)
	{
		cin >> count;
		if ( count > 0 )
		{
			break;
		}
		cout << "You should enter number > 0" << endl;
	}

	double* mas;

	try
	{
		mas = new double[count];
	}
	catch(bad_alloc & ba)
	{
		cerr << "Err: ";
		cout << ba.what() << endl;
	}

	cout << "Please enter " << count << " elements separated by space or enter" << endl;

	for (int i = 0; i < count; ++i)
	{
		double n;
		cin >> n;
		mas[i] = n;
	}

	ShowArray(mas,count);
	SelectionSorting(mas,count);
	cout << "Sorting ... " << endl;
	ShowArray(mas,count);

	cout << "\nHow many elements you would like to insert?" << endl;
	int insert;
	while (1)
	{
		cin >> insert;
		if ( insert > 0 )
		{
			break;
		}
		cout << "You should enter number > 0" << endl;
	}
	
	cout << "\nPlease enter this elements separated by space or enter" << endl;
	
	for (int i = 0; i < insert; ++i)
	{
		double element;
		cin >> element;
		Insert(mas,element,count);
	}

	ShowArray(mas,count);

	delete [] mas;
	system("@pause");
}

int Insert(double *& mas, const double & src, int & size)
{
	if (size <=0 )
	{
		return -1;
	}

	mas = (double*)realloc(mas, (sizeof(double)*size) + sizeof(double)); //size++
	size++;

	int i = 0; /*position for insert*/
	while ( mas[i] < src && i < size - 1 )
	{
		i++;
	}

	if ( i < size - 1 ) /*less than last empty position*/
	{
		/*from i to end -> shift by one element, and I will have an empty position for insert*/
		memmove(mas+i+1,mas+i,sizeof(double)*(size - i - 1));
		mas[i] = src;
	}
	else
	{
		mas[size - 1] = src;/*insert like last*/
	}
	return 0;
}



int ShowArray(double *& mas, int size)
{
	if ( size <= 0 )
	{
		return -1;
	}
	for (int i = 0; i < size; ++i)
	{
		cout << mas[i] << " ";
	}
	return 0;
}

int SelectionSorting(double *& mas, int size)
{
	if (size <= 0)
	{
		return -1;
	}

	double temp;
	double* pmin;

	for (int i = 0; i < size; ++i)
	{
		pmin = &mas[i];
	
		for (int j = i ; j < size; ++j)
		{
			if ( *pmin > mas[j])
			{
				pmin = &mas[j];
			}
		}
		temp = mas[i];
		mas[i] = *pmin;
		*pmin = temp;
	}
	return 0;
}