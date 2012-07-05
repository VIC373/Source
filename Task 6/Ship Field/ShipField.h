/*
* @file ShipField.h
* @brief This file has declaration of functions and structures for ShipField.cpp
*/

#ifndef SHIP_FIELD
#define SHIP_FIELD

#include "stdafx.h"
#include <iostream>
#include <ctime>
using namespace std;

typedef unsigned char UC;
typedef unsigned short US;

/*
* @struct Cell
* @brief Each cell has one of three values
* 00 empty, 01 ship, 10 hit 11 fire
*/
struct Cell
{
	UC info : 3;  /*sign + 2 numbers = 3*/
};

/*
* @class Field
* @brief Class realize functionality for fild with ships
* @param [in] UC - size of field
* @param [in] Cell* - pointer for array of cells
*/
class Field
{
private:
	UC size;  /*size of field (size * size) */
	Cell* field;

	Field();
	Field(const Field&);
	Field& operator = (const Field&);

	/*
	* @brief this function - change coordinate from x,y to index of array with cells
	* @param UC [in] x,y - coordinate
	* return UC index of array[]
	*/
	US Coord(UC, UC) const;

	/*
	* @brief Function chack area (empty or not)
	* function use next function
	* @param [in] x,y - coordinate
	* return bool - true (empty)
	*/
	bool IsEmpty(UC,UC) const;

	/*
	* @brief Function chack line (empty or not)
	* @param [in] UC - midle point
	* return bool - true (empty)
	*/
	inline bool EmptyLine(UC) const;
public:
	explicit Field(UC); /*UC - size of field = UC*UC*/
	~Field();
	void Show() const;
	bool InitShip(UC,UC,UC,UC); /*x,y and z,f - like line - two points*/
};

/*
* @brief Function check ship size througt coordinate
* @param [in] UC x,y,z,f - coordinate
* @param [in] UC size - size of ship
* return bool true (ship can exist)
*/
inline bool ShipSize(UC x, UC y, UC z, UC f, UC size);

/*
* @brief Function initialize ships for field
* @param [in] UC - ship size
* @param [in] UC - how many ships
* @param [in] Field - field for ships
*/
void Init(UC ShSize, UC count, Field& myField);

#endif /*SHIP_FIELD*/