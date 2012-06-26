/*
* @file Tree.h 
* @brief This file has declaration of functions for Task 4
*/

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

typedef unsigned int UI;

const int NAME_SIZE = 30;

/*
* @struct Author
* @brief struct for temporary array of authors
* @param [in,out] char - name of author
* @param [in,out] int - Erdos number of author
*/
struct Author 
{
	char name[NAME_SIZE];
	int erdosNumber;
};

/*
* @struct Tree
* @brief this struct is node in a tree
* @param [in,out] char - name of author
* @param [in,out] Tree** - pointer for list of elements under this node
* @param [in,out] UI - count of elements under this node
* @param [in,out] UI - Erdos number in this node (for this author)
*/
struct Tree
{
	char name[NAME_SIZE];
	Tree **childs;
	UI count;
	UI erdosNumber;
};

/*
* @brief Function initialize an elements of tree
* @param [in] Tree* - pointer for element that we should initialize
* @param [in] char* - name of author for this element
* return Tree* - pointer for initialized element
*/
Tree* Init(Tree* p, char* name);

/*
* @brief Function show node from tree
* @param [in] Tree* - pointer for element that we should show
*/
void ShowNode(Tree* p);

/*
* @brief Function find element from tree (find by name)
* @param [in] Tree* - pointer for root element
* @param [in] char* - name of author for this element that we should find
* return Tree* - pointer for finded element
*/
Tree* SearchNode(Tree* t, char* name);

/*
* @brief Function add new element to tree
* @param [in] Tree* - pointer for root element of tree
* @param [in] char* - name of author for element after which we should insert new element
* @param [in] char* - name of author for new element
* return Tree* - pointer for added element
*/
Tree* AddNode(Tree* ptr, char* nodeName, char* name);

/*
* @brief Function find element that we need, and show Erdos number for this element (through "cout")
* @param [in] Tree* - pointer for root element of tree
*/
void GetAuthor(Tree* tree);

/*
* @brief Function create elements for tree from string, put this elements in temp array and after this from array to tree
* @param [in] Tree* - pointer for root element of tree
* @param [in] string - text with authors
*/
void CreateElemForTree(Tree* tree, string& text);

#endif /*TREE_H*/