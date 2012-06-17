/*
* From the keyboard enter a sequence of records containing data for medical examination students:
* <Last Name, Initials> <Age> <Sex> <Height> <Weight>. 
* Print your entries in a table
* Sorting them by the names of students in alphabetical order.
* Determine the average height and weight of female students and male.
*/
#include "stdafx.h"
#include <iostream>
const int TEXT_SIZE = 30;
typedef unsigned short US;

using namespace std;

struct Students
{
	char lastName[TEXT_SIZE]; 
	US year;
	bool sex;
	US height;
	US weight;
};
/*
* @brief Function show elements from array of Students
* @param [in] Students - array with Students
* @param [in] int - size of array, only > 0
*/
void Show(Students*&, int);

/*
* @brief Function provides selection sorting for array of Students
* @param [in,out] Students - array of Students
* @param [in] int - size of array, only > 0
*/
void SelectionSorting(Students *&, int);

/*
* @brief Function show midle height and weight for men and women
* @param [in,out] Students - array of Students
* @param [in] int - size of array, only > 0
*/
void MidleHeightWeight(Students *&, int);

void main (void)
{
	cout << "How many students must pass a medical examination ?" << endl;
	int count;
	Students* stud;
	cin >> count;
	while (count <= 0)
	{
		cout << "You should enter a positive number" << endl;
		cin >> count;
	}
	
	try
	{
		stud = new Students [count];
	}
	catch(bad_alloc& ba)
	{
		cout << ba.what() << endl;
		system("@pause");
		exit(1);
	}

	cout << "Array was created" << endl 
		 << "Ented information about students\n <LastName> <YearOfBirth> <Sex> <Height> <Weight> " << endl;
	for (int i = 0; i < count; i++)
	{
		cin >> stud[i].lastName >> stud[i].year 
			>> stud[i].sex >> stud[i].height >> stud[i].weight;
	}

	Show(stud,count);
	SelectionSorting(stud,count);
	Show(stud,count);
	MidleHeightWeight(stud,count);

	delete[] stud;
	system("@pause");
}

void Show(Students*& stud, int size)
{
	cout << "==========================================================" << endl
		 << "<LastName> <YearOfBirth> <Sex> <Height> <Weight> " << endl;
	for (int i = 0; i < size; i++)
	{
		cout << stud[i].lastName << "\t" << stud[i].year << "\t\t" << stud[i].sex << "\t"
			 << stud[i].height << "\t" << stud[i].weight << endl;
	}
	cout << "==========================================================" << endl;
}

void SelectionSorting(Students *& stud, int size)
{
	cout << "sorting by Last name..." << endl;
	Students temp; //for change values
	Students* pmax;  //pointer for max element*

	for (int j = 0; j < size; j++)
	{	
		pmax = &stud[j];
		for (int i = j; i < size; i++) 
		{
			if (strcmp(pmax->lastName,stud[i].lastName) > 0 ) //pmax < stud[i]
			{
				pmax = &stud[i]; 
			}
		}
				temp = stud[j];/*save value of 1st element*/
				stud[j] = *pmax; /*into 1st - insert max value*/
				*pmax = temp;  /*into max value - insert 1st value from temp*/
	}
}

void MidleHeightWeight(Students *& stud, int size)
{
	int menCount = 0;
	int womCount = 0;
	float Hmen, Wmen, Hwom, Wwom;
	Hmen = Wmen = Hwom = Wwom = 0;

	for (int i = 0; i < size; i++)
	{
		if (stud[i].sex)
		{
			menCount++;
			Hmen += stud[i].height;
			Wmen += stud[i].weight;
		}
		else
		{
			womCount++;
			Hwom += stud[i].height;
			Wwom += stud[i].weight;
		}
	}
	if (menCount > 0) /*devision by zero*/
	{
		cout << "Midle Height for men = " << Hmen / menCount << endl
			 << "Midle Weight for men = " << Wmen / menCount << endl;
	}
	if (womCount > 0) /*devision by zero*/
	{
		cout << "Midle Height for women = " << Hwom / womCount << endl
			 << "Midle Weight for women = " << Wwom / womCount << endl;
	}
}
