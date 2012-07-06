/*
* @file ShipField.h
* @brief This file has declaration of functions and structures for ShipField.cpp
*/

#ifndef SHIP_FIELD
#define SHIP_FIELD

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <Windows.h> 
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
/*
* @brief function generate ship on a field
* we use "size" from private section, that is whay function like a friend
* return true (ships generated)
*/
friend bool InitPc(Field& myField);
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
	* @param [in] US - midle point
	* return bool - true (empty)
	*/
	inline bool EmptyLine(US) const;
public:
	explicit Field(UC); /*UC - size of field = UC*UC*/
	~Field();
	void Show() const;

	/*
	* @brief Function for fire 
	* @param UC [in] - coordinate
	* return true - (when we have hit)
	*/
	bool Fire(UC,UC);

	/*
	* @brief function return true (if in a field we have not ships)
	*/
	bool Win();
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