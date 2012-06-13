/*
* We enter an array with records <Code> <Price>. 
* After that enter the sequence data on the goods: 
* <Name of Product> <Code> <Count> (data of the same product may meet several times).
* According to these two arrays to print summary in tabular form with columns: 
* <Code> <Name of Product> <Count> <Total cost> sorted by Code
*/

#include "stdafx.h"
#include <iostream>
using namespace std;
const int NAME_SIZE = 30;

struct Info
{
	int code;   
	float price; 
};

struct Products
{
	char name[NAME_SIZE];
	int code;
	int count;
};

struct Sale
{
	int code;
	char name[NAME_SIZE];
	int count;
	float sumPrice;
};
/*
* @brief Function insert elements to Sale from Products and Info
* @param [in] Products - array of products
* @param [in] Info - array of Info
* @param [in,out] Sale - array with Products
*/
void ListCreate(Sale *&, Products *&, Info *&, int, int);	/*forward declaration*/

/*
* @brief Function show elements from array of Sale
* @param [in] Sale - array with Products
* @param [in] int - size of array
*/
void Show(Sale *&, int);

/*
* @brief Function provides selection sorting for array of Sale
* @param [in] Sale - array of Sale
* @param [in,out] Sale - array with Products
* @param [in] int - size of array
*/
void SelectionSorting(Sale *&, int);

void main(void)
{
	cout << "How many records you would like to have in INFORMATION array ?" << endl;
	int sizeInfo;
	cin >> sizeInfo;
		if (sizeInfo > 0)
		{
			//NULL 
		}
		else cerr << "Size of array can't be negative" << endl; 
	Info* inform = new Info[sizeInfo];

	cout << "Please enter: <Code> and <Price> separated by space " << sizeInfo << " times" << endl;
	int i = 0;
	while (i != sizeInfo)
	{
		cin >> inform[i].code >> inform[i].price;
		i++;
	}

	cout << "How many records you would like to have in PRODUCTS array ?" << endl;
	int sizeProd;
	cin >> sizeProd;
		if (sizeProd > 0)
		{
			//NULL 
		}
		else cerr << "Size of array can't be negative" << endl;
	Products* prod = new Products[sizeProd];
		
	cout << "Thanks. Now plase enter information for " << sizeProd
		 <<" Products:\n <Name> <Code> <Count> separated by space" << endl;
	int n = 0;
	while (n != sizeProd)
	{
		cin >> prod[n].name >> prod[n].code >> prod[n].count;
		n++;
	}
	
	Sale* sale = new Sale[sizeProd];

	ListCreate(sale,prod,inform,sizeProd,sizeInfo);
	Show(sale,sizeProd);
	SelectionSorting(sale,sizeProd);
	Show(sale,sizeProd);

	delete[] inform;
	delete[] prod;
	delete[] sale;
	system("@pause");
};

void ListCreate(Sale *& sale, Products *& prod, Info *& info, int sizeProd, int sizeInfo)
{
	for (int i = 0; i < sizeProd; i++)
	{
		sale[i].code = prod[i].code;
		strncpy(sale[i].name,prod[i].name,NAME_SIZE);
		sale[i].count = prod[i].count;

		for (int j = 0; j < sizeInfo; j++) 
		{
			if (sale[i].code == info[j].code)
			{
				sale[i].sumPrice = sale[i].count * info[j].price; /*get sumPrice*/
			}
		}

	}
}

void Show(Sale *& sale, int sizeProd)
{
	cout << "\t\tTable\n================================================\n"
		<<"<CODE> <NAME> <COUNT> <SUM PRICE>\n";
	for (int i = 0; i < sizeProd; i++)
	{
		cout << sale[i].code << "\t" << sale[i].name << "\t" << sale[i].count << "\t" << sale[i].sumPrice << endl;
	}
	cout << "================================================" << endl;
}

void SelectionSorting(Sale *& sale, int sizeProd)
{
	cout << "sorting by code..." << endl;
	Sale temp; /*for change values*/
	Sale* pmax;  /*pointer for max element*/

	for (int j = 0; j < sizeProd; j++)
	{	
		pmax = &sale[j];
		for (int i = j; i < sizeProd; i++) /*from next element*/
		{
			if (pmax->code < sale[i].code)
			{
				pmax = &sale[i]; 
			}
		}
				temp = sale[j];/*save value of 1st element*/
				sale[j] = *pmax; /*into 1st - insert max value*/
				*pmax = temp;  /*into max value - insert 1st value from temp*/
	}
}