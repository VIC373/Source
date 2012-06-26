/*
* @file Tree.cpp
* @brief This file has definition of functions for Task 4
*/

#include "Tree.h"

using namespace std;

const int ARRAY_SIZE = 10;	 /*Max count authors in one book*/
UI ErdosNumber = 0;	/*Erdos number for all authors - default*/


Tree* Init(Tree* p, char* name)
{
	strcpy(p->name,name);
	p->count = 0;
	p->childs = NULL;
	p->erdosNumber = 0;
	return p;
}

void ShowNode(Tree* p)
{
	cout << "Author " << p->name << " Erdos Number " << p->erdosNumber << endl;
}

Tree* SearchNode(Tree* t, char* name)
{
	ErdosNumber = 0; 

	if (!strcmp(t->name,name)) /* if name in node == name that we found - we return this node */
	{
		return t;
	}
	else if (t->count > 0)  /*if no, we check that the number of children in the node is more than 0*/
	{
		for (UI i = 0; i < t->count; i++) 
		{
			Tree* p = SearchNode(t->childs[i],name); /*the same search for each of sons*/

			ErdosNumber++; /*Erdos number is increased in depth*/
			if (p != NULL) /*if function return initialized node - we found him*/
			{				
				p->erdosNumber = ErdosNumber; /*set Erdos number for this node*/
				return p;
			}
		}
		return NULL;
	}
	else return NULL;
}


Tree* AddNode(Tree* ptr, char* nodeName, char* name)
{
	Tree* p = SearchNode(ptr,nodeName); /*first we should find the node, after which we will insert*/
	if ( p != NULL ) /*if this node exist*/
	{
		if ( p->childs == NULL ) /*if this node has not sons*/
		{
			p->childs = (Tree**)malloc(sizeof(Tree*)); /*create list of sons*/
		
			p->childs[0] = (Tree*)malloc(sizeof(Tree)); /*insert to list new son*/

			p->count = 1; /*this son has count 1 - it is count for his sons*/
		}
		else /*if this node has sons*/
		{
			p->childs = (Tree**)realloc(p->childs,sizeof(Tree*)*(p->count + 1)); /*Extend list for new son*/
	
			p->childs[p->count] = (Tree*)malloc(sizeof(Tree)); /*memory for new son*/

			p->count++; /*count of sons for this node*/
		}
		return Init(p->childs[p->count - 1],name); /*initialize new son*/
	}
	return NULL;
}


void GetAuthor(Tree* tree)/*cin authors and cout number of Erdos for each*/
{
	cout << "How many authors you would like to show?" << endl;
	int k;
	while (1)
	{
		cin >> k;
		if ( k > 0)
		{
			break;
		}
		cout << "You should enter > 0" << endl;
	}
	
	char* name = (char*)malloc(sizeof(char)*NAME_SIZE);

	while (k)
	{
		cout << "Enter author : " << endl;
		cin >> name; 
		Tree* s = SearchNode(tree,name);
		if (s != NULL)
		{
			ShowNode(s);
		}
		else
		{
			cout << "Author " << name << " Erdos Number " << " infinity" << endl;
		}
		k--;
	}
	free(name);
}

void CreateElemForTree(Tree* tree, string& text)
{
	char* ptr = &text[0];
	int space = 0;
	char name[NAME_SIZE]; /*author name*/
	int arrayIndex = 0;
	Author mas[ARRAY_SIZE]; /*Temp array of authors*/

	for (UI i = 0; i < text.length(); i++)
	{
		if ( ptr[i] == ':') /* after ':' we have name of book */
		{
			break; /*exit from for()*/
		}

		else if ( ptr[i] == ' ')
		{
			int k = 0;

			for (UI j = space ; j < i; j++, k++ ) /*from space to space*/
			{
				name[k] = text[j];
			}

			name[k] = '\0';
			space = i + 1; /* start from new word */

			Tree* s = SearchNode(tree,name);
			if ( s != NULL) /*if author exist*/
			{
				strcpy(mas[arrayIndex].name, s->name);
				mas[arrayIndex].erdosNumber = s->erdosNumber;
			}
			else 
			{
				strcpy(mas[arrayIndex].name, name);
				mas[arrayIndex].erdosNumber = 10000;
			}
			arrayIndex++; /*count of elements of array*/
			/*array was completed*/
		}
	}
	
/* Now we should find the lowest numbered by Erdos */
int minErdos = mas[0].erdosNumber;
int index = 0;

	for (int i = 0; i < arrayIndex; i++)
	{
		if ( minErdos > mas[i].erdosNumber )
		{
			minErdos = mas[i].erdosNumber; /*author with lowest number*/
			index = i;
		}
	}

	if ( minErdos >= 0) 
	{
		/* Add to tree from array of authors (but all without himself - because he is already in the tree)*/
		for (int i = 0; i< arrayIndex; i++)
		{
			if ( strcmp(mas[i].name,mas[index].name) )
			{
				AddNode(tree,mas[index].name,mas[i].name);
			}
		}

	}
	/*authors have not connections with tree*/
}