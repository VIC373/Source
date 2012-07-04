/*
* @file Cross_Zero.h
* @brief This file has declaration of functions and structures for game Cross - Zero
*/
#ifndef CROSS_ZERO
#define CROSS_ZERO

#include <iostream>
#include <ctime>

typedef unsigned int UI;

/*
* @struct Cell
* @brief Each cell has one with three values
*/
struct Cell 
{
	bool cross;
	bool zero;
	bool empty;
};

/*
* @struct Field
* @brief struct for Cells
* @param [in,out] Cell - cells of field
* 
*/
struct Field 
{
	Cell cell[9];
	/*
	* @brief Function set empty for all cells
	*/
	Field();
};

/*
* @brief Function check game : maybe somebody win
* @param [in] Field - game field
* @param [in] bool - (cross or zero) "1" or "0"
* return true whan somebody win
*/
bool Win(const Field&, bool);

/*
* @brief Function for Play
* @param [in] Field - game field 
* @param [in] bool - (cross or zero) "1" or "0"
* @param [in] UI - cell for move
* return true whan move have done
*/
bool Play(Field&, bool, UI);

/*
* @brief Function for show field
* @param [in] Field - game field 
*/
void ShowGame(const Field&);

/*
* @brief Function for move PC (generate [1;9])
* @param [in] Field - game field 
* @param [in] bool - (cross or zero) "1" or "0"
*/
void PcPlay(Field&, bool);


#endif /*CROSS_ZERO*/