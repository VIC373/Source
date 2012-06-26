/*
* Mathematician "Erdos" was one of the strongest mathematicians. He published his articles from other scientists that
* the result obtained so-called Erdos number. Those who worked directly with Erdos number 1 received, 
* those who worked with them - get 2, etc. Need to write a program that will count for Erdos number specified number of scientists.
*
* For example:
*
* Putting books
* Erdos Victor Oleg: Book
* Victor Dima Igor: better book
* Igor Ira: new book
*
* Putting scientists
* Victor Dima Ira Igor
*
* Output
* Victor - Erdos number 1
* Dima - Erdos number 2
* Igor - Erdos number 2
* Ira - Erdos number 3
*/
#include "stdafx.h"
#include "Tree.h"
using namespace std;


void main(void)
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	Init(tree,"Erdos");

	string text;
	cout << "Please enter BOOK " << endl;

	while(1)
	{
		text.clear();
		getline(cin,text);
		if ( text == "" )
		{
			GetAuthor(tree);  /*Function for getting author from tree*/
			break; 
		}
		CreateElemForTree(tree,text);
	}
	free(tree);
	system("@pause");
}