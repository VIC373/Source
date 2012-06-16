/*
* From the keyboard to enter data set of books in the form: 
* <author> <name>, <edition> <year>.
* Print a list of books entered in a table sort by years in descending order.
* Print information about books on programming in C / C + +.
*/

#include "stdafx.h"
#include <iostream>
using namespace std;

const int TEXT_SIZE = 30;
typedef unsigned short US;

struct Book
{
	char author[TEXT_SIZE];
	char name[TEXT_SIZE];
	char edition[TEXT_SIZE];
	US year;
};
/*
* @brief Function show elements from array of Books
* @param [in] Book - array with Books
* @param [in] int - size of array, only > 0
*/
void Show(Book *&, int);

/*
* @brief Function provides selection sorting for array of Books
* @param [in,out] Book - array of Info
* @param [in] int - size of array, only > 0
*/
void SelectionSorting(Book *&, int);

/*
* @brief Function find books by name
* @param [in] Book - array with Books
* @param [in] int - size of array, only > 0
*/
void FindBookByName(Book *&, int);

void main(void)
{
	cout << "Press entrer how many books you would like to have" << endl;

	int arraySize;
	Book* books; /* array of books */
	
	cin >> arraySize;
	while (arraySize <= 0)
	{
		cout << "You should enter positive number" <<endl;
		cin >> arraySize;
	}

	try
	{
		books = new Book[arraySize];
	}
	catch(bad_alloc & ba)
	{
		cout << ba.what() << endl;
		system("@pause");
		exit(1);
	}
	cout << "Array of books was created" <<endl <<"Enter books <AUTHOR> <NAME> <EDITION> <YEAR>" << endl;
	
	for (int i = 0; i < arraySize; i++)
	{
		cin >> books[i].author >> books[i].name >> books[i].edition >> books[i].year;
	}
	
	Show(books,arraySize);
	SelectionSorting(books,arraySize);
	Show(books,arraySize);
	FindBookByName(books,arraySize);

	delete[] books;
	system("@pause");
};


void Show(Book *& books, int size)
{
	cout << "============================================\n" 
			 << "<AUTHOR> <NAME> <EDITION> <YEAR>" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << books[i].author << "\t" << books[i].name << "\t" 
			 << books[i].edition << "\t" << books[i].year << endl;
	}
	cout << "============================================\n" << endl;
}

void SelectionSorting(Book *& books, int size)
{
	cout << "sorting by YEAR..." << endl;
	Book temp; //for change values
	Book* pmax;  //pointer for max element*

	for (int j = 0; j < size; j++)
	{	
		pmax = &books[j];
		for (int i = j; i < size; i++) 
		{
			if (pmax->year < books[i].year)
			{
				pmax = &books[i]; 
			}
		}
				temp = books[j];/*save value of 1st element*/
				books[j] = *pmax; /*into 1st - insert min value*/
				*pmax = temp;  /*into min value - insert 1st value from temp*/
	}
}

void FindBookByName(Book *& books, int size)
{
	char* name;
	try
	{
		name = new char[TEXT_SIZE];
	}
	catch(bad_alloc& ba)
	{
		cout << ba.what() << endl;
		system("@pause");
		exit(1);
	}
	cout << "Enter the name of book" << endl;
	cin >> name;
	for (int i = 0; i < size; i++)
	{
		if (!strcmp(books[i].name,name)) /*compare names*/
		{
			cout << books[i].author << "\t" << books[i].name << "\t" 
			 << books[i].edition << "\t" << books[i].year << endl;
		}
	}
	delete[] name;
}
