/*
* Enter the sequence data with the results of the teams this week: 
* <DAY> <PLAN> <ACTUAL>. Print your entries in a table, sorting them in ascending order PLAN.
* Identify the days of highest and lowest percentages of the plan.
*/ 

#include "stdafx.h"
#include <iostream>
using namespace std;
const int TEXT_SIZE = 30;
const int DAY_OF_WEEK = 7;

struct Info
{
	char day[TEXT_SIZE];
	int plan;
	int actual;
};
/*
* @brief Function provides selection sorting for array of Info
* @param [in,out] Info - array of Info
* @param [in] int - size of array
*/
void SelectionSorting(Info *&, int);

/*
* @brief Function show elements from array of Info
* @param [in] Info - array with Info
* @param [in] int - size of array
*/
void Show(Info *&, int);

/*
* @brief Function show Min and Max percent of plan
* @param [in] Info - array with Info
* @param [in] int - size of array
*/
void ShowMinMax(Info *&, int);

void main(void)
{
	cout<<"Please enter <DAY> <PLAN> <ACTUAL> separated by space for 1 week"<<endl;
	
	Info* data = new Info[DAY_OF_WEEK];
	
	for (int i = 0; i < DAY_OF_WEEK; i++)
	{
		cin >> data[i].day >> data[i].plan >> data[i].actual;
	}

	Show(data,DAY_OF_WEEK);
	SelectionSorting(data,DAY_OF_WEEK);
	Show(data,DAY_OF_WEEK);
	ShowMinMax(data,DAY_OF_WEEK);

	delete[] data;
	system("@pause");
};

void Show(Info *& data, int size)
{
	cout << "=========================================" << endl
		 << "DAY\t\tPLAN\tACTUAL"<<endl;
	for (int i = 0; i < size; i++)
	{
		cout << data[i].day << "\t\t" << data[i].plan << "\t" << data[i].actual << endl;
	}
	cout << "=========================================" << endl;
}

void SelectionSorting(Info *& data, int size)
{
	cout << "sorting by PLAN..." << endl;
	Info temp; /*for change values*/
	Info* pmin;  /*pointer for max element*/

	for (int j = 0; j < size; j++)
	{	
		pmin = &data[j];
		for (int i = j; i < size; i++) 
		{
			if (pmin->plan > data[i].plan)
			{
				pmin = &data[i]; 
			}
		}
				temp = data[j];/*save value of 1st element*/
				data[j] = *pmin; /*into 1st - insert min value*/
				*pmin = temp;  /*into min value - insert 1st value from temp*/
	}
}

void ShowMinMax(Info *& data, int size)
{
	const int PERCENT = 100;/* this is a percent for calculation*/
	int indexMax, indexMin;
	indexMax = indexMin = 0;
	float max = ( data[0].actual*PERCENT / data[0].plan ); /*values of max*/
	float min = ( data[0].actual*PERCENT / data[0].plan ); /*values of min*/
	
	for (int i = 0; i < size; i++)
	{
		if ( max < ( data[i].actual*PERCENT / data[i].plan ) )
		{
			max = ( data[i].actual*PERCENT / data[i].plan );
			indexMax = i;
		}
		if ( min > ( data[i].actual*PERCENT / data[i].plan ) )
		{
			min = ( data[i].actual*PERCENT / data[i].plan );
			indexMin = i;
		}
	}
	cout << "Max " << max << "% was on " << data[indexMax].day <<endl;
	cout << "\nMin " << min <<"% was on " << data[indexMin].day <<endl;
}