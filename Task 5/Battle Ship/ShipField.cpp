#include "stdafx.h"
#include "ShipField.h"

inline bool ShipSize(UC x, UC y, UC z, UC f, UC size)
{
	return ( (x - z == size - 1) || (z - x == size - 1) || (y - f == size - 1) || (f - y == size - 1) );
}

Field::Field(UC n) : size(n)
{
	try
	{
		field = new Cell[n*n];
	}
	catch(bad_alloc& ba)
	{
		cout << ba.what();
	}
	for (US i = 0; i < size*size; i++)
	{
		field[i].info = 0;
	}
}

Field::~Field()
{
	delete[] field;
}

void Field::Show() const
{
	system("CLS");
	char s = 1;
	cout << "   ";
	while (s <= size) /*horizontal numeration*/
	{
		cout << " " << (int)s;
		s++;
	}

	for (US i = 0; i < size*size; i++)
	{	
		if ( i % size == 0 )
		{
			cout  << endl << (int)(i / size) + 1; /*vertical numeration*/
		}

		switch ( field[i].info )
		{
			case 1 : cout << "[]" ; break;
			case 2 : cout << " X" ; break;
			case 3 : cout << " *" ; break;
	
			default : cout << "  " ;
		}
	}
}

US Field::Coord(UC hor, UC vert) const /*interface for mas[100] throught coordinate like (x,y)*/
{
	if ( (hor < size) && (hor > 1) && (vert < size) && (vert > 1 ) ) /*not so close to wall*/
	{
		return ( hor - 1 ) * size + vert;
	}
	else
	{
		return 0;
	}
}

bool Field::InitShip(UC hor, UC vert, UC hor1, UC vert1)
{
	if ( Coord(hor,vert) && Coord(hor1,vert1) ) /*Coordinate normal (on field) ?*/
	{
		if ( (hor == hor1) && IsEmpty(hor,vert) && IsEmpty(hor1,vert1) ) /*HORIZONTAL SHIP && Empty pos?*/
		{
			if ( vert > vert1 ) /*from left to right*/
			{
				while ( vert - vert1 >= 0 )
				{
					field[Coord(hor,vert)].info = 1;
					vert--;
				}
			}
			else /* from right to left */
			{
				while ( vert1 - vert >= 0 )
				{
					field[Coord(hor,vert1)].info = 1;
					vert1--;
				}
			}
			return true;
		}

		else if ( ( vert == vert1) && IsEmpty(hor,vert) && IsEmpty(hor1,vert1) ) /*VERTICAL SHIP && Empty pos?*/
		{
			if ( hor > hor1 ) /*from up to down*/
			{
				while ( hor - hor1 >= 0 )
				{
					field[Coord(hor,vert)].info = 1;
					hor--;
				}
			}
			else /* from down to up */
			{
				while ( hor1 - hor >= 0 )
				{
					field[Coord(hor1,vert)].info = 1;
					hor1--;
				}
			}
		
			return true;
		}
		return false; /*not vertical or horizontal (bad coordinate)*/
	}
	else
	{
		return false; /*bad coordanate (not on a field)*/
	}
}

inline bool Field::EmptyLine(US f) const
{
	return  ( field[f].info == 0 ) && ( field[f+1].info == 0 ) && ( field[f-1].info == 0 ) ;
}

bool Field::IsEmpty(UC x, UC y) const
{
	US f = Coord(x,y);

	if ( EmptyLine(f) && EmptyLine( f + size ) && EmptyLine ( f - size ) )
	{
		return true;
	}
	return false;
}

bool Field::Fire(UC x, UC y)
{
	/* 00 empty, 01 ship, 10 hit 11 fire*/

	US i = Coord(x,y);

	switch (field[i].info)
	{
		case 0 : field[i].info = 3; return false;
		case 1 : field[i].info = 2; return true;
		default : return false;			/*shot to the same cell*/
	}
}

bool Field::Win()
{
	for (US i = 0; i < size*size; i++)
	{
		if ( field[i].info == 1 )
		{
			return true;
		}
	}
	return false;
}

void Init(UC ShSize, UC count, Field& myField)
{
	short x,y,z,f; /* coordinate (we use short 'couse "cin" use short like a number)*/ 
	while (count)
	{
		cout << endl << "Please put coordinate separated by space for " << (int)ShSize << "deck Ship" << endl;
		cin >> x >> y >> z >> f;
		if ( ShSize == 1 )
		{
			z = x;
			f = y;
		}
		if ( ShipSize(x,y,z,f,ShSize) ) 
		{
			if ( myField.InitShip(x,y,z,f) )
			{
				count--;
				myField.Show();
			}
			else
			{
				cout << "Bad coordinate. Err" << endl;
			}
		}
		else
		{
			cout << "Bad coordinate. Err" << endl;
		}
	}
}

bool InitPc(Field& myField)
{
	US x,y,z,f;
	//rand() % (max-min+1) + min  
	
	UC i;

	i = 1;
	while (i)
	{
		srand(time(0));
		x = rand() % (myField.size - 1) + 2;
		y = rand() % (myField.size - 1) + 2;
		z = x;
		f = y + 3;

		if ( ShipSize(x,y,z,f,4 ) )
		{
			if ( myField.InitShip(x,y,z,f) )
			{
				i--;
			}
		}
	}
	myField.Show();
	cout << "4x done" << endl;

	i = 2;
	while (i)
	{
		srand(time(0));
		x = rand() % (myField.size - 1) + 2;
		y = rand() % (myField.size - 1) + 2;
		z = x;
		f = y + 2;

		if ( ShipSize(x,y,z,f,3 ) )
		{
			if ( myField.InitShip(x,y,z,f) )
			{
				i--;
			}
		}
	}
	myField.Show();
	cout << "3x done" << endl;


	i = 3;
	while (i)
	{
		srand(time(0));
		x = rand() % (myField.size - 1) + 2;
		y = rand() % (myField.size - 1) + 2;
		z = x;
		f = y + 1;

		if ( ShipSize(x,y,z,f,2 ) )
		{
			if ( myField.InitShip(x,y,z,f) )
			{
				i--;
			}
		}
	}
	myField.Show();
	cout << "2x done" << endl;
	
	i = 4;
	while (i)
	{
		srand(time(0));
		x = rand() % (myField.size - 1) + 2;
		y = rand() % (myField.size - 1) + 2;
		if ( ShipSize(x,y,x,y,1 ) )
		{
			if ( myField.InitShip(x,y,x,y) )
			{
				i--;
			}
		}
	}
	myField.Show();
	cout << "1x done" << endl;

return true;
}